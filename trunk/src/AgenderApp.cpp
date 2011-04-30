/***************************************************************
 * Name:      AgenderApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Gabriel Espinoza
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "AgenderApp.h"
#include "AgenderMain.h"
#include "AgenderIPC.h"
#include "Updater.h"
#include "XmlNotes.h"
#include "version.h"

#include <wx/log.h>
#include <wx/defs.h>
#include <wx/stdpaths.h>
#include <wx/cmdline.h>
#include <wx/config.h>
#include <wx/fileconf.h>
#include <wx/uri.h>
#include <wx/image.h>
#include <wx/fs_mem.h>
#include <wx/sysopt.h>
#include <wx/ffile.h>
#include <wx/debugrpt.h>
#include <wx/utils.h>

#ifdef __WXUNIVERSAL__
WX_USE_THEME(Metal);
WX_USE_THEME(mono);
WX_USE_THEME(gtk);
#endif

namespace Agender {

#if defined __UNIX__
#include <signal.h>
//i hate globals
void OnSignal(int sig);
#endif

inline const wxString GetOpenDirCmdFor(const wxString& exe,const wxString& dir)
{
	return exe + _T(" ") + _T("\"") + dir + _T("\"");
}

bool LaunchFileBrowser(const wxString& dir)
{
	wxString file_browser_command;
	#ifdef __WXMSW__
	file_browser_command = GetOpenDirCmdFor(_T("explorer"),dir);
	#elif defined __LINUX__
	file_browser_command = GetOpenDirCmdFor(_T("xdg-open"),dir);
	#elif defined __WXOSX__
	// TODO (gabriel#1#): is this the right command for Finder ?
	file_browser_command = GetOpenDirCmdFor(_T("open -R"),dir);
	#else
	return false;
	#endif
	return wxExecute(file_browser_command) == 0;
}

BEGIN_EVENT_TABLE(AgenderApp,wxApp)
	EVT_QUERY_END_SESSION(AgenderApp::OnEndSession)
	EVT_END_SESSION(AgenderApp::OnEndSession)
END_EVENT_TABLE()

IMPLEMENT_APP(AgenderApp);

#if wxUSE_ON_FATAL_EXCEPTION
AgenderApp::AgenderApp()
{
	::wxHandleFatalExceptions(true);
}
#endif

bool AgenderApp::OnInit()
{
	//who are we?
	SetAppName(wxT("Agender"));
	SetVendorName(wxT("Virtuosonic"));
	//log to file
	{
		wxFileName logfname;
		logfname.AssignDir(wxStandardPaths::Get().GetUserDataDir());
		logfname.SetName(GetAppName());
		logfname.SetExt(_T("log"));
		wxFFile logfile(logfname.GetFullPath(),_T("w"));
		wxLog::SetActiveTarget(new wxLogStderr(logfile.fp()));
		wxLog::SetVerbose(true);
		logfile.Detach();
	}
	//check for datadir
	if (!wxDirExists(wxStandardPaths::Get().GetUserDataDir()))
		wxMkdir(wxStandardPaths::Get().GetUserDataDir());
#if defined __WXMAC__ || defined __WXOSX__
	//spell checking for mac
	wxSystemOptions::SetOptionInt(wxMAC_TEXTCONTROL_USE_SPELL_CHECKER,1);
#endif
	//parse arguments
	wxCmdLineParser cmd(argc,argv);
	//not in use
	//cmd.AddOption(_T("c"),_T("config"),_T("specify a config file to load"),wxCMD_LINE_VAL_STRING);
	//switches
	cmd.AddSwitch(_T("nt"),_T("no-taskbar"),_T("use when you don't have a taskbar"));
	cmd.AddSwitch(_T("p"),_T("portable"),_T("read config and notes from app dir"));
	cmd.AddSwitch(_T("na"),_T("no-autostart"),_T("disable auto start"));
	cmd.AddSwitch(_T("?"),wxEmptyString,wxEmptyString,wxCMD_LINE_OPTION_HELP);
	//why OnInitCmdLine doesn't have /?  ??? :P
	OnInitCmdLine(cmd);
	int res = cmd.Parse(false);
	OnCmdLineParsed(cmd);
	if (res < 0 || cmd.Found(_T("?")))
	{
		cmd.Usage();
		exit(EXIT_SUCCESS);
	}
	//are we alone?
	m_checker = new wxSingleInstanceChecker;
	SingleInstance();
	//load configuration
	if(cmd.Found(_T("p")))//PortableApp
	{
		wxFileName fname;
		fname.AssignDir(wxStandardPaths::Get().GetDataDir());
		fname.SetName(GetAppName());
		fname.SetExt(wxT("ini"));
		wxConfig::Set(new wxFileConfig(wxEmptyString,wxEmptyString,
		                               fname.GetFullPath(),wxEmptyString,wxCONFIG_USE_SUBDIR|
		                               wxCONFIG_USE_LOCAL_FILE));
		fname.SetExt(wxT("xml"));
		AgCal::Set(new AgCal(fname.GetFullPath()));
	}
	else//nonPortableApp
		wxConfig::Set(new wxConfig(wxEmptyString,wxEmptyString,wxEmptyString,wxEmptyString,wxCONFIG_USE_SUBDIR|wxCONFIG_USE_LOCAL_FILE));
	if (cmd.Found(_T("na")))
	{
		wxConfig::Get()->Write(_T("/autostart"),false);
	}
	// please talk me in a language that i understand
	m_locale.Init(wxConfig::Get()->Read(_T("/lang"),wxLANGUAGE_DEFAULT),wxLOCALE_LOAD_DEFAULT);
	m_locale.AddCatalog(wxT("Agender"),wxLANGUAGE_ENGLISH,wxT("UTF-8"));
	//(*AppInitialize
	bool wxsOK = true;
	wxInitAllImageHandlers();
	//*)
	//create main frame
	wxFrame* Frame = new AgenderFrame(m_locale);
	SetTopWindow(Frame);
	//lets create a server so Anothers can comunicate with this->m_server
	m_server = new AgenderServer;
	if (m_server->Create(IPC_Service))
		wxLogMessage(_T("server created"));
	else
	{
		wxLogWarning(_T("server creation failed"));
		m_server = NULL;
	}
	//no taskbar?
	if (cmd.Found(_T("nt")))
		Frame->Show();
#ifdef __UNIX__
	signal(SIGINT,&OnSignal);
	signal(SIGTERM,&OnSignal);
#endif
#if !defined wxHAS_TASK_BAR_ICON
	Frame->Show();
#endif//wxHAS_TASK_BAR_ICON
	return wxsOK;
}

int AgenderApp::OnRun()
{
	//here we create the updater & let it search for updates
	try {
		Updater* up = new Updater(_T("agender.sourceforge.net"),
		                          wxT("/agender_version"),wxString::FromAscii(FULLVERSION_STRING));
		if (up->Create() == wxTHREAD_NO_ERROR)
		{
			if (up->Run() != wxTHREAD_NO_ERROR)
				delete up;
		}
	}
	catch(...) {}
	notif.Start(20000);
	//continue
	return wxApp::OnRun();
}

int AgenderApp::OnExit()
{
	if (m_checker)
		delete m_checker;
	if (m_server)
		delete m_server;
	//delete global pointer
	delete AgCal::Get();
	wxLogMessage(_T("Exiting: goodbye"));
	return wxApp::OnExit();
}

#ifdef __UNIX__
void OnSignal(int sig)
{
	wxLogMessage(_T("signal %i catched"),sig);
	if (wxTheApp->GetTopWindow())
	{
		//if the frame is hiden calling destroy won't work
		wxTheApp->GetTopWindow()->Show();
		wxTheApp->GetTopWindow()->Destroy();
	}
}
#endif

void AgenderApp::OnEndSession(wxCloseEvent& WXUNUSED(event))
{
	wxLogMessage(_T("ending session"));
	if (GetTopWindow())
	{
		GetTopWindow()->Show();
		GetTopWindow()->Destroy();
	}
}

void AgenderApp::SingleInstance()
{
	if (m_checker->Create(_T(".") + GetAppName() + _T("-") + ::wxGetUserId())
	        && m_checker->IsAnotherRunning())
	{
		//lets try to connect to Another and  asking to show it self
		wxClient client;
		wxConnection* cnn = NULL;
		cnn = (wxConnection*)client.MakeConnection(_T("localhost"),IPC_Service,IPC_Topic);
		if (cnn)
		{
			wxLogMessage(_T("executing"));
			//this is a security issue, someone could write a client application(even you),
			//that sends NULL, via Execute and causes Agender to crash
			if (cnn->Execute(wxEmptyString))
			{
				wxLogMessage(_T("finished executing"));
				//first ending, like on video games it sucks!
				exit(EXIT_SUCCESS);
			}
			wxLogError(_T("not executed"));
		}
		else
			wxLogError(_T("connection failed: %s"),wxSysErrorMsg());
		//this goes outside of the 'else' because  if everything goes right : exit(EXIT_SUCCESS);
		//second ending, like on videogames it sucks even more!
		exit(EXIT_FAILURE);
	}
}

#if wxUSE_ON_FATAL_EXCEPTION
void AgenderApp::OnFatalException()
{
	wxDebugReportCompress *report = new wxDebugReportCompress;
	report->AddAll(wxDebugReport::Context_Exception);
	//add log file
	wxFileName logfname;
	logfname.AssignDir(wxStandardPaths::Get().GetUserDataDir());
	logfname.SetName(GetAppName());
	logfname.SetExt(_T("log"));
	report->AddFile(logfname.GetFullPath(),_("Agender log file"));
	//add revision data
	report->AddText(_T("svn_revision.txt"),
			wxString::FromAscii(SVN_REVISION)+
			_T(" ") + wxString::FromAscii(SVN_DATE),
			_("Subversion revision data."));
	//preview
	if ( wxDebugReportPreviewStd().Show(*report) )
	{
		report->Process();
		wxString dir(report->GetDirectory());
		report->Reset();
		::wxLaunchDefaultBrowser(_T("http://sourceforge.net/tracker/?group_id=271084&atid=1152801"));
		LaunchFileBrowser(dir);
	}
	delete report;
}
#endif
}//namespace Agender

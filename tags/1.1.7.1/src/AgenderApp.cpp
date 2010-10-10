/***************************************************************
 * Name:      AgenderApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Gabriel Espinoza
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "AgenderApp.h"
#include "AgenderMain.h"
#include "AgenderIPC.h"

#ifndef WX_PRECOMP
#include <wx/log.h>
#include <wx/defs.h>
#include <wx/stdpaths.h>
#include <wx/cmdline.h>
#endif

#if !defined __WXMAC__ || !defined __WXOSX__
#include <iostream>
#endif

#if defined __UNIX__
#include <signal.h>
//i hate globals
void OnSignal(int sig);
#endif

//(*AppHeaders
#include <wx/image.h>
//*)

BEGIN_EVENT_TABLE(AgenderApp,wxApp)
	EVT_QUERY_END_SESSION(AgenderApp::OnEndSession)
	EVT_END_SESSION(AgenderApp::OnEndSession)
END_EVENT_TABLE()

IMPLEMENT_APP(AgenderApp);

bool AgenderApp::OnInit()
{
	//who are we?
	SetAppName(_T("Agender"));
	SetVendorName(_T("Virtuosonic"));
#if defined __WXMAC__ || defined __WXOSX__
	//under OSX the next block gives a compilation error
	//so we use this instead
	wxLogNull logNo;
	wxSystemOptions::SetOptionInt(wxMAC_TEXTCONTROL_USE_SPELL_CHECKER,1);
#else
	/*redirect logging to cout, if you want to annoy users use ::wxMessageBox(_T("do you want me to annoy you?"));*/
	delete wxLog::SetActiveTarget(new wxLogStream(&std::cout));
#endif
	//parse arguments
	wxCmdLineParser cmd(argc,argv);
	cmd.AddOption(_T("c"),_T("config"),_T("specify a config file to load"),wxCMD_LINE_VAL_STRING);
	cmd.AddSwitch(_T("nt"),_T("no-taskbar"),_T("use when you don't have a taskbar"));
	OnInitCmdLine(cmd);
	int res = cmd.Parse(false);
	if (res < 0)
	{
		cmd.Usage();
		exit(EXIT_SUCCESS);
	}
	wxString cfgFile;
	cmd.Found(_T("c"),&cfgFile);
	if(cmd.Found(_T("verbose")))
	{
		wxLog::SetVerbose(true);
	}
	//are we alone?
	m_checker = new wxSingleInstanceChecker;
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
				wxLogVerbose(_T("finished executing"));
				//first ending, like on video games it sucks!
				exit(EXIT_SUCCESS);
			}
			wxLogVerbose(_T("not executed"));
		}
		else
			wxLogVerbose(_T("connection failed: %s"),wxSysErrorMsg());
		//this goes outside of the 'else' because  if everything goes right : exit(EXIT_SUCCESS);
		//second ending, like on videogames it sucks even more!
		exit(EXIT_FAILURE);
	}
	// please talk me in a language that i understand
	if (m_locale.Init(wxLANGUAGE_DEFAULT,wxLOCALE_LOAD_DEFAULT)) ;

	m_locale.AddCatalog(wxT("Agender"),wxLANGUAGE_ENGLISH,wxT("UTF-8"));

	//(*AppInitialize
	bool wxsOK = true;
	wxInitAllImageHandlers();
	//*)
	//create main frame
	wxFrame* Frame = new AgenderFrame(m_locale,cfgFile);
	SetTopWindow(Frame);
	//lets create a server so Anothers can comunicate with this->m_server
#ifndef __WXMSW__
	m_server = new AgenderServer;
	if (m_server->Create(IPC_Service))
		wxLogVerbose(_T("server created"));
	else
		wxLogVerbose(_T("server creation failed"));
#else
	m_server = NULL;
#endif
	//no taskbar?
	if (cmd.Found(_T("nt")))
		Frame->Show();
#ifdef __UNIX__
	signal(SIGINT,&OnSignal);
	signal(SIGTERM,&OnSignal);
#endif
#if !defined wxHAS_TASK_BAR_ICON
	Frame->Show();
	// TODO (virtuoso#1#): think in another way to exit agender
	//without having to kill it
	//this is intended for some mobile platform, is it needed?
	//i remember that windows CE had a function to finish apps
	// and accoding to its guidelines it should continue in memory
	//but what about Familiar Linux, iPhoneOS, etc ?
#endif//wxHAS_TASK_BAR_ICON
	return wxsOK;
}

int AgenderApp::OnExit()
{
	if (m_checker)
		delete m_checker;
	if (m_server)
		delete m_server;
	wxLogVerbose(_T("Exiting: goodbye"));
	return wxApp::OnExit();
}

#ifdef __UNIX__
void OnSignal(int sig)
{
	wxLogVerbose(_T("signal %i catched"),sig);
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
	wxLogVerbose(_T("ending session"));
	if (GetTopWindow())
	{
		GetTopWindow()->Show();
		GetTopWindow()->Destroy();
	}
}

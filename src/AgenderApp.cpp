/***************************************************************
 * Name:      AgenderApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Gabriel Espinoza
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License: GPL 3
 **************************************************************/

#include "AgenderApp.h"
#include "AgenderMain.h"
#include "AgenderIPC.h"

#include <wx/log.h>
#include <wx/defs.h>
#include <wx/stdpaths.h>
#include <wx/cmdline.h>
#include <wx/apptrait.h>
#include <iostream>

#if defined __UNIX__
	#include <signal.h>
#endif

//(*AppHeaders
#include <wx/image.h>
//*)

#ifdef __UNIX__
//i hate globals
void OnSignal(int sig);
#endif

BEGIN_EVENT_TABLE(AgenderApp,wxApp)
	//does this work somewhere? write once, debug everywhere!
	EVT_QUERY_END_SESSION(AgenderApp::OnEndSession)
	EVT_END_SESSION(AgenderApp::OnEndSession)
	// TODO (virtuoso#1#): probar usar idleevent
END_EVENT_TABLE()

IMPLEMENT_APP(AgenderApp);

bool AgenderApp::OnInit()
{
	//who are we?
	SetAppName(_T("Agender"));
	SetVendorName(_T("Virtuosonic"));
	//redirect logging to cout, if you want to annoy users use ::wxMessageBox(_T("do you want me to annoy you?"));
	delete wxLog::SetActiveTarget(new wxLogStream(&std::cout));
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
	//are we alone?
	m_checker = new wxSingleInstanceChecker;
	if (m_checker->Create(_T(".") + GetAppName() + _T("-") + ::wxGetUserId())
		&& m_checker->IsAnotherRunning())
	{
		//lets try to connect to Another and  asking to show it self
		wxClient client;
		AgenderConnection* cnn = NULL;
		cnn = (AgenderConnection*)client.MakeConnection(_T("localhost"),IPC_Service,IPC_Topic);
		if (cnn)
		{
			wxLogMessage(_T("executing"));
			cnn->Execute(IPC_Topic);
			if (cnn->Execute(IPC_Topic))
			{
				wxLogMessage(_T("finished executing"));
				//first ending, like on video games it sucks!
				exit(EXIT_SUCCESS);
			}
			wxLogError(_T("not executed"));
		}
		else
			wxLogError(_T("connection failed"));
		//this goes outside of the 'else' because  if everything goes right : exit(EXIT_SUCCESS);
		//second ending, like on videogames it sucks even more!
		exit(EXIT_FAILURE);
	}
	// please talk me in a language that i understand
	if (m_locale.Init(wxLANGUAGE_DEFAULT,wxLOCALE_CONV_ENCODING))
		m_locale.AddCatalog(wxT("Agender"));
	//(*AppInitialize
	bool wxsOK = true;
	wxInitAllImageHandlers();
	//*)
	//create main frame
	wxFrame* Frame = new AgenderFrame(m_locale,cfgFile);
	SetTopWindow(Frame);
	//lets create a server so Anothers can comunicate with this->m_server
	m_server = new AgenderServer;
	if (m_server->Create(IPC_Service))
		wxLogMessage(_T("server created"));
	else
		wxLogError(_T("server creation failed"));
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
	wxLogMessage(_T("Exiting: goodbye"));
	return wxApp::OnExit();
}

#ifdef __UNIX__
void OnSignal(int sig)
{
	wxLogMessage(_T("signal %i catched"),sig);
	if (wxTheApp->GetTopWindow())
	{
		wxTheApp->GetTopWindow()->Show();
		wxTheApp->GetTopWindow()->Destroy();
	}
}
#endif

void AgenderApp::OnEndSession(wxCloseEvent& event)
{
	wxLogMessage(_T("ending session"));
	if (GetTopWindow())
	{
		GetTopWindow()->Show();
		GetTopWindow()->Destroy();
	}
}


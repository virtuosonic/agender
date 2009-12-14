/***************************************************************
 * Name:      AgenderApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Gabriel Espinoza
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License:
 **************************************************************/

#include "AgenderApp.h"
#ifdef __UNIX__
#include <signal.h>
#endif
#include <wx/log.h>
#include <iostream>

//(*AppHeaders
#include "AgenderMain.h"
#include <wx/image.h>
//*)

void OnSigTerm(int sig)
{
	::wxExit();
}

IMPLEMENT_APP(AgenderApp);

bool AgenderApp::OnInit()
{
	wxLog* logger = new wxLogStream(&std::cout);
	delete wxLog::SetActiveTarget(logger);
	wxLog::SetVerbose(true);
	m_checker = new wxSingleInstanceChecker(_T(".") + GetAppName() + _T("-") + ::wxGetUserId());
	if (m_checker->IsAnotherRunning())
	{
		AgenderClient client;
		AgenderConnection* cnn = NULL;
		cnn = (AgenderConnection*)client.MakeConnection(_T("localhost"),IPC_Service,IPC_Topic);
		if (cnn)
		{
			wxLogMessage(_T("executing"));
			cnn->Execute(IPC_Topic);
			if (cnn->Execute(IPC_Topic))
				wxLogMessage(_T("finished executing"));
			else
				wxLogError(_T("not executed"));
		}
		else
			wxLogError(_T("connection failed"));
		return false;
	}
#ifdef __UNIX__
	signal(SIGTERM,OnSigTerm);
#endif
	//(*AppInitialize
	bool wxsOK = true;
	wxInitAllImageHandlers();
	if ( wxsOK )
	{
	AgenderFrame* Frame = new AgenderFrame(0);
	Frame->Show(false);
	SetTopWindow(Frame);
	}
	//*)
	m_server = new AgenderServer((wxFrame*)GetTopWindow());
	if (m_server->Create(IPC_Service))
		wxLogMessage(_T("server created"));
	else
		wxLogError(_T("server creation failed"));
	return wxsOK;
}

int AgenderApp::OnExit()
{
	delete m_checker;
	delete m_server;
	return wxApp::OnExit();
}

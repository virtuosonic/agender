/***************************************************************
 * Name:      AgenderApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Gabriel Espinoza
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License: GPL 3
 **************************************************************/

#include "AgenderApp.h"
#include "AgenderIPC.h"

#include <wx/log.h>
#include <wx/stdpaths.h>
#include <iostream>

//(*AppHeaders
#include "AgenderMain.h"
#include <wx/image.h>
//*)

IMPLEMENT_APP(AgenderApp);

bool AgenderApp::OnInit()
{
	//who are we?
	SetAppName(_T("Agender"));
	SetVendorName(_T("Virtuosonic"));
	//redirect logging to cout, if you want to annoy users use ::wxMessageBox(_T("do you want me to annoy you"));
	wxLog* logger = new wxLogStream(&std::cout);
	delete wxLog::SetActiveTarget(logger);
	wxLog::SetVerbose(true);
	wxLogMessage(wxStandardPaths::Get().GetExecutablePath());
	m_checker = new wxSingleInstanceChecker(_T(".") + GetAppName() + _T("-") + ::wxGetUserId());
	if (m_checker->IsAnotherRunning())
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
				wxLogMessage(_T("finished executing"));
			else
				wxLogError(_T("not executed"));
		}
		else
			wxLogError(_T("connection failed"));
		return false;
	}
	// please talk me in a language that i understand
	if (m_locale.Init(wxLANGUAGE_DEFAULT,wxLOCALE_CONV_ENCODING))
		m_locale.AddCatalog(wxT("Agender"));
	//(*AppInitialize
	bool wxsOK = true;
	wxInitAllImageHandlers();
	if ( wxsOK )
	{
		AgenderFrame* Frame = new AgenderFrame(m_locale);
		Frame->Show(false);
		SetTopWindow(Frame);
	}
	//*)
	//lets create a server so Anothers can comunicate with this->m_server
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
	wxLogMessage(_T("Exiting: goodbye"));
	return wxApp::OnExit();
}

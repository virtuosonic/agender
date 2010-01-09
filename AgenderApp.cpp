/***************************************************************
 * Name:      AgenderApp.cpp
 * Purpose:   Code for Application Class
 * Author:    Gabriel Espinoza
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License:
 **************************************************************/

#include "AgenderApp.h"

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
	SetAppName(_T("Agender"));
	wxLog* logger = new wxLogStream(&std::cout);
	delete wxLog::SetActiveTarget(logger);
	wxLog::SetVerbose(true);
	wxLogMessage(wxStandardPaths::Get().GetExecutablePath());
	m_checker = new wxSingleInstanceChecker(_T(".") + GetAppName() + _T("-") + ::wxGetUserId());
	if (m_checker->IsAnotherRunning())
	{
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
	wxLogMessage(_T("Exiting:goodbye"));
	return wxApp::OnExit();
}

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
	wxLogNull logNo;
	m_checker = new wxSingleInstanceChecker(_T(".") + GetAppName() + _T("-") + ::wxGetUserId());
	if (m_checker->IsAnotherRunning())
		return false;
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
	return wxsOK;
}

int AgenderApp::OnExit()
{
	delete m_checker;
	return wxApp::OnExit();
}

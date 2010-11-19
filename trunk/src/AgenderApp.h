/***************************************************************
 * Name:      AgenderApp.h
 * Purpose:   Defines Application Class
 * Author:    Gabriel Espinoza (virtuosonic@users.sourceforge.net)
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef AGENDERAPP_H_INCLUDED
#define AGENDERAPP_H_INCLUDED

#include <wx/app.h>
#include <wx/snglinst.h>
#include <wx/intl.h>
#include <wx/ipc.h>
#include "Notifier.h"
//#include "AgenderIPC.h"

class AgenderApp : public wxApp
{
	public:
		bool OnInit();
		int OnRun();
		int OnExit();
	private:
		void OnEndSession(wxCloseEvent& event);
		wxSingleInstanceChecker* m_checker;
		wxThread* httpUp;
		wxServer* m_server;
		wxLocale m_locale;
		Notifier notif;
		DECLARE_EVENT_TABLE()
};

DECLARE_APP(AgenderApp)

#endif // AGENDERAPP_H_INCLUDED

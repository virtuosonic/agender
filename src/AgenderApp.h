/***************************************************************
 * Name:      AgenderApp.h
 * Purpose:   Defines Application Class
 * Author:    Gabriel Espinoza (virtuosonic@users.sourceforge.net)
unrecognized  * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef AGENDERAPP_H_INCLUDED
#define AGENDERAPP_H_INCLUDED

#include <wx/app.h>
#include <wx/snglinst.h>
#include <wx/intl.h>
#include <wx/ipc.h>
#include <wx/thread.h>
#include "Notifier.h"

class AgenderApp : public wxApp
{
	public:
		bool OnInit();
		int OnRun();
		int OnExit();
	private:
		void OnEndSession(wxCloseEvent& event);
		inline void SingleInstance();
		wxSingleInstanceChecker* m_checker;
		wxServer* m_server;
		wxLocale m_locale;
		Notifier notif;
		wxMutex run_mutex;
		wxCondition* exit_cond;
		DECLARE_EVENT_TABLE()
};

#endif // AGENDERAPP_H_INCLUDED

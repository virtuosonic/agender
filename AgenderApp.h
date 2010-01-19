/***************************************************************
 * Name:      AgenderApp.h
 * Purpose:   Defines Application Class
 * Author:    Gabriel Espinoza (virtuosonic@users.sourceforge.net)
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License: GPL 3
 **************************************************************/

#ifndef AGENDERAPP_H_INCLUDED
#define AGENDERAPP_H_INCLUDED

#include <wx/app.h>
#include <wx/snglinst.h>
#include <wx/intl.h>

#include <wx/ipc.h>

class AgenderApp : public wxApp
{
	public:
		virtual bool OnInit();
		virtual int OnExit();
	private:
		wxSingleInstanceChecker* m_checker;
		wxServer* m_server;
		wxLocale m_locale;
};

#endif // AGENDERAPP_H_INCLUDED

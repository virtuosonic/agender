/***************************************************************
 * Name:      AgenderApp.h
 * Purpose:   Defines Application Class
 * Author:    Gabriel Espinoza (virtuoso.sdc@gmail.com)
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza (www.virtuosonic.110mb.com)
 * License:
 **************************************************************/

#ifndef AGENDERAPP_H
#define AGENDERAPP_H

#include <wx/app.h>
#include <wx/snglinst.h>
#include <wx/intl.h>
#include "AgenderIPC.h"

class AgenderApp : public wxApp
{
	public:
		virtual bool OnInit();
		virtual int OnExit();
	private:
		wxSingleInstanceChecker* m_checker;
		AgenderServer* m_server;
		wxLocale m_locale;
};

#endif // AGENDERAPP_H

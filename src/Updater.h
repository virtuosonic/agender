/***************************************************************
 * Name:      Updater.h
 * Purpose:   Defines Updater Class, connects to a http server and
 *		asks for the latest version
 * Author:    Gabriel Espinoza (virtuosonic@users.sourceforge.net)
 * Created:   2010-09-23
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef _UPDATER_H_
#define _UPDATER_H_

#include <wx/thread.h>
#include <wx/string.h>
#include <wx/dynarray.h>

//this is a detached thread
//it creates a http client
//searchs the lastest version
//in the file hosted in host
//and compares it with
//ver, which is a string of
//the style 1.1.9, if the one
//found in host is newer
//it sends a message to
//the topwindow

class Updater : public wxThread
{
	public:
		Updater(wxString host,wxString file,wxString ver);
		~Updater();
		ExitCode Entry();
	private:
		//methods
		wxString Search();
		bool IsLatest(wxString latest);
		void AskUser(wxString ver);
		wxArrayInt ToInt(wxString ver);
		//members
		wxString m_host;
		wxString m_file;
		wxString m_ver;
};

#endif // _UPDATER_H_

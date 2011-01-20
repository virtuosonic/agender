/***************************************************************
 * Name:      AboutDialog.h
 * Purpose:   New about dialog
 * Author:    Gabriel Espinoza
 * Created:   2010-12-31
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
 #ifndef ABOUTDIALOG_H
#define ABOUTDIALOG_H

//(*Headers(AboutDialog)
#include <wx/notebook.h>
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/statbmp.h>
#include <wx/dialog.h>
#include <wx/html/htmlwin.h>
//*)

#include <wx/aboutdlg.h>

class AboutDialog: public wxDialog
{
	public:

		AboutDialog(wxAboutDialogInfo& info,wxWindow* parent=0);
		virtual ~AboutDialog();

	private:

		//(*Declarations(AboutDialog)
		//*)

		//(*Identifiers(AboutDialog)
		static const long ID_STATICBITMAP1;
		static const long ID_HTMLWINDOW1;
		static const long ID_HTMLWINDOW3;
		static const long ID_HTMLWINDOW4;
		static const long ID_TEXTCTRL1;
		static const long ID_NOTEBOOK1;
		//*)

		//(*Handlers(AboutDialog)
		//*)
		void OnLink(wxHtmlLinkEvent& event);

		DECLARE_EVENT_TABLE()
};

#endif

/***************************************************************
 * Name:      AgenderTray.h
 * Purpose:   Defines TaskBarIcon Class
 * Author:    Gabriel Espinoza (virtuosonic@users.sourceforge.net)
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef AGENDERTRAY_H
#define AGENDERTRAY_H

#include <wx/taskbar.h>
#include <wx/colour.h>
#include <wx/frame.h>
#include "wxAutoStart.h"

class AgenderTray : public wxTaskBarIcon
{
	public:
		AgenderTray(wxFrame* frame);
		wxMenu* CreatePopupMenu();
	private:
		enum
		{
			ID_SHOW = wxID_HIGHEST+1,
			ID_HIDE,
			ID_OPC100,
			ID_OPC75,
			ID_OPC50,
			ID_OPC25,
			ID_BGCOLOUR,
			ID_SYMBOL,
			ID_YEARSEL=7003,
			ID_NOTES_COLOUR=7004,
			ID_AUTOSTART = 7005,
			ID_NOTIFY,
			ID_LANG_DEF,
			ID_LANG_ES,
			ID_LANG_DE,
			ID_LANG_JA,
			ID_LANG_SV,
			ID_LANG_FR,
			ID_LANG_PT,
			ID_LANG_EL,
			ID_LANG_ZH_HK,
			ID_LANG_ZH_CN,
			ID_LANG_HE,
			ID_LANG_RO,
			ID_LANG_LAST
		};
		wxFrame* frame;
		int alpha;
		int opc;
		wxColour notesColour;
		AutoStart astart;

		void OnLeft(wxTaskBarIconEvent& event);
		void OnMenuShow(wxCommandEvent& event);
		void OnMenuHide(wxCommandEvent& event);
		void OnMenuOpc(wxCommandEvent& event);
		void OnYearSel(wxCommandEvent& event);
		void OnMenuNotesColour(wxCommandEvent& event);
		void OnMenuExit(wxCommandEvent& event);
		void OnMenuFind(wxCommandEvent& event);
		void OnMenuAutoStart(wxCommandEvent& event);
		void OnMenuSymbols(wxCommandEvent& event);
		void OnMenuNotify(wxCommandEvent& event);
		void OnMenuLang(wxCommandEvent& event);

		DECLARE_EVENT_TABLE()
};

#endif // AGENDERTRAY_H

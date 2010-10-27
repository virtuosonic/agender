/***************************************************************
 * Name:      AgenderMain.h
 * Purpose:   Defines Application Frame
 * Author:    Gabriel Espinoza
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/

#ifndef AGENDERMAIN_H
#define AGENDERMAIN_H

//(*Headers(AgenderFrame)
#include <wx/sizer.h>
#include <wx/textctrl.h>
#include <wx/calctrl.h>
#include <wx/listbox.h>
#include <wx/button.h>
#include <wx/frame.h>
//*)
#include <wx/fileconf.h>
#include <wx/config.h>
#include <wx/fdrepdlg.h>
#include <wx/taskbar.h>

#define __AGENDER_VERSION__ _T("1.1.9")

class AgenderCal;

class AgenderFrame: public wxFrame
{
	public:
		AgenderFrame(wxLocale& locale,wxString cfgFile);
		~AgenderFrame();
		static const long ID_UPDATE_FOUND;
	private:
		//(*Handlers(AgenderFrame)
		void OnButton3Click(wxCommandEvent& event);
		void OnCalendarCtrl1Changed(wxCalendarEvent& event);
		void OnListBox1Select(wxCommandEvent& event);
		void OnBtnNuevoClick(wxCommandEvent& event);
		void OnBtnElimClick(wxCommandEvent& event);
		void OnClose(wxCloseEvent& event);
		void OnCalendarCtrl1MonthChanged(wxCalendarEvent& event);
		void OnTextCtrl1Text(wxCommandEvent& event);
		void OnListBox1DClick(wxCommandEvent& event);
		//*)
		void OnFind(wxFindDialogEvent& event);
		void OnSearch(wxCommandEvent& event);
		void OnChangeNotesColour(wxCommandEvent& event);
		void OnYearSel(wxCommandEvent& event);
		void OnMenuRename(wxCommandEvent& event);
		void OnMenuNoteFlag(wxCommandEvent& event);
		void OnActivate(wxActivateEvent& event);
		void OnEscape(wxCommandEvent& event);
		void OnUpdateFound(wxCommandEvent& event);
		//(*Identifiers(AgenderFrame)
		static const long ID_CALENDARCTRL1;
		static const long ID_LISTBOX1;
		static const long ID_TEXTCTRL1;
		static const long ID_BUTTON1;
		static const long ID_BUTTON2;
		//*)
		//(*Declarations(AgenderFrame)
		wxButton* BtnNuevo;
		wxCalendarCtrl* CalendarCtrl1;
		wxButton* BtnElim;
		wxButton* Button3;
		wxTextCtrl* TextCtrl1;
		wxListBox* ListBox1;
		//*)
		wxFindReplaceDialog* fndDlg;
		wxFindReplaceData* fndData;
		wxFileConfig* schdl;
		wxString schFile;
		wxTaskBarIcon* trayicon;
		bool SearchMode;
		wxLocale& m_locale;
		AgenderCal* a_cal;

		void MarkDays();
		void ChangeSelector();

		enum
		{
			ID_RENAME,
			ID_NORMAL,
			ID_STICKY
		};

		DECLARE_EVENT_TABLE()
};

#endif // AGENDERMAIN_H

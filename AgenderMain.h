/***************************************************************
 * Name:      AgenderMain.h
 * Purpose:   Defines Application Frame
 * Author:    Gabriel Espinoza
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License:
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
#include <wx/arrstr.h>
#include <wx/fdrepdlg.h>
#include <wx/taskbar.h>

class AgenderFrame: public wxFrame
{
    public:

        AgenderFrame(wxLocale& locale);
        virtual ~AgenderFrame();

    private:

        //(*Handlers(AgenderFrame)
        void OnButton3Click(wxCommandEvent& event);
        void OnCalendarCtrl1Changed(wxCalendarEvent& event);
        void OnListBox1Select(wxCommandEvent& event);
        void OnBtnNuevoClick(wxCommandEvent& event);
        void OnBtnElimClick(wxCommandEvent& event);
        void OnClose(wxCloseEvent& event);
        void OnCalendarCtrl1MonthChanged(wxCalendarEvent& event);
        //*)
        void OnFind(wxFindDialogEvent& event);
        void OnSearch(wxCommandEvent& event);
        void OnChangeNotesColour(wxCommandEvent& event);
        void OnYearSel(wxCommandEvent& event);
        void OnAutoStart(wxCommandEvent& event);

        //(*Identifiers(AgenderFrame)
        static const long ID_CALENDARCTRL1;
        static const long ID_LISTBOX1;
        static const long ID_TEXTCTRL1;
        static const long ID_BUTTON1;
        static const long ID_BUTTON2;
        static const long ID_BUTTON3;
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

        void MarkDays();
        void savePastNote();
        void ChangeSelector();

        wxFileConfig* schdl;
        wxTaskBarIcon* trayicon;
        wxString schFile;
        wxArrayString msgs;
        int prevSel;
        bool SearchMode;
        wxString prevDate;
        wxLocale& m_locale;

        DECLARE_EVENT_TABLE()
};

#endif // AGENDERMAIN_H

/***************************************************************
 * Name:      AgenderMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Gabriel Espinoza
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License:
 **************************************************************/

#include "AgenderMain.h"
#include <wx/msgdlg.h>

//(*InternalHeaders(AgenderFrame)
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/aboutdlg.h>
#include <wx/accel.h>
#include <wx/textdlg.h>
#include <wx/stdpaths.h>
#include <wx/wfstream.h>
#include <wx/utils.h>
#include <wx/datetime.h>
#include <wx/log.h>

//escribir algunas cosas en el registro
#ifdef __WXMSW__
#include <wx/msw/registry.h>
#endif

#include "AgenderTray.h"


#include "version.h"
#include "Agender16x16.xpm"
#include "Agender.xpm"

//(*IdInit(AgenderFrame)
const long AgenderFrame::ID_CALENDARCTRL1 = wxNewId();
const long AgenderFrame::ID_LISTBOX1 = wxNewId();
const long AgenderFrame::ID_TEXTCTRL1 = wxNewId();
const long AgenderFrame::ID_BUTTON1 = wxNewId();
const long AgenderFrame::ID_BUTTON2 = wxNewId();
const long AgenderFrame::ID_BUTTON3 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AgenderFrame,wxFrame)
    EVT_FIND(wxID_ANY,AgenderFrame::OnFind)
    EVT_MENU(wxID_FIND,AgenderFrame::OnSearch)
    //(*EventTable(AgenderFrame)
    //*)
END_EVENT_TABLE()

AgenderFrame::AgenderFrame(wxWindow* parent,wxWindowID id)
{
    //(*Initialize(AgenderFrame)
    wxBoxSizer* BoxSizer1;
    wxFlexGridSizer* FlexGridSizer1;

    Create(parent, wxID_ANY, _("Agender"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxCLOSE_BOX|wxFRAME_TOOL_WINDOW|wxWANTS_CHARS, _T("wxID_ANY"));
    FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
    FlexGridSizer1->AddGrowableCol(0);
    FlexGridSizer1->AddGrowableRow(0);
    CalendarCtrl1 = new wxCalendarCtrl(this, ID_CALENDARCTRL1, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SEQUENTIAL_MONTH_SELECTION|wxSUNKEN_BORDER|wxTAB_TRAVERSAL, _T("ID_CALENDARCTRL1"));
    FlexGridSizer1->Add(CalendarCtrl1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    ListBox1 = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
    FlexGridSizer1->Add(ListBox1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE, wxDefaultValidator, _T("ID_TEXTCTRL1"));
    TextCtrl1->Disable();
    FlexGridSizer1->Add(TextCtrl1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    BoxSizer1 = new wxBoxSizer(wxVERTICAL);
    BtnNuevo = new wxButton(this, ID_BUTTON1, _("Add note"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
    BtnNuevo->SetDefault();
    BoxSizer1->Add(BtnNuevo, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    BtnElim = new wxButton(this, ID_BUTTON2, _("Delete selection"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
    BoxSizer1->Add(BtnElim, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    Button3 = new wxButton(this, ID_BUTTON3, _("About..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON3"));
    BoxSizer1->Add(Button3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
    FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
    SetSizer(FlexGridSizer1);
    FlexGridSizer1->Fit(this);
    FlexGridSizer1->SetSizeHints(this);
    Center();

    Connect(ID_CALENDARCTRL1,wxEVT_CALENDAR_SEL_CHANGED,(wxObjectEventFunction)&AgenderFrame::OnCalendarCtrl1Changed);
    Connect(ID_CALENDARCTRL1,wxEVT_CALENDAR_MONTH_CHANGED,(wxObjectEventFunction)&AgenderFrame::OnCalendarCtrl1MonthChanged);
    Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&AgenderFrame::OnListBox1Select);
    Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AgenderFrame::OnBtnNuevoClick);
    Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AgenderFrame::OnBtnElimClick);
    Connect(ID_BUTTON3,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AgenderFrame::OnButton3Click);
    Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&AgenderFrame::OnClose);
    //*)

    #ifdef _WXMSW__
    wxRegKey key;
    key.SetName(_T("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
    if (!key.HasValue(_T("Agender")))
    {
        key.Create();
        key.SetValue(_T("Agender"),wxStandardPaths::Get().GetExecutablePath());
    }
    #endif
    schFile = wxStandardPaths::Get().GetUserConfigDir() + _T("/.Agender-current user.txt");
    if (wxFile::Exists(schFile))
    {
    	wxFileInputStream infile(schFile);
        schdl = new wxFileConfig(infile);
    }
    else
    {
        schdl = new wxFileConfig;
    }
    schdl->Write(_T("AgenderMessage"),_("Agender uses this file to save your schedule, don't delete it!"));
    prevDate = CalendarCtrl1->GetDate().Format(_T("%Y-%m-%j"));
    SetTransparent(schdl->Read(_T("/opacity"),255));
    prevSel = wxNOT_FOUND;
    trayicon = new AgenderTray(this,schdl->Read(_T("/opacity"),255));
    trayicon->SetIcon(Agender16x16_xpm,_T("Virtuosonic Agender"));

    if (schdl->HasGroup(CalendarCtrl1->GetDate().Format(_T("%Y-%m-%d"))))
    {
    	schdl->SetPath(_T("/") + CalendarCtrl1->GetDate().Format(_T("%Y-%m-%d/")));
    	wxString nota;
    	long j;
    	schdl->GetFirstEntry(nota,j);
    	ListBox1->Append(nota);
        msgs.Add(schdl->Read(nota,wxEmptyString));
    	for (unsigned int i = 1;i < schdl->GetNumberOfEntries();i++)
    	{
    		schdl->GetNextEntry(nota,j);
    		ListBox1->Append(nota);
    		msgs.Add(schdl->Read(nota,wxEmptyString));
    	}
    	if (schdl->GetNumberOfEntries())
    	{
    		ListBox1->SetSelection(0);
            prevSel = ListBox1->GetSelection();
            TextCtrl1->ChangeValue(msgs[prevSel]);
            TextCtrl1->Enable();
    	}
    	schdl->SetPath(_T("/"));
    }
    MarkDays();

    //parece que esto no funciona en gtk+
    wxAcceleratorEntry entries[1];
    entries[0].Set(wxACCEL_CTRL,(int)"F",wxID_FIND);
    wxAcceleratorTable accel(1, entries);
    this->SetAcceleratorTable(accel);
    fndDlg = NULL;
}

AgenderFrame::~AgenderFrame()
{
    schdl->Write(_T("/bgcolour"),GetBackgroundColour().GetAsString(wxC2S_HTML_SYNTAX));
    schdl->Write(_T("/opacity"),trayicon->GetAlpha());
    if (ListBox1->GetSelection() !=wxNOT_FOUND)
    {
        schdl->Write(CalendarCtrl1->GetDate().Format(_T("%Y-%m-%d/")) +
                                _T("/") + ListBox1->GetStringSelection(),
                                TextCtrl1->GetValue());
    }
    wxFileOutputStream ofile(schFile);
    schdl->Save(ofile);
    //delete
    delete schdl;
    delete trayicon;
    //(*Destroy(AgenderFrame)
    //*)
}

void AgenderFrame::OnClose(wxCloseEvent& event)
{
    Hide();
}

void AgenderFrame::OnButton3Click(wxCommandEvent& event)
{
    wxAboutDialogInfo info;
    info.AddDeveloper(_("Gabriel Espinoza a.k.a. virtuoso"));
    info.SetDescription(_("A cross-plataform schedule tool"));
    info.SetWebSite(_T("http://sourceforge.net/projects/agender"));
    info.SetLicence(_("Agender is free software; you can redistribute it and/or modify\n"
        "it under the terms of the GNU General Public License as published by\n"
        "the Free Software Foundation."
        "\n"
        "This program is distributed in the hope that it will be useful,\n"
        "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
        "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
        "GNU General Public License for more details.\n"
        "\n"
        "You should have received a copy of the GNU General Public License along\n"
        "with this program; if not, write to the Free Software Foundation, Inc.,\n"
        "51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.\n"
        ));
    info.SetVersion(wxString(AutoVersion::FULLVERSION_STRING,wxConvUTF8) +
                                    _T("\n") +
                                    wxString(AutoVersion::DATE,wxConvUTF8) +
                                    _T("-") +
                                    wxString(AutoVersion::MONTH,wxConvUTF8) +
                                    _T("-") +
                                    wxString(AutoVersion::YEAR,wxConvUTF8));
    info.SetIcon(agender_xpm);

    wxAboutBox(info);
}

void AgenderFrame::OnCalendarCtrl1Changed(wxCalendarEvent& event)
{
    if (ListBox1->GetSelection() != wxNOT_FOUND)
    {
    	schdl->Write(prevDate + _T("/") + ListBox1->GetStringSelection(),TextCtrl1->GetValue());
    }
    ListBox1->Clear();
    TextCtrl1->Disable();
    msgs.Clear();
    if (schdl->HasGroup(CalendarCtrl1->GetDate().Format(_T("%Y-%m-%d"))))
    {
    	schdl->SetPath(_T("/") + CalendarCtrl1->GetDate().Format(_T("%Y-%m-%d/")));
    	wxString nota;
    	long j;
    	schdl->GetFirstEntry(nota,j);
    	ListBox1->Append(nota);
        msgs.Add(schdl->Read(nota,wxEmptyString));
    	for (unsigned int i = 1;i < schdl->GetNumberOfEntries();i++)
    	{
    		schdl->GetNextEntry(nota,j);
    		ListBox1->Append(nota);
    		msgs.Add(schdl->Read(nota,wxEmptyString));
    	}
    	if (schdl->GetNumberOfEntries())
    	{
    		ListBox1->SetSelection(0);
            prevSel = ListBox1->GetSelection();
            TextCtrl1->ChangeValue(msgs[prevSel]);
            TextCtrl1->Enable();
    	}
    	schdl->SetPath(_T("/"));
    }
    else
    {
        prevSel = wxNOT_FOUND;
        TextCtrl1->Clear();
    }
    wxFileOutputStream ofile(schFile);
    schdl->Save(ofile);
    prevDate = CalendarCtrl1->GetDate().Format(_T("%Y-%m-%d"));
}

void AgenderFrame::OnListBox1Select(wxCommandEvent& event)
{
    if (ListBox1->GetSelection() != wxNOT_FOUND)
    {
        savePastNote();
        TextCtrl1->Enable();
        TextCtrl1->ChangeValue(msgs[ListBox1->GetSelection()]);
        prevSel = ListBox1->GetSelection();

        wxFileOutputStream ofile(schFile);
        schdl->Save(ofile);
    }
}

void AgenderFrame::savePastNote()
{
    if (prevSel != wxNOT_FOUND)
                msgs[prevSel] = TextCtrl1->GetValue();
    schdl->Write(CalendarCtrl1->GetDate().Format(_T("%Y-%m-%d")) +
                            _T("/") + ListBox1->GetString(prevSel),
                            TextCtrl1->GetValue());
}

void AgenderFrame::OnBtnNuevoClick(wxCommandEvent& event)
{
    wxTextEntryDialog dlg(this,_("Titulo del Pendiente"),_("Nuevo Pendiente"));
    if (dlg.ShowModal() == wxID_OK)
    {
    	ListBox1->Append(dlg.GetValue());
    	ListBox1->SetSelection(ListBox1->GetCount()-1);
    	savePastNote();
    	TextCtrl1->Enable();
    	TextCtrl1->Clear();
    	prevSel = ListBox1->GetSelection();
    	wxFileOutputStream ofile(schFile);
        schdl->Save(ofile);
        msgs.Add(wxEmptyString);
        MarkDays();
    }
}

void AgenderFrame::OnBtnElimClick(wxCommandEvent& event)
{
    if (ListBox1->GetSelection() != wxNOT_FOUND)
    {
    	msgs.RemoveAt(ListBox1->GetSelection());
    	schdl->DeleteEntry(CalendarCtrl1->GetDate().Format(_T("/%Y-%m-%d/"))
                                            +ListBox1->GetStringSelection());
        ListBox1->Delete(ListBox1->GetSelection());
        prevSel = wxNOT_FOUND;
        TextCtrl1->Clear();
        TextCtrl1->Disable();
        if ( !ListBox1->GetCount())
                MarkDays();
    }
}

void AgenderFrame::SetNotesColour(wxColour colour)
{
    schdl->Write(_T("/notescolour"),colour.GetAsString(wxC2S_HTML_SYNTAX));
    MarkDays();
    Refresh();
}


void AgenderFrame::OnCalendarCtrl1MonthChanged(wxCalendarEvent& event)
{
    MarkDays();
}

void AgenderFrame::MarkDays()
{
    wxString dateStr;
    size_t count = 1 + wxDateTime::GetNumberOfDays(CalendarCtrl1->GetDate().GetMonth());
    for (size_t i = 1;i < count; i++)
    {
    	CalendarCtrl1->ResetAttr(i);
        if (i < 10)
        {
        	dateStr = CalendarCtrl1->GetDate().Format(_("%Y-%m-")) +
                            wxString::Format(_T("0%i"),i);
        }
        else
        {
            dateStr = CalendarCtrl1->GetDate().Format(_("%Y-%m-")) +
                            wxString::Format(_T("%i"),i);
        }
        if (!dateStr.IsEmpty() && schdl->HasGroup(dateStr))
        {
            wxCalendarDateAttr* note_attr = new wxCalendarDateAttr;
            note_attr->SetTextColour(wxColour(schdl->Read(_T("/notescolour"),_T("#ff0000"))));
            CalendarCtrl1->SetAttr(i,note_attr);
        }
    }
}

void AgenderFrame::OnFind(wxFindDialogEvent& event)
{
    wxLogMessage(_T(" Not Found!"));
}

void AgenderFrame::OnSearch(wxCommandEvent& event)
{
    if (!fndDlg)
    {
    	fndDlg=new wxFindReplaceDialog(this,&fndData,_("Agender| Buscar"),wxFR_NOUPDOWN|wxFR_NOMATCHCASE|wxFR_NOWHOLEWORD);
        fndDlg->Show();
    }
}

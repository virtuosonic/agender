/***************************************************************
 * Name:      AgenderMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Gabriel Espinoza
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifdef __BORLANDC__
//for those who can't change turboc++, like theacher Nancy
#pragma hdrstop
#endif

#include <wx/msgdlg.h>
#include <wx/defs.h>
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/string.h>
#include <wx/aboutdlg.h>
#include <wx/accel.h>
#include <wx/textdlg.h>
#include <wx/menu.h>
#include <wx/stdpaths.h>
#include <wx/wfstream.h>
#include <wx/utils.h>
#include <wx/filename.h>
#include <wx/log.h>
#include <wx/config.h>
#include <wx/dirdlg.h>
#include <wx/file.h>

#if defined wxHAS_TASK_BAR_ICON
#include "AgenderTray.h"
#endif

#include "AgenderMain.h"
#include "AgenderCal.h"
#include "AboutDialog.h"

#ifndef __REVISION__
#define __REVISION__ 0
#endif


namespace Agender {

#include "Agender16x16.xpm"

//(*IdInit(AgenderFrame)
const long AgenderFrame::ID_CALENDARCTRL1 = wxNewId();
const long AgenderFrame::ID_LISTBOX1 = wxNewId();
const long AgenderFrame::ID_TEXTCTRL1 = wxNewId();
const long AgenderFrame::ID_BUTTON1 = wxNewId();
const long AgenderFrame::ID_BUTTON2 = wxNewId();
const long AgenderFrame::ID_UPDATE_FOUND = wxNewId();
//*)

BEGIN_EVENT_TABLE(AgenderFrame,wxFrame)
	EVT_FIND(wxID_ANY,AgenderFrame::OnFind)
	EVT_FIND_NEXT(wxID_ANY,AgenderFrame::OnFind)
	EVT_MENU(wxID_FIND,AgenderFrame::OnSearch)
	EVT_MENU(7004,AgenderFrame::OnChangeNotesColour)
	EVT_MENU(7003,AgenderFrame::OnYearSel)
	EVT_MENU(ID_RENAME,AgenderFrame::OnMenuRename)
	EVT_MENU_RANGE(ID_NORMAL,ID_STICKY,AgenderFrame::OnMenuNoteFlag)
	EVT_ACTIVATE(AgenderFrame::OnActivate)
	EVT_MENU(wxID_CLOSE,AgenderFrame::OnEscape)
	EVT_MENU(ID_UPDATE_FOUND,AgenderFrame::OnUpdateFound)
	EVT_MENU(wxID_EXIT,AgenderFrame::OnQuit)
	//(*EventTable(AgenderFrame)
	//*)
END_EVENT_TABLE()

AgenderFrame::AgenderFrame(wxLocale& locale,wxString cfgFile):m_locale(locale)
{
	// TODO (virtuoso#5#): compatibilidad wx-2.9: opcion de usar wxGenericCalenderCtrl en vez de wxCalenderCtrl
	//(*Initialize(AgenderFrame)
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(0, wxID_ANY, _("Agender"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxRESIZE_BORDER|wxCLOSE_BOX|wxFRAME_TOOL_WINDOW|wxTAB_TRAVERSAL, _T("wxID_ANY"));
#ifdef __WXMSW__
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUBAR));
#endif
	FlexGridSizer1 = new wxFlexGridSizer(0, 2, 0, 0);
	FlexGridSizer1->AddGrowableCol(0);
	FlexGridSizer1->AddGrowableRow(0);
	FlexGridSizer1->AddGrowableRow(1);
	CalendarCtrl1 = new wxCalendarCtrl(this, ID_CALENDARCTRL1, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, wxCAL_SEQUENTIAL_MONTH_SELECTION|wxSUNKEN_BORDER, _T("ID_CALENDARCTRL1"));
	FlexGridSizer1->Add(CalendarCtrl1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	ListBox1 = new wxListBox(this, ID_LISTBOX1, wxDefaultPosition, wxDefaultSize, 0, 0, 0, wxDefaultValidator, _T("ID_LISTBOX1"));
	FlexGridSizer1->Add(ListBox1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	TextCtrl1 = new wxTextCtrl(this, ID_TEXTCTRL1, wxEmptyString, wxDefaultPosition, wxDefaultSize, wxTE_MULTILINE|wxTE_AUTO_URL, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	TextCtrl1->Disable();
	FlexGridSizer1->Add(TextCtrl1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	BoxSizer1 = new wxBoxSizer(wxVERTICAL);
	BtnNuevo = new wxButton(this, ID_BUTTON1, _("Add &note"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON1"));
	BtnNuevo->SetDefault();
	BtnNuevo->SetFocus();
	BoxSizer1->Add(BtnNuevo, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	BtnElim = new wxButton(this, ID_BUTTON2, _("&Delete selection"), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("ID_BUTTON2"));
	BoxSizer1->Add(BtnElim, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	Button3 = new wxButton(this, wxID_ABOUT, _("&About..."), wxDefaultPosition, wxDefaultSize, 0, wxDefaultValidator, _T("wxID_ABOUT"));
	BoxSizer1->Add(Button3, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 0);
	FlexGridSizer1->Add(BoxSizer1, 1, wxALL|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->Fit(this);
	FlexGridSizer1->SetSizeHints(this);
	Center();

	Connect(ID_CALENDARCTRL1,wxEVT_CALENDAR_SEL_CHANGED,(wxObjectEventFunction)&AgenderFrame::OnCalendarCtrl1Changed);
	Connect(ID_CALENDARCTRL1,wxEVT_CALENDAR_MONTH_CHANGED,(wxObjectEventFunction)&AgenderFrame::OnCalendarCtrl1MonthChanged);
	Connect(ID_CALENDARCTRL1,wxEVT_CALENDAR_YEAR_CHANGED,(wxObjectEventFunction)&AgenderFrame::OnCalendarCtrl1MonthChanged);
	Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_SELECTED,(wxObjectEventFunction)&AgenderFrame::OnListBox1Select);
	Connect(ID_LISTBOX1,wxEVT_COMMAND_LISTBOX_DOUBLECLICKED,(wxObjectEventFunction)&AgenderFrame::OnListBox1DClick);
	Connect(ID_TEXTCTRL1,wxEVT_COMMAND_TEXT_UPDATED,(wxObjectEventFunction)&AgenderFrame::OnTextCtrl1Text);
	Connect(ID_BUTTON1,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AgenderFrame::OnBtnNuevoClick);
	Connect(ID_BUTTON2,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AgenderFrame::OnBtnElimClick);
	Connect(wxID_ABOUT,wxEVT_COMMAND_BUTTON_CLICKED,(wxObjectEventFunction)&AgenderFrame::OnButton3Click);
	Connect(wxID_ANY,wxEVT_CLOSE_WINDOW,(wxObjectEventFunction)&AgenderFrame::OnClose);
	//*)
	if (!(cfgFile.IsEmpty()))
	{
		schFile=cfgFile;
	}
	else
	{
		wxFileName schFname;
		schFname.AssignDir(wxStandardPaths::Get().GetUserConfigDir());
		schFname.SetName(_T(".Agender-current user.txt"));
		schFile = schFname.GetFullPath();
	}
	if (wxFileExists(schFile))
	{
		wxFileInputStream infile(schFile);
		schdl = new wxFileConfig(infile);
		::wxCopyFile(schFile,schFile+_T(".bak"));
		wxLogVerbose(_T("config loaded from: %s"),schFile.c_str());
	}
	else
		schdl = new wxFileConfig;
	wxConfig::Set(schdl);
	a_cal = new AgenderCal(wxDateTime::Now(),schdl);
	//update
	UpdateNotesList();
	ChangeSelector();
	MarkDays();
	//shortcuts
	wxAcceleratorEntry entries[5];
	entries[0].Set(wxACCEL_CTRL,(int)'f',wxID_FIND);
	entries[1].Set(wxACCEL_NORMAL,WXK_ESCAPE,wxID_CLOSE);
	// TODO (virtuoso#5#): use for cut
	entries[2].Set(wxACCEL_CTRL,(int)'x',wxID_ANY);
	entries[3].Set(wxACCEL_CTRL,(int)'q',wxID_EXIT);
	entries[4].Set(wxACCEL_CTRL,(int)'n',ID_BUTTON1);
	wxAcceleratorTable accel(5, entries);
	this->SetAcceleratorTable(accel);
	//find dialog
	fndData = new wxFindReplaceData;
	fndDlg = new wxFindReplaceDialog(this,fndData,_("Agender|Search Notes"),wxFR_NOUPDOWN|wxFR_NOMATCHCASE|wxFR_NOWHOLEWORD);
	SearchMode = false;
	//size
	SetSize(wxConfig::Get()->Read(_T("/x"),wxDefaultPosition.x),wxConfig::Get()->Read(_T("/y"),wxDefaultPosition.y),
	        wxConfig::Get()->Read(_T("/w"),wxDefaultSize.x),wxConfig::Get()->Read(_T("/h"),wxDefaultSize.y));
	SetTransparent(wxConfig::Get()->Read(_T("/opacity"),255));
	//taskbaricon
#if defined wxHAS_TASK_BAR_ICON
	trayicon = new AgenderTray(this);
	trayicon->SetIcon(Agender16x16_xpm,_T("Virtuosonic Agender"));
#endif//wxHAS_TASK_BAR_ICON
}

AgenderFrame::~AgenderFrame()
{
	wxLogMessage(_T("destroying AgenderFrame"));
	wxConfig::Get()->Write(_T("/x"),GetPosition().x);
	wxConfig::Get()->Write(_T("/y"),GetPosition().y);
	wxConfig::Get()->Write(_T("/w"),GetSize().x);
	wxConfig::Get()->Write(_T("/h"),GetSize().y);
	wxFileOutputStream ofile(schFile);
	schdl->Save(ofile);
	wxConfig::Set(NULL);
	//delete
#if defined wxHAS_TASK_BAR_ICON
	delete trayicon;
#endif
	delete schdl;
	delete a_cal;
	//(*Destroy(AgenderFrame)
	//*)
}

void AgenderFrame::OnClose(wxCloseEvent& WXUNUSED(event))
{
	Hide();
	wxConfig::Get()->Write(_T("/x"),GetPosition().x);
	wxConfig::Get()->Write(_T("/y"),GetPosition().y);
	wxConfig::Get()->Write(_T("/w"),GetSize().x);
	wxConfig::Get()->Write(_T("/h"),GetSize().y);
}

void AgenderFrame::OnButton3Click(wxCommandEvent& WXUNUSED(event))
{
	//about dialog!
	wxAboutDialogInfo info;
	//developer a.k.a. me
	//sound
	info.AddArtist(_T("xyzr_kx from Freesound Project: alarm_clock.wav"));
	//etc
	info.SetDescription(wxString::Format(_T("%s\n%s %s %s\n%s %i"),_("A cross-platform schedule tool"),
	                                     _("Build:"),__TDATE__,__TTIME__,_("Revision:"),__REVISION__));
	info.SetWebSite(_T("http://agender.sourceforge.net"),_("Agender Web Site"));
	info.SetLicence(_("Agender is free software; you can redistribute it and/or modify\n\
it under the terms of the GNU General Public License as published by\n\
the Free Software Foundation, either version 3 of the License, or\n\
(at your option) any later version.\n\
\n\
Agender is distributed in the hope that it will be useful,\n\
but WITHOUT ANY WARRANTY; without even the implied warranty of\n\
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n\
GNU General Public License for more details.\n\
\n\
You should have received a copy of the GNU General Public License\n\
along with Agender. If not, see <http://www.gnu.org/licenses/>."));
	info.SetVersion(wxString::FromAscii(FULLVERSION_STRING));
	info.SetCopyright(_T("Copyright (C) 2009-2011 Gabriel Espinoza"));
	AboutDialog dlg(info,this);
	dlg.ShowModal();
}

void AgenderFrame::OnCalendarCtrl1Changed(wxCalendarEvent& WXUNUSED(event))
{
	ListBox1->Clear();
	a_cal->SetDate(CalendarCtrl1->GetDate());
	UpdateNotesList();
	wxFileOutputStream ofile(schFile);
	schdl->Save(ofile);
}

void AgenderFrame::OnListBox1Select(wxCommandEvent& WXUNUSED(event))
{
	if (ListBox1->GetSelection() != wxNOT_FOUND)
	{
		TextCtrl1->Enable();
		TextCtrl1->ChangeValue(a_cal->GetNoteText(ListBox1->GetStringSelection()));
		wxFileOutputStream ofile(schFile);
		schdl->Save(ofile);
	}
}

void AgenderFrame::OnBtnNuevoClick(wxCommandEvent& WXUNUSED(event))
{
	//ask for note title, if empty ignore else create
	wxTextEntryDialog dlg(this,_("To-Do Title"),_("New To-Do"));
	if (dlg.ShowModal() == wxID_OK  && dlg.GetValue() != wxEmptyString)
	{
		if (dlg.GetValue().Find(_T("$(")) != wxNOT_FOUND)
		{
			wxMessageBox(_("Expresion '$(' reserved for Agender, please use another name"),
			             _T("Error"),wxICON_ERROR,this);
			return;
		}
		else if (a_cal->HasNote(dlg.GetValue()))
			return;
		//add
		ListBox1->Append(dlg.GetValue());
		ListBox1->SetSelection(ListBox1->GetCount()-1);
		TextCtrl1->Enable();
		TextCtrl1->ChangeValue(wxEmptyString);
		a_cal->SetNoteText(dlg.GetValue(),wxEmptyString);
		wxFileOutputStream ofile(schFile);
		schdl->Save(ofile);
		MarkDays();
	}
}

void AgenderFrame::OnBtnElimClick(wxCommandEvent& WXUNUSED(event))
{
	//remove selection
	if (ListBox1->GetSelection() != wxNOT_FOUND)
	{
		a_cal->RmNote(ListBox1->GetStringSelection());
		ListBox1->Delete(ListBox1->GetSelection());
		TextCtrl1->ChangeValue(wxEmptyString);
		TextCtrl1->Disable();
		MarkDays();
	}
}

void AgenderFrame::OnChangeNotesColour(wxCommandEvent& event)
{
	//called by tray icon
	wxConfig::Get()->Write(_T("/notescolour"),event.GetString());
	MarkDays();
	Refresh();
}


void AgenderFrame::OnCalendarCtrl1MonthChanged(wxCalendarEvent& WXUNUSED(event))
{
	a_cal->SetDate(CalendarCtrl1->GetDate());
	MarkDays();
}

void AgenderFrame::MarkDays()
{
	///reset all days attributes
	unsigned int i;
	for (i = 0;
	        i < wxDateTime::GetNumberOfDays(CalendarCtrl1->GetDate().GetMonth());
	        i++)
		CalendarCtrl1->ResetAttr(i+1);
	///get day with notes
	wxArrayInt days =  a_cal->GetDaysWithNotes();
	///mark that days
	for (i = 0; i < days.GetCount(); i++)
	{
		wxCalendarDateAttr* note_attr = new wxCalendarDateAttr;
		note_attr->SetTextColour(wxColour(wxConfig::Get()->Read(_T("/notescolour"),_T("#00FF00"))));
		CalendarCtrl1->SetAttr(days[i],note_attr);
	}
	///mark today
	if (wxDateTime::Now().GetMonth() == CalendarCtrl1->GetDate().GetMonth())
	{
		wxCalendarDateAttr* today_attr = CalendarCtrl1->GetAttr(wxDateTime::Now().GetDay());
		if (today_attr == NULL)
		{
			today_attr = new wxCalendarDateAttr;
			today_attr->SetBorder(wxCAL_BORDER_ROUND);
			today_attr->SetBorderColour(wxColour(wxConfig::Get()->Read(_T("/notescolour"),_T("#00ff00"))));
			CalendarCtrl1->SetAttr(wxDateTime::Now().GetDay(),today_attr);
		}
	}
}

void AgenderFrame::OnFind(wxFindDialogEvent& event)
{
	//missing!
	event.GetFindString();
}

void AgenderFrame::OnSearch(wxCommandEvent& WXUNUSED(event))
{
	//missing!
	if (!fndDlg->IsShown())
		fndDlg->Show();
}

void AgenderFrame::OnYearSel(wxCommandEvent& WXUNUSED(event))
{
	ChangeSelector();
}

void AgenderFrame::ChangeSelector()
{
	bool yearSel = false;
	wxConfig::Get()->Read(_T("/yearselector"),&yearSel);
	int style;
	wxDateTime date(CalendarCtrl1->GetDate());
	if (yearSel)
		style = wxSUNKEN_BORDER|wxTAB_TRAVERSAL;
	else
		style = wxCAL_SEQUENTIAL_MONTH_SELECTION|wxSUNKEN_BORDER|wxTAB_TRAVERSAL;
	wxCalendarCtrl* calendar = new wxCalendarCtrl(this, ID_CALENDARCTRL1, wxDefaultDateTime, wxDefaultPosition, wxDefaultSize, style, _T("ID_CALENDARCTRL1"));
	GetSizer()->Replace(CalendarCtrl1,calendar);
	delete CalendarCtrl1;
	CalendarCtrl1 = calendar;
	GetSizer()->Layout();
	GetSizer()->Fit(this);
	CalendarCtrl1->SetDate(date);
	MarkDays();
}

void AgenderFrame::OnTextCtrl1Text(wxCommandEvent& WXUNUSED(event))
{
	a_cal->SetNoteText(ListBox1->GetStringSelection(),TextCtrl1->GetValue());
}

void AgenderFrame::OnListBox1DClick(wxCommandEvent& WXUNUSED(event))
{
	//double click on a listbox item pops a menu
	wxMenu* noteMenu = new wxMenu;
	noteMenu->Append(ID_RENAME,_("Rename"));
	noteMenu->AppendSeparator();
	noteMenu->AppendRadioItem(ID_NORMAL,_("Normal"));
	noteMenu->AppendRadioItem(ID_STICKY,_("Sticky"));
	if (a_cal->IsSticky(ListBox1->GetStringSelection()))
		noteMenu->Check(ID_STICKY,true);
	ListBox1->PopupMenu(noteMenu);
}

void AgenderFrame::OnMenuNoteFlag(wxCommandEvent& event)
{
	switch (event.GetId())
	{
		case ID_NORMAL:
			a_cal->UnStick(ListBox1->GetStringSelection());
			ListBox1->SetString(ListBox1->GetSelection(),ListBox1->GetStringSelection().BeforeLast('$'));
			MarkDays();
			break;
		case ID_STICKY:
			a_cal->MakeSticky(ListBox1->GetStringSelection());
			ListBox1->SetString(ListBox1->GetSelection(),wxString::Format(_T("%s%s"),
			                    ListBox1->GetStringSelection().c_str(),stickSymb));
			MarkDays();
			break;
		default:
			break;
	}
}

void AgenderFrame::OnMenuRename(wxCommandEvent& WXUNUSED(event))
{
	wxString oldName(ListBox1->GetStringSelection());
	bool sticky = false;
	if (oldName.Find(stickSymb) != wxNOT_FOUND)
	{
		oldName = oldName.BeforeLast('$');
		sticky=true;
	}
	wxTextEntryDialog dlg(this,_("New name"),_("Rename"),oldName);
	if (dlg.ShowModal() ==wxID_OK && !oldName.IsSameAs(dlg.GetValue().c_str(),true))
	{
		if (sticky)
		{
			a_cal->RenameNote(ListBox1->GetStringSelection(),dlg.GetValue()+stickSymb);
			ListBox1->SetString(ListBox1->GetSelection(),dlg.GetValue()+stickSymb);
		}
		else
		{
			a_cal->RenameNote(ListBox1->GetStringSelection(),dlg.GetValue());
			ListBox1->SetString(ListBox1->GetSelection(),dlg.GetValue());
		}
	}
}


void AgenderFrame::OnActivate(wxActivateEvent& event)
{
	if (!event.GetActive())
	{
		wxFileOutputStream ofile(schFile);
		schdl->Save(ofile);
	}
}

void AgenderFrame::OnEscape(wxCommandEvent& WXUNUSED(event))
{
	Close();
}

void AgenderFrame::OnUpdateFound(wxCommandEvent& event)
{
	wxLogMessage(_T("creating update dialog"));
	wxMessageDialog dlg(wxTheApp->GetTopWindow(),
	                    wxString::Format(_("The %s version of %s has been released. \
				Do you want to download it?"),event.GetString().c_str(),
	                                     wxTheApp->GetAppName().c_str()),
	                    _("Upgrade Found"),wxYES_NO|wxSTAY_ON_TOP);
	if (dlg.ShowModal() == wxID_YES)
	{
		wxLaunchDefaultBrowser(_T("http://agender.sourceforge.net/index.php?page=Downloads"));
	}
}

void AgenderFrame::UpdateNotesList()
{
	wxArrayString notes = a_cal->GetNotes();
	for (unsigned int i = 0; i < notes.GetCount(); i++)
		ListBox1->Append(notes[i]);
	if (notes.GetCount() > 0)
	{
		ListBox1->SetSelection(0);
		TextCtrl1->Enable();
		TextCtrl1->ChangeValue(a_cal->GetNoteText(ListBox1->GetStringSelection()));
	}
	else
	{
		TextCtrl1->ChangeValue(wxEmptyString);
		ListBox1->Clear();
		TextCtrl1->Disable();
	}
}

void AgenderFrame::OnQuit(wxCommandEvent& WXUNUSED(event))
{
	Destroy();
}
}//namespace Agender

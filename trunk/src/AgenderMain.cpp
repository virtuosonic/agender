/***************************************************************
 * Name:      AgenderMain.cpp
 * Purpose:   Code for Application Frame
 * Author:    Gabriel Espinoza
 * Created:   2008-11-21
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifdef __BORLANDC__
    #pragma hdrstop
#endif

#include "AgenderMain.h"
#include <wx/msgdlg.h>
#include <wx/defs.h>

//(*InternalHeaders(AgenderFrame)
#include <wx/settings.h>
#include <wx/intl.h>
#include <wx/string.h>
//*)

#include <wx/aboutdlg.h>
#include <wx/accel.h>
#include <wx/textdlg.h>
#include <wx/choicdlg.h>
#include <wx/menu.h>
#include <wx/stdpaths.h>
#include <wx/wfstream.h>
#include <wx/utils.h>
#include <wx/log.h>
#include <wx/filename.h>
#include <wx/app.h>
#include <wx/apptrait.h>

//escribir algunas cosas en el registro
#ifdef __WXMSW__
#include <wx/msw/registry.h>
#endif//__WXMSW__

#ifdef __WXMAC__
#include <ApplicationServices/ApplicationServices.h>
#endif// __WXMAC__

#include "AgenderCal.h"

#if defined wxHAS_TASK_BAR_ICON
#include "AgenderTray.h"
#endif

#include "Agender16x16.xpm"
#include "Agender.xpm"

//(*IdInit(AgenderFrame)
const long AgenderFrame::ID_CALENDARCTRL1 = wxNewId();
const long AgenderFrame::ID_LISTBOX1 = wxNewId();
const long AgenderFrame::ID_TEXTCTRL1 = wxNewId();
const long AgenderFrame::ID_BUTTON1 = wxNewId();
const long AgenderFrame::ID_BUTTON2 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AgenderFrame,wxFrame)
	EVT_FIND(wxID_ANY,AgenderFrame::OnFind)
	EVT_FIND_NEXT(wxID_ANY,AgenderFrame::OnFind)
	EVT_MENU(wxID_FIND,AgenderFrame::OnSearch)
	EVT_MENU(7004,AgenderFrame::OnChangeNotesColour)
	EVT_MENU(7003,AgenderFrame::OnYearSel)
	EVT_MENU(7005,AgenderFrame::OnAutoStart)
	EVT_MENU(ID_RENAME,AgenderFrame::OnMenuRename)
	EVT_MENU_RANGE(ID_NORMAL,ID_STICKY,AgenderFrame::OnMenuNoteFlag)
	EVT_ACTIVATE(AgenderFrame::OnActivate)
	EVT_MENU(wxID_CLOSE,AgenderFrame::OnEscape)
	//(*EventTable(AgenderFrame)
	//*)
END_EVENT_TABLE()

AgenderFrame::AgenderFrame(wxLocale& locale,wxString cfgFile):m_locale(locale)
{
	// TODO (virtuoso#1#): compatibilidad wx-2.9: opcion de usar wxGenericCalenderCtrl en vez de wxCalenderCtrl
	//(*Initialize(AgenderFrame)
	wxBoxSizer* BoxSizer1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(0, wxID_ANY, _("Agender"), wxDefaultPosition, wxDefaultSize, wxCAPTION|wxSYSTEM_MENU|wxRESIZE_BORDER|wxCLOSE_BOX|wxFRAME_TOOL_WINDOW|wxTAB_TRAVERSAL|wxWANTS_CHARS, _T("wxID_ANY"));
	SetBackgroundColour(wxSystemSettings::GetColour(wxSYS_COLOUR_MENUBAR));
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
	if (wxFileExists(cfgFile))
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
		wxLogMessage(_T("config loaded from: %s"),schFile.c_str());
	}
	else
		schdl = new wxFileConfig;
	wxConfig::Set(schdl);
	schdl->Write(_T("/AgenderMessage"),_("Agender uses this file to save your schedule, don't delete it!"));
	a_cal = new AgenderCal(CalendarCtrl1->GetDate());
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
		TextCtrl1->Disable();
	ChangeSelector();
	MarkDays();
	//shortcuts
	wxAcceleratorEntry entries[3];
	entries[0].Set(wxACCEL_CTRL,(int)'f',wxID_FIND);
	entries[1].Set(wxACCEL_NORMAL,WXK_ESCAPE,wxID_CLOSE);
	// TODO (virtuoso#1#): use for cut
	entries[2].Set(wxACCEL_CTRL,(int)'x',wxID_ANY);
	wxAcceleratorTable accel(3, entries);
	this->SetAcceleratorTable(accel);
	//find dialog
	fndData = new wxFindReplaceData;
	fndDlg = new wxFindReplaceDialog(this,fndData,_("Agender|Search Notes"),wxFR_NOUPDOWN|wxFR_NOMATCHCASE|wxFR_NOWHOLEWORD);
	SearchMode = false;
	//size
	SetSize(schdl->Read(_T("/x"),wxDefaultPosition.x),schdl->Read(_T("/y"),wxDefaultPosition.y),
		  schdl->Read(_T("/w"),wxDefaultSize.x),schdl->Read(_T("/h"),wxDefaultSize.y));
	SetTransparent(schdl->Read(_T("/opacity"),255));
	//autostart
	wxCommandEvent event;
	event.SetId(7005);
	wxPostEvent(GetEventHandler(),event);
	//taskbaricon
#if defined wxHAS_TASK_BAR_ICON
	//this is a stupid hack, but gnome is a very stupid desktop environment
#if defined __X__ || defined __WXGTK__
	wxArrayString output;
	wxExecute(_T("pidof gnome-session"),output,wxEXEC_SYNC);
	if (!output.IsEmpty()) {
		output.Empty();
		do
		{
			wxExecute(_T("pidof gnome-panel"),output,wxEXEC_SYNC);
			if (output.IsEmpty())
				wxSleep(3);
		} while(output.IsEmpty());
		wxSleep(3);
	}
#endif
	trayicon = new AgenderTray(this,schdl->Read(_T("/opacity"),255));
	trayicon->SetIcon(Agender16x16_xpm,_T("Virtuosonic Agender"));
#endif//wxHAS_TASK_BAR_ICON
#ifdef __WXMAC__
	//this isn't tested, but i read it in wxwiki
	//if you want me to test it, and make it work,  you can donate me a Mac Pro ;)	-virtuosonic at users dot sourceforge dot net
	ProcessSerialNumber PSN;
	GetCurrentProcess(&PSN);
	TransformProcessType(&PSN,kProcessTransformToForegroundApplication);
#endif// __WXMAC__
}

AgenderFrame::~AgenderFrame()
{
	wxLogDebug(_T("destroying AgenderFrame"));
	schdl->Write(_T("/x"),GetPosition().x);
	schdl->Write(_T("/y"),GetPosition().y);
	schdl->Write(_T("/w"),GetSize().x);
	schdl->Write(_T("/h"),GetSize().y);
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

void AgenderFrame::OnClose(wxCloseEvent& event)
{
	Hide();
	schdl->Write(_T("/x"),GetPosition().x);
	schdl->Write(_T("/y"),GetPosition().y);
	schdl->Write(_T("/w"),GetSize().x);
	schdl->Write(_T("/h"),GetSize().y);
}

void AgenderFrame::OnButton3Click(wxCommandEvent& event)
{
	wxAboutDialogInfo info;
	//developer
	info.AddDeveloper(_T("Gabriel Espinoza <virtuosonic@users.sourceforge.net>"));
	//translators
	info.AddTranslator(_T("Gabriel Espinoza : español"));
	info.AddTranslator(_T("Ester Espinoza : deutsch"));
	info.AddTranslator(_T("Florian Haag <fhaag@users.sourceforge.net> : deutsch"));
	info.AddTranslator(_T("Daniel Daows : japanese"));
	info.AddTranslator(_T("Miguel Haruki Yamaguchi <mhy@users.sourceforge.net> : japanese"));
	info.AddTranslator(_T("Pedro Silva <pbsilva@users.sourceforge.net> : portuguese"));
	//etc
	info.SetDescription(wxString::Format(_T("%s\n%s %s %s"),_("A cross-platform schedule tool"),
							 _("Build:"),__TDATE__,__TTIME__));
	info.SetWebSite(_T("http://agender.sourceforge.net"),_("Agender Web Site"));
	info.SetLicence(_("Agender is free software; you can redistribute it and/or modify\n"
				"it under the terms of the GNU General Public License as published by\n"
				"the Free Software Foundation, either version 3 of the License, or\n"
				"(at your option) any later version.\n"
				"\n"
				"Agender is distributed in the hope that it will be useful,\n"
				"but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
				"MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
				"GNU General Public License for more details.\n"
				"\n"
				"You should have received a copy of the GNU General Public License\n"
				"along with Agender. If not, see <http://www.gnu.org/licenses/>."));
	info.SetVersion(_T("1.1.6"));
	info.SetCopyright(_T("Copyright (C) 2009-2010 Gabriel Espinoza"));
	info.SetIcon(agender_xpm);
	wxAboutBox(info);
}

void AgenderFrame::OnCalendarCtrl1Changed(wxCalendarEvent& event)
{
	ListBox1->Clear();
	TextCtrl1->ChangeValue(wxEmptyString);
	a_cal->SetDate(CalendarCtrl1->GetDate());
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
		TextCtrl1->Disable();
	wxFileOutputStream ofile(schFile);
	schdl->Save(ofile);
}

void AgenderFrame::OnListBox1Select(wxCommandEvent& event)
{
	if (ListBox1->GetSelection() != wxNOT_FOUND)
	{
		TextCtrl1->Enable();
		TextCtrl1->ChangeValue(a_cal->GetNoteText(ListBox1->GetStringSelection()));
		wxFileOutputStream ofile(schFile);
		schdl->Save(ofile);
	}
}

void AgenderFrame::OnBtnNuevoClick(wxCommandEvent& event)
{
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

void AgenderFrame::OnBtnElimClick(wxCommandEvent& event)
{
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
	schdl->Write(_T("/notescolour"),event.GetString());
	MarkDays();
	Refresh();
}


void AgenderFrame::OnCalendarCtrl1MonthChanged(wxCalendarEvent& event)
{
	a_cal->SetDate(CalendarCtrl1->GetDate());
	MarkDays();
}

void AgenderFrame::MarkDays()
{
	///reset all days attributes
	for (unsigned int i = 0;
			i < wxDateTime::GetNumberOfDays(CalendarCtrl1->GetDate().GetMonth());
			i++)
		CalendarCtrl1->ResetAttr(i+1);
	///get day with notes
	wxArrayInt days =  a_cal->GetDaysWithNotes();
	///mark that days
	for (unsigned int i = 0; i < days.GetCount(); i++)
	{
		wxCalendarDateAttr* note_attr = new wxCalendarDateAttr;
		note_attr->SetTextColour(wxColour(schdl->Read(_T("/notescolour"),_T("#00FF00"))));
		CalendarCtrl1->SetAttr(days[i],note_attr);
	}
	if (wxDateTime::Now().GetMonth() == CalendarCtrl1->GetDate().GetMonth())
	{
		wxCalendarDateAttr* today_attr = CalendarCtrl1->GetAttr(wxDateTime::Now().GetDay());
		if (today_attr == NULL)
		{
			today_attr = new wxCalendarDateAttr;
			CalendarCtrl1->SetAttr(wxDateTime::Now().GetDay(),today_attr);
		}
		today_attr->SetBorder(wxCAL_BORDER_ROUND);
		today_attr->SetBorderColour(wxColour(schdl->Read(_T("/notescolour"),_T("#00ff00"))));
	}
}

void AgenderFrame::OnFind(wxFindDialogEvent& event)
{
	event.GetFindString();
}

void AgenderFrame::OnSearch(wxCommandEvent& event)
{
	if (!fndDlg->IsShown())
		fndDlg->Show();
}

void AgenderFrame::OnYearSel(wxCommandEvent& event)
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

void AgenderFrame::OnAutoStart(wxCommandEvent& event)
{
#if defined __UNIX__ && !defined __APPLE__ //should i simply use __LINUX__ || __BSD__ ? and maybe __SOLARIS__
	//we use freedestop.org standard
	wxFileName desktopFname;
	desktopFname.AssignDir(wxGetHomeDir());
	desktopFname.AppendDir(_T(".config"));
	desktopFname.AppendDir(_T("autostart"));
	desktopFname.SetName(_T("Agender"));
	desktopFname.SetExt(_T("desktop"));
	wxString desktopFile = desktopFname.GetFullPath();
	//fluxbox startup script
	wxFileName fluxFname;
	fluxFname.AssignDir(wxGetHomeDir());
	fluxFname.AppendDir(_T(".fluxbox"));
	fluxFname.SetName(_T("startup"));
	wxString  fluxFile= fluxFname.GetFullPath();
	//existance!
	if (!wxDirExists(desktopFname.GetPath()) && !wxFileExists(fluxFile))
	{
		wxMessageBox(_("AutoStart is only available under Windows, Fluxbox "
				   " and Unix desktops that follow the freedesktop.org standards. "//how sadly! =(
				   "If you add support for any other system, please send patches "
				   "to the patch tracker in the Agender project page at "
				   "http://sourceforge.net/projects/agender/ or you can also help "
				   "donating hardware that runs your favorite system."));
		return;
	}
#elif defined __WXMSW__
	//we use the windows registry
	wxRegKey key;
	key.SetName(_T("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
#else //__WXOSX__ || __WXMAC__
	//we ask for help :)
	wxMessageBox(_("AutoStart is only available under Windows, Fluxbox "
			   " and Unix desktops that follow the freedesktop.org standards. "//how sadly! =(
			   "If you add support for any other system, please send patches "
			   "to the patch tracker in the Agender project page at "
			   "http://sourceforge.net/projects/agender/ or you can also help "
			   "donating hardware that runs your favorite system."));
	return;
#endif
	//add or remove
	bool autostart=false;
	wxConfig::Get()->Read(_T("/autostart"),&autostart,false);
	if (autostart)
	{
		///add
#if defined __UNIX__ && !defined __APPLE__
		//freedesktop.org
		if (!wxFileExists(desktopFile))
		{
			//lets use the easyest way
			wxTextFile desktop;
			desktop.Create(desktopFile);
			desktop.AddLine(_T("[Desktop Entry]"));
			desktop.AddLine(_T("Type=Application"));
			desktop.AddLine(_T("Name=Agender"));
			desktop.AddLine(_T("Exec=Agender"));
			desktop.AddLine(_T("Icon=Agender"));
			desktop.Write(wxTextFileType_Unix);//needed?
			desktop.Close();
		}
		//add a command to run Agender to the fluxbox  startup script
		wxTextFile startflux;
		if (startflux.Open(fluxFile))
		{
			wxString command;
			int indx = -1;
			bool alreadyThere = false;
			for (command = startflux.GetLastLine(); startflux.GetCurrentLine() > 0;
					command = startflux.GetPrevLine())
			{
				if (command.Matches(_T("exec*fluxbox*")))
					indx = startflux.GetCurrentLine();
				if (command.Matches(_T("Agender &")))
					alreadyThere = true;
			}
			if (indx > -1 && !alreadyThere)
			{
				startflux.InsertLine(_T("Agender &"),indx);
				startflux.Write();
			}
			startflux.Close();
		}
#elif defined __WXMSW__
		wxString AgenderValue;
		key.QueryValue(_T("Agender"),AgenderValue);
		if (!key.HasValue(_T("Agender")) || AgenderValue != wxStandardPaths::Get().GetExecutablePath())
			key.SetValue(_T("Agender"),wxStandardPaths::Get().GetExecutablePath());
#endif
	}
	else///remove
#if defined __UNIX__ && !defined __APPLE__
	{
		if (wxFileExists(desktopFile))
			wxRemoveFile(desktopFile);
		//clean fluxbox startup script
		wxTextFile startflux;
		if (startflux.Open(fluxFile))
		{
			wxString command;
			for (command = startflux.GetLastLine(); startflux.GetCurrentLine() > 0;
					command = startflux.GetPrevLine())
			{
				if (command.Matches(_T("Agender &")))
				{
					startflux.RemoveLine(startflux.GetCurrentLine());
					startflux.Write();
				}
			}
			startflux.Close();
		}
	}
#elif defined __WXMSW__
		if (key.HasValue(_T("Agender")))
			key.DeleteValue(_T("Agender"));
#endif
}

void AgenderFrame::OnTextCtrl1Text(wxCommandEvent& event)
{
	a_cal->SetNoteText(ListBox1->GetStringSelection(),TextCtrl1->GetValue());
}

void AgenderFrame::OnListBox1DClick(wxCommandEvent& event)
{
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

void AgenderFrame::OnMenuRename(wxCommandEvent& event)
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

void AgenderFrame::OnEscape(wxCommandEvent& event)
{
	Close();
}

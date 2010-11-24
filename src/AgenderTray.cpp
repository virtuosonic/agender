/***************************************************************
 * Name:      AgenderTray.cpp
 * Purpose:   Code for the tray/notification/taskbar/etc icon
 * Author:    Gabriel Espinoza
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifdef __BORLANDC__
	#pragma hdrstop
#endif

#include <wx/defs.h>

#if defined wxHAS_TASK_BAR_ICON

#include "AgenderTray.h"
#include <wx/colordlg.h>
#include <wx/numdlg.h>
#include <wx/menu.h>
#include <wx/config.h>
#include <wx/app.h>
#include <wx/clipbrd.h>
#include <wx/dataobj.h>
#include <wx/msgdlg.h>
#include <wx/intl.h>
#include <wx/richtext/richtextsymboldlg.h>


BEGIN_EVENT_TABLE(AgenderTray,wxTaskBarIcon)
	EVT_TASKBAR_LEFT_UP(AgenderTray::OnLeft)
	EVT_MENU(ID_SHOW,AgenderTray::OnMenuShow)
	EVT_MENU(ID_HIDE,AgenderTray::OnMenuHide)
	EVT_MENU_RANGE(ID_OPC100,ID_OPC25,AgenderTray::OnMenuOpc)
	EVT_MENU(ID_YEARSEL,AgenderTray::OnYearSel)
	EVT_MENU(ID_NOTES_COLOUR,AgenderTray::OnMenuNotesColour)
	EVT_MENU(wxID_EXIT,AgenderTray::OnMenuExit)
	EVT_MENU(wxID_FIND,AgenderTray::OnMenuFind)
	EVT_MENU(ID_AUTOSTART,AgenderTray::OnMenuAutoStart)
	EVT_MENU(ID_SYMBOL,AgenderTray::OnMenuSymbols)
	EVT_MENU(ID_NOTIFY,AgenderTray::OnMenuNotify)
	EVT_MENU_RANGE(ID_LANG_DEF,ID_LANG_LAST-1,AgenderTray::OnMenuLang)
END_EVENT_TABLE()

AgenderTray::AgenderTray(wxFrame* frame)
{
	this->frame = frame;
	alpha = wxConfig::Get()->Read(_T("/opacity"),255);
	switch (alpha)
	{
		case 255:
			opc = ID_OPC100;
			break;
		case 187:
			opc = ID_OPC75;
			break;
		case 125:
			opc = ID_OPC50;
			break;
		case 62:
			opc = ID_OPC25;
			break;

		default:
			break;
	}
	bool autostart=true;
	wxConfig::Get()->Read(_T("/autostart"),&autostart,true);
	astart.Set(autostart);
}

void AgenderTray::OnLeft(wxTaskBarIconEvent& WXUNUSED(event))
{
	//show the main window
	if (frame->IsShownOnScreen())
	{
		frame->Hide();
	}
	else
	{
		frame->Show();
		frame->SetFocus();
		frame->Raise();
	}
}

wxMenu * AgenderTray::CreatePopupMenu()
{
	//opacity submenu
	wxMenu* opcMenu;
	opcMenu = new wxMenu;
	opcMenu->AppendRadioItem(ID_OPC100,_("100%"));
	opcMenu->AppendRadioItem(ID_OPC75,_("75%"));
	opcMenu->AppendRadioItem(ID_OPC50,_("50%"));
	opcMenu->AppendRadioItem(ID_OPC25,_("25%"));
	opcMenu->Check(opc,true);
	//lang submenu
	wxMenu* lmenu;
	lmenu = new wxMenu;
	lmenu->AppendRadioItem(ID_LANG_DEF,_("default"));
	lmenu->AppendRadioItem(ID_LANG_ES,_("Spanish"));
	lmenu->AppendRadioItem(ID_LANG_DE,_("Deutch"));
	lmenu->AppendRadioItem(ID_LANG_JA,_("Japanese"));
	lmenu->AppendRadioItem(ID_LANG_PT,_("Portuguese"));
	lmenu->AppendRadioItem(ID_LANG_FR,_("French"));
	lmenu->AppendRadioItem(ID_LANG_EL,_("Greek"));
	lmenu->AppendRadioItem(ID_LANG_SV,_("Swedish"));
	lmenu->AppendRadioItem(ID_LANG_ZH_HK,_("Traditional Chinese"));
	lmenu->AppendRadioItem(ID_LANG_ZH_CN,_("Simplified Chinese"));
	lmenu->AppendRadioItem(ID_LANG_RO,_("Romanian"));
	lmenu->AppendRadioItem(ID_LANG_HE,_("Hebrew"));
	long lang = wxConfig::Get()->Read(_T("/lang"),wxLANGUAGE_UNKNOWN);
	switch (lang)
	{
		case wxLANGUAGE_SPANISH:
			lmenu->Check(ID_LANG_ES,true);
			break;
		case wxLANGUAGE_GERMAN:
			lmenu->Check(ID_LANG_DE,true);
			break;
		case wxLANGUAGE_JAPANESE:
			lmenu->Check(ID_LANG_JA,true);
			break;
		case wxLANGUAGE_SWEDISH:
			lmenu->Check(ID_LANG_SV,true);
			break;
		case wxLANGUAGE_FRENCH:
			lmenu->Check(ID_LANG_FR,true);
			break;
		case wxLANGUAGE_PORTUGUESE:
			lmenu->Check(ID_LANG_PT,true);
			break;
		case wxLANGUAGE_GREEK:
			lmenu->Check(ID_LANG_EL,true);
			break;
		case wxLANGUAGE_CHINESE_TRADITIONAL:
			lmenu->Check(ID_LANG_ZH_HK,true);
			break;
		case wxLANGUAGE_CHINESE_SIMPLIFIED:
			lmenu->Check(ID_LANG_ZH_CN,true);
			break;
		case wxLANGUAGE_HEBREW:
			lmenu->Check(ID_LANG_HE,true);
			break;
		case wxLANGUAGE_ROMANIAN:
			lmenu->Check(ID_LANG_RO,true);
			break;
		default:
			break;
	}
	//main menu
	wxMenu* menu;
	menu = new wxMenu;
	menu->Append(ID_SHOW,_("Show"));
	menu->Append(ID_HIDE,_("Hide"));
	menu->AppendSeparator();
	if (frame->CanSetTransparent())
		menu->AppendSubMenu(opcMenu,_("Opacity"));
	menu->AppendCheckItem(ID_YEARSEL,_("Year selector"));
	menu->Append(ID_NOTES_COLOUR,_("Notes Colour"));
	menu->AppendSubMenu(lmenu,_("Language"));
#if wxUSE_RICHTEXT
	menu->Append(ID_SYMBOL,_("Symbol"));
#endif//wxUSE_RICHTEXT
	// TODO (virtuoso#1#): uncoment when implemented in v1.2
	//menu->AppendCheckItem(ID_NOTIFY,_("Notify"));
	menu->AppendCheckItem(ID_AUTOSTART,_("Autostart"));
	menu->AppendSeparator();
	menu->Append(wxID_EXIT,_("Exit"));
	//read value from config
	bool test_bool= false;
	wxConfig::Get()->Read(_T("/yearselector"),&test_bool,false);
	menu->Check(ID_YEARSEL,test_bool);
	wxConfig::Get()->Read(_T("/autostart"),&test_bool,true);
	menu->Check(ID_AUTOSTART,test_bool);
	//wxConfig::Get()->Read(_T("/notify"),&test_bool,false);
	//menu->Check(ID_NOTIFY,test_bool);

	return menu;
}

void AgenderTray::OnMenuExit(wxCommandEvent& WXUNUSED(event))
{
	frame->Destroy();
}

void AgenderTray::OnMenuHide(wxCommandEvent& WXUNUSED(event))
{
	frame->Hide();
}

void AgenderTray::OnMenuShow(wxCommandEvent& WXUNUSED(event))
{
	frame->Show();
	frame->SetFocus();
	frame->Raise();
}

void AgenderTray::OnMenuOpc(wxCommandEvent& event)
{
	opc = event.GetId();
	switch (opc)
	{
		case ID_OPC25:
			alpha = 62;
			break;
		case ID_OPC50:
			alpha = 125;
			break;
		case ID_OPC75:
			alpha = 187;
			break;
		default:
			alpha = 255;
			break;
	}
	frame->SetTransparent(alpha);
	wxConfig::Get()->Write(_T("/opacity"),alpha);
}

void AgenderTray::OnMenuNotesColour(wxCommandEvent& event)
{
	wxColourDialog dlg(frame);
	dlg.GetColourData().SetChooseFull(true);
	if (dlg.ShowModal() == wxID_OK)
	{
		event.SetString(dlg.GetColourData().GetColour().GetAsString(wxC2S_HTML_SYNTAX));
		::wxPostEvent(frame->GetEventHandler(),event);
	}
}

void AgenderTray::OnMenuFind(wxCommandEvent& event)
{
	wxPostEvent(frame->GetEventHandler(),event);
}

void AgenderTray::OnYearSel(wxCommandEvent& event)
{
	wxConfig::Get()->Write(_T("/yearselector"),event.IsChecked());
	wxPostEvent(frame->GetEventHandler(),event);
}

void AgenderTray::OnMenuAutoStart(wxCommandEvent& event)
{
	wxConfig::Get()->Write(_T("/autostart"),event.IsChecked());
	astart.Set(event.IsChecked());
}

void AgenderTray::OnMenuSymbols(wxCommandEvent& WXUNUSED(event))
{
#if wxUSE_RICHTEXT
	wxSymbolPickerDialog dlg(_T("*"),wxEmptyString,
							 wxTheApp->GetTopWindow()->GetFont().GetFaceName(),NULL);
	if (dlg.ShowModal() ==wxID_OK && dlg.HasSelection())
	{
		if (wxTheClipboard->Open())
		{
			wxTheClipboard->SetData(new wxTextDataObject(dlg.GetSymbol()));
			wxTheClipboard->Close();
		}
	}
#endif//wxUSE_RICHTEXT
}

void AgenderTray::OnMenuNotify(wxCommandEvent& event)
{
	if (event.IsChecked())
	{
		wxNumberEntryDialog dlg(wxTheApp->GetTopWindow(),_("Days to notify before note"),_("Days"),
				_("Notify"),1,0,365);
		if (dlg.ShowModal() == wxID_OK)
		{
			wxConfig::Get()->Write(_T("/notify"),true);
		}
	}
	else
		wxConfig::Get()->Write(_T("/notify"),false);
}

void AgenderTray::OnMenuLang(wxCommandEvent& event)
{
	wxLanguage l = wxLANGUAGE_UNKNOWN;
	switch (event.GetId())
	{
		case ID_LANG_DEF:
			l = wxLANGUAGE_DEFAULT;
			break;
		case ID_LANG_ES:
			l = wxLANGUAGE_SPANISH;
			break;
		case ID_LANG_DE:
			l = wxLANGUAGE_GERMAN;
			break;
		case ID_LANG_JA:
			l = wxLANGUAGE_JAPANESE;
			break;
		case ID_LANG_SV:
			l = wxLANGUAGE_SWEDISH;
			break;
		case ID_LANG_FR:
			l = wxLANGUAGE_FRENCH;
			break;
		case ID_LANG_PT:
			l = wxLANGUAGE_PORTUGUESE;
			break;
		case ID_LANG_EL:
			l = wxLANGUAGE_GREEK;
			break;
		case ID_LANG_ZH_HK:
			l = wxLANGUAGE_CHINESE_HONGKONG;
			break;
		case ID_LANG_ZH_CN:
			l = wxLANGUAGE_CHINESE_SIMPLIFIED;
			break;
		case ID_LANG_HE:
			l = wxLANGUAGE_HEBREW;
			break;
		case ID_LANG_RO:
			l = wxLANGUAGE_ROMANIAN;
			break;
		default:
			l = wxLANGUAGE_DEFAULT;
			break;
	}
	wxConfig::Get()->Write(_T("/lang"),(long)l);
	wxMessageBox(_T("To apply changes you must restart Agender"),
		_("Agender Language changed"),wxOK,frame);
}

#endif //wxHAS_TASK_BAR_ICON

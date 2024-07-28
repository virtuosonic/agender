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
#include <wx/filedlg.h>
#include <wx/intl.h>
#include <wx/richtext/richtextsymboldlg.h>
#include <wx/artprov.h>
#include <wx/utils.h>

namespace Agender
{

BEGIN_EVENT_TABLE(AgenderTray,wxTaskBarIcon)
	//click
	EVT_TASKBAR_LEFT_UP(AgenderTray::OnLeft)
	//menu
	EVT_MENU(ID_SHOW,AgenderTray::OnMenuShow)
	EVT_MENU(ID_HIDE,AgenderTray::OnMenuHide)
	//opacity
	EVT_MENU_RANGE(ID_OPC100,ID_OPC25,AgenderTray::OnMenuOpc)
	EVT_MENU(ID_YEARSEL,AgenderTray::OnYearSel)
	EVT_MENU(ID_NOTES_COLOUR,AgenderTray::OnMenuNotesColour)
	EVT_MENU(wxID_EXIT,AgenderTray::OnMenuExit)
	EVT_MENU(wxID_FIND,AgenderTray::OnMenuFind)
	EVT_MENU(ID_AUTOSTART,AgenderTray::OnMenuAutoStart)
	EVT_MENU(ID_SYMBOL,AgenderTray::OnMenuSymbols)
	EVT_MENU(ID_NOTIFY,AgenderTray::OnMenuNotify)
	//lang menu
	EVT_MENU_RANGE(ID_LANG_DEF,ID_LANG_LAST-1,AgenderTray::OnMenuLang)
	//help menu
	EVT_MENU(ID_WIKI,AgenderTray::OnMenuWiki)
	EVT_MENU(ID_BUG,AgenderTray::OnMenuBug)
	EVT_MENU(ID_DONATE,AgenderTray::OnMenuDonate)
	EVT_MENU(wxID_ABOUT,AgenderTray::OnMenuAbout)
	EVT_MENU(ID_UPDATE,AgenderTray::OnMenuUpdate)
END_EVENT_TABLE()

#define wiki wxT("http://sourceforge.net/apps/mediawiki/agender")
#define bugtracker wxT("http://sourceforge.net/tracker/?group_id=271084&atid=1152801")
#define donate wxT("http://sourceforge.net/donate/index.php?group_id=271084")

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
#ifdef __APPLE__
    bool autostart=false;
#else
	bool autostart=true;
#endif
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
	lmenu->AppendRadioItem(ID_LANG_ES,_T("Español"));
	lmenu->AppendRadioItem(ID_LANG_DE,_T("Deutch"));
	lmenu->AppendRadioItem(ID_LANG_JA,_T("日本語"));
	lmenu->AppendRadioItem(ID_LANG_PT,_T("Português"));
	lmenu->AppendRadioItem(ID_LANG_FR,_T("Français"));
	lmenu->AppendRadioItem(ID_LANG_EL,_T("Ελληνικά"));
	lmenu->AppendRadioItem(ID_LANG_SV,_T("Svenska"));
	lmenu->AppendRadioItem(ID_LANG_ZH_HK,_T("Traditional Chinese"));
	lmenu->AppendRadioItem(ID_LANG_ZH_CN,_T("中文"));
	lmenu->AppendRadioItem(ID_LANG_RO,_T("Romanian"));
	lmenu->AppendRadioItem(ID_LANG_HE,_T("Hebrew"));
	lmenu->AppendRadioItem(ID_LANG_AR,_T("العربية"));
	long lang = wxConfig::Get()->Read(_T("/lang"),wxLANGUAGE_UNKNOWN);
	// TODO (gabriel#3#): move to a class
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
		case wxLANGUAGE_ARABIC:
			lmenu->Check(ID_LANG_AR,true);
			break;
		default:
			break;
	}
	//file menu
	//gui menu
	wxMenu* GuiMenu = new wxMenu;
	if (frame->CanSetTransparent())
		GuiMenu->AppendSubMenu(opcMenu,_("Opacity"));
	GuiMenu->AppendCheckItem(ID_YEARSEL,_("Year selector"));
	GuiMenu->Append(ID_NOTES_COLOUR,_("Notes Colour"));
	GuiMenu->AppendSubMenu(lmenu,_("Language"));
	//Tools menu
	wxMenu* ToolsMenu = new wxMenu;
	ToolsMenu->AppendCheckItem(ID_NOTIFY,_("Notify"));
	ToolsMenu->AppendCheckItem(ID_AUTOSTART,_("Autostart"));
	ToolsMenu->AppendCheckItem(ID_UPDATE,_("Search for updates"));
#if wxUSE_RICHTEXT
	ToolsMenu->Append(ID_SYMBOL,_("Symbol"));
#endif//wxUSE_RICHTEXT
	//help menu
	wxMenu* HelpMenu = new wxMenu;
	HelpMenu->Append(ID_WIKI,_("Visit wiki"));
	HelpMenu->Append(ID_BUG,_("Report a bug"));
	HelpMenu->Append(ID_DONATE,_("Make a donation"));
	HelpMenu->Append(wxID_ABOUT,_("About..."));
	//main menu
	wxMenu* menu;
	menu = new wxMenu;
	//show/hide
#ifdef __APPLE__
    menu->Append(ID_SHOW,_("Show"));//->SetBitmaps(m_icon);
#endif
	menu->Append(ID_HIDE,_("Hide"));
	//submenus
	menu->AppendSeparator();
	menu->AppendSubMenu(GuiMenu,_("Gui"));
	menu->AppendSubMenu(ToolsMenu,_("Tools"));
	menu->AppendSubMenu(HelpMenu,_("Help"))->SetBitmap(wxArtProvider::GetBitmap(wxART_HELP,wxART_MENU));
	//exit
	menu->AppendSeparator();
	menu->Append(wxID_EXIT,_("Exit"),_("Exits"))->SetBitmap(wxArtProvider::GetBitmap(wxART_QUIT,wxART_MENU));
	//read value from config
	bool test_bool= false;
	wxConfig::Get()->Read(_T("/yearselector"),&test_bool,false);
	menu->Check(ID_YEARSEL,test_bool);
	wxConfig::Get()->Read(_T("/autostart"),&test_bool,true);
	menu->Check(ID_AUTOSTART,test_bool);
	wxConfig::Get()->Read(_T("/searchforupdates"),&test_bool,true);
	menu->Check(ID_UPDATE,test_bool);
	//wxConfig::Get()->Read(2_T("/notify"),&test_bool,false);
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
		case ID_LANG_AR:
			l = wxLANGUAGE_ARABIC;
			break;
		default:
			l = wxLANGUAGE_DEFAULT;
			break;
	}
	wxConfig::Get()->Write(_T("/lang"),(long)l);
	wxMessageBox(_T("To apply changes you must restart Agender"),
	             _("Agender Language changed"),wxOK,frame);
}

void AgenderTray::OnMenuAbout(wxCommandEvent& event)
{
	event.SetEventType(wxEVT_COMMAND_BUTTON_CLICKED);
	::wxPostEvent(frame->GetEventHandler(),event);
}

void AgenderTray::OnMenuDonate(wxCommandEvent& WXUNUSED(event))
{
	wxLaunchDefaultBrowser(
	    _T("http://sourceforge.net/donate/index.php?group_id=271084"));
}

void AgenderTray::OnMenuBug(wxCommandEvent& WXUNUSED(event))
{
	wxLaunchDefaultBrowser(
	    _T("http://sourceforge.net/tracker/?group_id=271084&atid=1152801"));
}

void AgenderTray::OnMenuWiki(wxCommandEvent& WXUNUSED(event))
{
	wxLaunchDefaultBrowser(
	    _T("http://sourceforge.net/apps/mediawiki/agender"));
}

void AgenderTray::OnMenuUpdate(wxCommandEvent& event)
{
	wxConfig::Get()->Write(_T("/searchforupdates"),event.IsChecked());
}
}//namespace Agender
#endif //wxHAS_TASK_BAR_ICON

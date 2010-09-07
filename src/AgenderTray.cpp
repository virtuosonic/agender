/***************************************************************
 * Name:      AgenderTray.cpp
 * Purpose:   Code for the tray/notification/taskbar/etc icon
 * Author:    Gabriel Espinoza
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#include <wx/wxprec.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif
#ifndef WX_PRECOMP
#include <wx/defs.h>
#endif
#if defined wxHAS_TASK_BAR_ICON

#ifndef WX_PRECOMP
#include "AgenderTray.h"
#include <wx/colordlg.h>
#include <wx/menu.h>
#include <wx/config.h>
#include <wx/app.h>
#include <wx/clipbrd.h>
#include <wx/dataobj.h>
#if wxUSE_RICHTEXT
#include <wx/richtext/richtextsymboldlg.h>
#endif
#endif

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
END_EVENT_TABLE()

AgenderTray::AgenderTray(wxFrame* frame,long colalpha)
{
	this->frame = frame;
	alpha = colalpha;
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
}

void AgenderTray::OnLeft(wxTaskBarIconEvent& WXUNUSED(event))
{
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
	wxMenu* opcMenu;
	opcMenu = new wxMenu;
	opcMenu->AppendRadioItem(ID_OPC100,_("100%"));
	opcMenu->AppendRadioItem(ID_OPC75,_("75%"));
	opcMenu->AppendRadioItem(ID_OPC50,_("50%"));
	opcMenu->AppendRadioItem(ID_OPC25,_("25%"));
	opcMenu->Check(opc,true);
	//
	wxMenu* menu;
	menu = new wxMenu;
	menu->Append(ID_SHOW,_("Show"));
	menu->Append(ID_HIDE,_("Hide"));
	menu->AppendSeparator();
	if (frame->CanSetTransparent())
		menu->AppendSubMenu(opcMenu,_("Opacity"));
	menu->AppendCheckItem(ID_YEARSEL,_("Year selector"));
	menu->Append(ID_NOTES_COLOUR,_("Notes Colour"));
#if wxUSE_RICHTEXT
	menu->Append(ID_SYMBOL,_("Symbol"));
#endif
	menu->AppendCheckItem(ID_AUTOSTART,_("Autostart"));
	menu->AppendSeparator();
	menu->Append(wxID_EXIT,_("Exit"));
	//read value from config
	bool test_bool= false;
	wxConfig::Get()->Read(_T("/yearselector"),&test_bool);
	menu->Check(ID_YEARSEL,test_bool);
	wxConfig::Get()->Read(_T("/autostart"),&test_bool);
	menu->Check(ID_AUTOSTART,test_bool);

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
	wxPostEvent(frame->GetEventHandler(),event);
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
#endif
}

#endif //wxHAS_TASK_BAR_ICON

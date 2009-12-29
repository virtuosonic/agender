#include "AgenderTray.h"
#include <wx/colordlg.h>
#include <wx/menu.h>
#include <wx/config.h>
#include <wx/msgdlg.h>


BEGIN_EVENT_TABLE(AgenderTray,wxTaskBarIcon)
	#if wxCHECK_VERSION(2,9,0) || defined __WXGTK20__//another bug?
	EVT_TASKBAR_LEFT_DOWN(AgenderTray::OnLeft)
	#else
	EVT_TASKBAR_LEFT_UP(AgenderTray::OnLeft)
	#endif
	EVT_MENU(ID_SHOW,AgenderTray::OnMenuShow)
	EVT_MENU(ID_HIDE,AgenderTray::OnMenuHide)
	EVT_MENU_RANGE(ID_OPC100,ID_OPC25,AgenderTray::OnMenuOpc)
	EVT_MENU(ID_YEARSEL,AgenderTray::OnYearSel)
	EVT_MENU(ID_NOTES_COLOUR,AgenderTray::OnMenuNotesColour)
	EVT_MENU(wxID_EXIT,AgenderTray::OnMenuExit)
	EVT_MENU(wxID_FIND,AgenderTray::OnMenuFind)
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

void AgenderTray::OnLeft(wxTaskBarIconEvent& event)
{
	// TODO (virtuoso#1#): compatibilidad wx-2.9: no se muestra ventana
	if (frame->IsShown())
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
	menu->AppendSubMenu(opcMenu,_("Opacity"));
	//menu->Append(ID_BGCOLOUR,_("Set Background Colour"));
	menu->AppendCheckItem(ID_YEARSEL,_("Year selector"));
	menu->Append(ID_NOTES_COLOUR,_("Notes Colour"));
	//menu->AppendSeparator();
	//menu->Append(wxID_FIND,_("Find"));
	menu->AppendSeparator();
	menu->Append(wxID_EXIT,_("Exit"));
	menu->Enable(menu->FindItem(_("Opacity")),frame->CanSetTransparent());
	bool yearSel= false;
	wxConfig::Get()->Read(_T("yearselector"),&yearSel);
	menu->Check(ID_YEARSEL,yearSel);

	return menu;
}

void AgenderTray::OnMenuExit(wxCommandEvent& event)
{
	frame->Destroy();
}

void AgenderTray::OnMenuHide(wxCommandEvent& event)
{
	frame->Hide();
}

void AgenderTray::OnMenuShow(wxCommandEvent& event)
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
		//frame->SetNotesColour(dlg.GetColourData().GetColour());
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
	wxConfig::Get()->Write(_T("yearselector"),event.IsChecked());
	wxPostEvent(frame->GetEventHandler(),event);
}


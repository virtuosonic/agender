#ifndef AGENDERTRAY_H
#define AGENDERTRAY_H

#include <wx/taskbar.h>
#include <wx/colour.h>
#include <wx/frame.h>

class AgenderTray : public wxTaskBarIcon
{
	public:
		AgenderTray(wxFrame* frame,long colalpha);

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
			ID_YEARSEL=7003,
			ID_NOTES_COLOUR=7004,
			ID_AUTOSTART = 7005
		};
		wxFrame* frame;
		int alpha;
		int opc;
		wxColour notesColour;

		void OnLeft(wxTaskBarIconEvent& event);
		void OnMenuShow(wxCommandEvent& event);
		void OnMenuHide(wxCommandEvent& event);
		void OnMenuOpc(wxCommandEvent& event);
		void OnYearSel(wxCommandEvent& event);
		void OnMenuNotesColour(wxCommandEvent& event);
		void OnMenuExit(wxCommandEvent& event);
		void OnMenuFind(wxCommandEvent& event);
		void OnMenuAutoStart(wxCommandEvent& event);

		DECLARE_EVENT_TABLE()
};

#endif // AGENDERTRAY_H

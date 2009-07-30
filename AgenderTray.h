#ifndef AGENDERTRAY_H
#define AGENDERTRAY_H

#include <wx/taskbar.h>

class AgenderFrame;

class AgenderTray : public wxTaskBarIcon
{
    public:
        AgenderTray(AgenderFrame* frame,long colalpha);

        wxMenu* CreatePopupMenu();
        int GetAlpha(){ return alpha;}
    protected:
        AgenderFrame* frame;
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
            ID_NOTES_COLOUR
        };

        int alpha;
        int opc;
        wxColour bgColour;
        wxColour notesColour;

        void OnLeft(wxTaskBarIconEvent& event);
        void OnMenuShow(wxCommandEvent& event);
        void OnMenuHide(wxCommandEvent& event);
        void OnMenuOpc(wxCommandEvent& event);
        void OnMenuBgColour(wxCommandEvent& event);
        void OnMenuNotesColour(wxCommandEvent& event);
        void OnMenuExit(wxCommandEvent& event);
        void OnMenuFind(wxCommandEvent& event);


        DECLARE_EVENT_TABLE()
};

#endif // AGENDERTRAY_H

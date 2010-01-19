/***************************************************************
 * Name:      AgenderIPC.h
 * Purpose:   Defines Classes for Inter Process Communication
 * Author:    Gabriel Espinoza (virtuosonic@users.sourceforge.net)
 * Copyright: Gabriel Espinoza
 * License: GPL 3
 **************************************************************/
#ifndef AGENDERIPC_H_INCLUDED
#define AGENDERIPC_H_INCLUDED

#include <wx/ipc.h>
#include <wx/frame.h>

const wxString IPC_Topic(_T("Agender wakeup"));
const wxString IPC_Service(_T(".agender-server"));

class AgenderConnection : public wxConnection
{
	public:
		AgenderConnection(wxFrame* frame);
		 virtual bool OnExecute(const wxString& topic,wxChar* data,int size,wxIPCFormat format);
	private:
		wxFrame* m_frame;
};

 class AgenderServer : public wxServer
 {
 	public:
		AgenderServer(wxFrame* frame);
 		virtual wxConnectionBase* OnAcceptConnection(const wxString& topic);
	private:
 		wxFrame* m_frame;
 };

#endif // AGENDERIPC_H_INCLUDED

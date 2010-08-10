/***************************************************************
 * Name:      AgenderIPC.h
 * Purpose:   Defines Classes for Inter Process Communication
 * Author:    Gabriel Espinoza (virtuosonic@users.sourceforge.net)
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef AGENDERIPC_H_INCLUDED
#define AGENDERIPC_H_INCLUDED

#include <wx/ipc.h>

const wxString IPC_Topic(_T("Agender wakeup"));
const wxString IPC_Service(_T(".agender-server"));

class AgenderConnection : public wxConnection
{
	public:
		virtual bool OnExecute(const wxString& topic,wxChar* data,int size,wxIPCFormat format);
};

class AgenderServer : public wxServer
{
	public:
		virtual wxConnectionBase* OnAcceptConnection(const wxString& topic);
};

#endif // AGENDERIPC_H_INCLUDED

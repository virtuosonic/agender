/***************************************************************
 * Name:      AgenderIPC.cpp
 * Purpose:   Code for Inter Process Communication
 * Author:    Gabriel Espinoza
 * Copyright: Gabriel Espinoza
 * License: GPL 3
 **************************************************************/
#include "AgenderIPC.h"
#include <wx/log.h>
#include <wx/defs.h>
#include <wx/app.h>

#if defined __WXMSW__ && wxUSE_DDE_FOR_IPC == 0
#warning not using dde under msw
#warning please configure wxMSW to use DDE
//this can scare windows people, they could think we are trojan
//it actually produces a warning by the firewall!!!
//and doesn't work! help needed here
//tested on Windows se7en and XP, linux works fine :P
//Windows 98 & 2000 don't show any warning
#endif


bool AgenderConnection::OnExecute(const wxString& topic,wxChar* data,int size,wxIPCFormat format)
{
	wxLogMessage(_T("checking topic"));
	if (topic != IPC_Topic)
		return false;
	wxLogMessage(_T("checking frame"));
	if (wxTheApp->GetTopWindow())
	{
		wxLogMessage(_T("showing frame"));
		wxTheApp->GetTopWindow()->Show(true);
	}
	return true;
}

wxConnectionBase * AgenderServer::OnAcceptConnection(const wxString& topic)
{
	// TODO (virtuoso#1#): compatibilidad wx-2.9: al parecer  no se establece una conexion
	if (topic != IPC_Topic)
		return NULL;
	wxLogMessage(_T("Connection acepted"));
	return new AgenderConnection;
}

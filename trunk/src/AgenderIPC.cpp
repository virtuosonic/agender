/***************************************************************
 * Name:      AgenderIPC.cpp
 * Purpose:   Code for Inter Process Communication
 * Author:    Gabriel Espinoza
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include <wx/log.h>
#include <wx/window.h>
#include <wx/app.h>
/**
the next file must be the last we include
else the others will overide wxUSE_DDE_FOR_IPC
and cause Agender to crash when calling
AgenderServer->Create()
*/
#include "AgenderIPC.h"

bool AgenderConnection::OnExecute(const wxString& topic,wxChar* WXUNUSED(data),int WXUNUSED(size),wxIPCFormat WXUNUSED(format))
{
	wxLogVerbose(_T("checking topic"));
	if (topic != IPC_Topic)
		return false;
	wxLogVerbose(_T("checking frame"));
	if (wxTheApp->GetTopWindow())
	{
		wxLogVerbose(_T("showing frame"));
		wxTheApp->GetTopWindow()->Show(true);
	}
	return true;
}

wxConnectionBase * AgenderServer::OnAcceptConnection(const wxString& topic)
{
	if (topic != IPC_Topic)
		return NULL;
	wxLogVerbose(_T("IPC Connection acepted"));
	return new AgenderConnection;
}

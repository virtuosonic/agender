/***************************************************************
 * Name:      AgenderIPC.cpp
 * Purpose:   Code for Inter Process Communication
 * Author:    Gabriel Espinoza
 * Copyright: Gabriel Espinoza
 * License: GPL 3
 **************************************************************/
#include "AgenderIPC.h"
#include <wx/log.h>
#include <wx/msgdlg.h>

 AgenderConnection::AgenderConnection(wxFrame* frame)
{
	#if defined __WXMSW__ && wxUSE_DDE_FOR_IPC == 0
		#warning "not using dde under msw"
		#warning "please configure wxMSW to use DDE"
		//this can scare windows people, they could think we are trojan
		//it actually produces a warning by the firewall!!!
		//tested on Win se7en and XP, linux works fine :P
	#endif
	m_frame = frame;
}

bool AgenderConnection::OnExecute(const wxString& topic,wxChar* data,int size,wxIPCFormat format)
{
	wxLogMessage(_T("checking topic"));
	if (topic != IPC_Topic)
		return false;
	wxLogMessage(_T("checking frame"));
	if (m_frame)
	{
		wxLogMessage(_T("showing frame"));
		m_frame->Show(true);
	}
	return true;
}

 AgenderServer::AgenderServer(wxFrame* frame)
{
	m_frame = frame;
}

wxConnectionBase * AgenderServer::OnAcceptConnection(const wxString& topic)
{
	// TODO (virtuoso#1#): compatibilidad wx-2.9: al parecer  no se establece una conexion
	if (topic != IPC_Topic)
		return NULL;
	wxLogMessage(_T("Connection acepted"));
	return new AgenderConnection(m_frame);
}


#include "AgenderIPC.h"
#include <wx/log.h>
#include <wx/msgdlg.h>

 AgenderConnection::AgenderConnection(wxFrame* frame)
{
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
	if (topic != IPC_Topic)
		return NULL;
	wxLogMessage(_T("Connection acepted"));
	return new AgenderConnection(m_frame);
}

wxConnectionBase* AgenderClient::OnMakeConnection()
{
	//m_cnn = new wxConnection;
	return new wxConnection;
}
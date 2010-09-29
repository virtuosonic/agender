/***************************************************************
 * Name:      Updater.cpp
 * Purpose:   Implements Updater Class
 * Author:    Gabriel Espinoza
 * Created:   2010-09-23
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#include "Updater.h"
#include "AgenderMain.h"

#include <wx/protocol/http.h>
#include <wx/txtstrm.h>
#include <wx/tokenzr.h>
#include <wx/log.h>
#include <wx/msgdlg.h>
#include <wx/app.h>

#ifdef __BORLANDC__
#pragma hdrstop
#endif

Updater::Updater(wxString host,wxString file,wxString ver) : wxThread(wxTHREAD_DETACHED)
{
	m_host=host;
	m_file=file;
	m_ver=ver;
}

Updater::~Updater()
{
	wxLogVerbose(_T("destroying updater"));
}

wxThread::ExitCode Updater::Entry()
{
	wxString found = Search();
	if (!found.IsEmpty())
	{
		if (IsLatest(found))
		{
			AskUser(found);
		}
	}
	return (wxThread::ExitCode) 0;
}

wxString Updater::Search()
{
	wxLogVerbose(_T("creating client"));
	wxHTTP updateClient;
	wxLogVerbose(_T("connecting"));
	if (updateClient.Connect(m_host))
	{
		wxInputStream* ver_data = (wxInputStream*)updateClient.GetInputStream(m_file);
		wxLogVerbose(_T("response: %i"),updateClient.GetResponse());
		if (ver_data)
		{
			wxString last_ver;
			wxTextInputStream strm(*ver_data);
			last_ver = strm.ReadLine();
			delete ver_data;
			return last_ver;
		}
		else
			wxLogVerbose(_T("failed opening stream"));
	}
	else
		wxLogVerbose(_T("failed connecting"));
	return wxEmptyString;
}

bool Updater::IsLatest(wxString latest)
{
	wxArrayInt i_cur = ToInt(m_ver);
	wxArrayInt i_latest = ToInt(latest);
	for (unsigned int i = 0;i < i_cur.GetCount()  && i < i_latest.GetCount();i++)
	{
		if (i_latest[i] > i_cur[i])
		{
			wxLogVerbose(_T("found new version"));
			return true;
		}
	}
	wxLogVerbose(_T("this is the latest"));
	return false;
}

void Updater::AskUser(wxString ver)
{
	wxLogVerbose(_T("sending event to frame"));
	wxCommandEvent event(wxEVT_COMMAND_MENU_SELECTED,AgenderFrame::ID_UPDATE_FOUND);
	event.SetString(ver);
	wxPostEvent(wxTheApp->GetTopWindow(),event);
}

wxArrayInt Updater::ToInt(wxString ver)
{
	wxStringTokenizer tokenizer(ver,_T('.'));
	wxArrayInt ver_num;
	while (tokenizer.HasMoreTokens())
	{
		wxString token =tokenizer.GetNextToken();
		long n;
		token.ToLong(&n);
		ver_num.Add(n);
	}
	return ver_num;
}

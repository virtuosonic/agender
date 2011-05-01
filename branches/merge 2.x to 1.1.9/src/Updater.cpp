/***************************************************************
 * Name:      Updater.cpp
 * Purpose:   Implements Updater Class
 * Author:    Gabriel Espinoza
 * Created:   2010-09-23
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "Updater.h"
#include "AgenderMain.h"

#include <wx/protocol/http.h>
#include <wx/txtstrm.h>
#include <wx/tokenzr.h>
#include <wx/log.h>
#include <wx/config.h>
#include <wx/app.h>

namespace Agender
{

Updater::Updater(wxString host,wxString file,wxString ver) : wxThread(wxTHREAD_DETACHED)
{
	m_host=host;
	m_file=file;
	m_ver=ver;
}

Updater::~Updater()
{
	//nothing todo here
	wxLogMessage(_T("destroying updater"));
}

wxThread::ExitCode Updater::Entry()
{
	//wait 5 minutes
	//to give oportunity
	//to the user to
	//connect to internet
	Sleep(300000);
	wxString found;
	while (found.IsEmpty())
	{
		//read option to search for updates from
		//config, the default is to search
		bool searchforupdates = true;
		wxConfig::Get()->Read(_T("/searchforupdates"),&searchforupdates);
		if (searchforupdates)
		{
			//if true search
			found = Search();
		}
		//if not empty compare
		if (!found.IsEmpty())
		{
			if (!IsLatest(found))
				AskUser(found);
		}
		else
		{
			//sleep 1 hour
			Sleep(3600000);
		}
	}
	return (wxThread::ExitCode) 0;
}

wxString Updater::Search()
{
	wxLogMessage(_T("creating http client"));
	wxHTTP updateClient;
	wxLogMessage(_T("connecting to %s"),m_host.c_str());
	if (updateClient.Connect(m_host))
	{
		//this saves a little band width
		updateClient.SetHeader(_T("If-Modified-Since"),
		                       wxConfig::Get()->Read(_T("/http-modified-time"),wxEmptyString));
		wxInputStream* ver_data = (wxInputStream*)updateClient.GetInputStream(m_file);
		wxLogMessage(_T("http response: %i"),updateClient.GetResponse());
		if (ver_data && updateClient.GetResponse() == 200)
		{
			wxConfig::Get()->Write(_T("/http-modified-time"),
			                       updateClient.GetHeader(_T("Date")));
			wxLogMessage(_T("Date = %s"),updateClient.GetHeader(_T("Date")).c_str());
			wxString last_ver;
			wxTextInputStream strm(*ver_data);
			last_ver = strm.ReadLine();
			delete ver_data;
			//here we return the
			//contents of the file
			//it should be something like
			//9.9.9
			return last_ver;
		}
		else if (updateClient.GetResponse() == 304)
			wxLogMessage(_T("no changes in version info"));
		else
			wxLogMessage(_T("failed opening http stream"));
	}
	else
		wxLogWarning(_T("failed connecting to %s"),m_host.c_str());
	//we return nothing
	return wxEmptyString;
}

bool Updater::IsLatest(wxString latest)
{
	if (m_ver == latest)
		return true;
	//current
	wxArrayInt i_cur = ToInt(m_ver);
	//retrieved from inet
	wxArrayInt i_latest = ToInt(latest);
	for (unsigned int i = 0; i < i_cur.GetCount()  && i < i_latest.GetCount(); i++)
	{
		if (i_latest[i] > i_cur[i])
		{
			wxLogVerbose(_T("found new version"));
			return false;
		}
	}
	if (i_latest.GetCount() > i_cur.GetCount())
	{
		wxLogVerbose(_T("found new version"));
		return false;
	}
	wxLogVerbose(_T("this is the latest version"));
	return true;
}

void Updater::AskUser(wxString ver)
{
	//this sends an event to the
	//main window
	wxLogMessage(_T("sending event to frame"));
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
}

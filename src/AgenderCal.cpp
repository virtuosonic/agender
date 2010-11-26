/***************************************************************
 * Name:      AgenderCal.cpp
 * Purpose:   Code for Reading schedule
 * Author:    Gabriel Espinoza
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "AgenderCal.h"
#include <wx/log.h>
#include <wx/wfstream.h>

//since this  software has a very bad design, now I have to use hacks because it wasn't mean to
//be extensible, however it acomplishes it goals: small, fast & portable
//maybe i'll fix al this in 2.0

const wxChar* AgenderCal::stickPath = _T("/sticky");

AgenderCal::AgenderCal(wxDateTime date,wxString file)
{
	wxFileInputStream stream(file);
	cfg = new wxFileConfig(stream);
	SetDate(date);
}

AgenderCal::~AgenderCal()
{
	wxLogVerbose(_T("destroying AgenderCal"));
	delete cfg;
}

void AgenderCal::SetDate(wxDateTime date)
{
	m_date=date;
}

wxDateTime AgenderCal::GetDate()
{
	return m_date;
}

wxArrayString AgenderCal::GetNotes()
{
	wxArrayString notes;
	wxString dateStr(m_date.Format(_T("%Y-%m-%d")));
	if (cfg->HasGroup(m_date.Format(_T("%Y-%m-%d"))))
	{
		cfg->SetPath(dateStr);
		wxString noteName;
		long indx = 0;
		if (cfg->GetFirstEntry(noteName,indx))
		{
			notes.Add(noteName);
			while (cfg->GetNextEntry(noteName,indx))
				notes.Add(noteName);
		}
		cfg->SetPath(_T("/"));
		// TODO (virtuoso#1#): is this needed?
		if (notes.GetCount() == 0)
			cfg->DeleteGroup(dateStr);
	}
	if (cfg->HasGroup(stickPath))
	{
		cfg->SetPath(stickPath);
		wxString noteName;
		long indx = 0;
		if (cfg->GetFirstEntry(noteName,indx))
		{
			notes.Add(noteName+ stickSymb);
			while (cfg->GetNextEntry(noteName,indx))
				notes.Add(noteName+ stickSymb);
		}
		cfg->SetPath(_T("/"));
	}
	return notes;
}

wxString AgenderCal::GetNoteText(wxString note)
{
	return cfg->Read(GetFullPath(note),wxEmptyString);
}

void AgenderCal::SetNoteText(wxString note,wxString text)
{
	cfg->Write(GetFullPath(note),text);
}

wxArrayString AgenderCal::Find(wxString WXUNUSED(FindString))
{
	wxArrayString found;
	// TODO (virtuoso#1#): implement!!!
	return found;
}

wxArrayInt AgenderCal::GetDaysWithNotes()
{
	//whe have two diferent algorithms  for the same problem
	wxArrayInt days;
	//the first looks if the existing notes
	//belong to the current month
	if (cfg->GetNumberOfGroups() < 30)
	{
		wxString group;
		long indx=0;
		if (cfg->GetFirstGroup(group,indx))
		{
			// TODO (virtuoso#1#): send this to a method?
			if (m_date.Format(_T("%m")) == group.BeforeLast('-').AfterFirst('-'))
			{
				long i;
				group.AfterLast('-').ToLong(&i);
				days.Add(i);
			}
			while(cfg->GetNextGroup(group,indx))
			{
				if (m_date.Format(_T("%m")) == group.BeforeLast('-').AfterFirst('-'))
				{
					long i;
					group.AfterLast('-').ToLong(&i);
					days.Add(i);
				}
			}
		}
		return days;
	}
	//the second (original) checks if there are notes for each date
	int count = 1 + wxDateTime::GetNumberOfDays(m_date.GetMonth(),m_date.GetYear());
	wxString dateStr;
	for (int i = 1; i < count; i++)
	{
		if (i < 10)
		{
			dateStr = m_date.Format(_T("%Y-%m-")) +
					  wxString::Format(_T("0%i"),i);
		}
		else
		{
			dateStr = m_date.Format(_T("%Y-%m-")) +
					  wxString::Format(_T("%i"),i);
		}
		if (cfg->HasGroup(dateStr))
			days.Add(i);
	}
	return days;
}

void AgenderCal::RmNote(wxString note)
{
	cfg->DeleteEntry(GetFullPath(note),true);
}

bool AgenderCal::RenameNote(wxString OldName,wxString NewName)
{
	wxString noteVal;
	if (!cfg->Read(GetFullPath(OldName),&noteVal))
		return false;
	cfg->DeleteEntry(GetFullPath(OldName),true);
	cfg->Write(GetFullPath(NewName),noteVal);
	return true;
}

bool AgenderCal::HasNote(wxString note)
{
	return cfg->HasEntry(GetFullPath(note));
}

bool AgenderCal::MakeSticky(wxString note)
{
	wxString stickyNote(wxString::Format(_T("%s/%s"),stickPath,note.c_str()));
	cfg->Write(stickyNote,GetNoteText(note));
	RmNote(note);
	return true;
}

wxString AgenderCal::GetFullPath(wxString note)
{
	if (RmStickySimb(&note))
	{
		return wxString::Format(_T("%s/%s") ,stickPath,note.c_str());
	}
	return m_date.Format(_T("/%Y-%m-%d/")) + note;
}

bool AgenderCal::IsSticky(wxString note)
{
	if (RmStickySimb(&note))
		return cfg->HasEntry(wxString::Format(_T("%s/%s"),stickPath,note.c_str()));
	return false;

}

bool AgenderCal::UnStick(wxString note)
{
	wxString NormalNote(GetFullPath(note.BeforeLast('$')));
	cfg->Write(NormalNote,GetNoteText(note));
	RmNote(note);
	return true;
}

bool AgenderCal::RmStickySimb(wxString* note)
{
	if (note->Find(stickSymb) != wxNOT_FOUND)
	{
		*note = note->BeforeLast('$');
		return true;
	}
	return false;
}


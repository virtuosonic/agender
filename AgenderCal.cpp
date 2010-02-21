/***************************************************************
 * Name:      AgenderCal.cpp
 * Purpose:   Code for Reading schedule
 * Author:    Gabriel Espinoza
 * Copyright: Gabriel Espinoza
 * License: GPL 3
 **************************************************************/
#include "AgenderCal.h"

#include <wx/config.h>
#include <wx/textfile.h>
#include <wx/log.h>

AgenderCal::AgenderCal(wxDateTime date)
{
	SetDate(date);
}

AgenderCal::~AgenderCal()
{
	wxLogDebug(_T("destroying AgenderCal"));
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
	if (wxConfig::Get()->HasGroup(m_date.Format(_T("%Y-%m-%d"))))
	{
		wxConfig::Get()->SetPath(dateStr);
		wxString noteName;
		long indx = 0;
		if (wxConfig::Get()->GetFirstEntry(noteName,indx))
		{
			notes.Add(noteName);
			while (wxConfig::Get()->GetNextEntry(noteName,indx))
				notes.Add(noteName);
		}
		wxConfig::Get()->SetPath(_T("/"));
		if (notes.GetCount() == 0)
			wxConfig::Get()->DeleteGroup(dateStr);
	}
	if (wxConfig::Get()->HasGroup(stickPath))
	{
		wxConfig::Get()->SetPath(stickPath);
		wxString noteName;
		long indx = 0;
		if (wxConfig::Get()->GetFirstEntry(noteName,indx))
		{
			notes.Add(noteName+ stickSymb);
			while (wxConfig::Get()->GetNextEntry(noteName,indx))
				notes.Add(noteName+ stickSymb);
		}
		wxConfig::Get()->SetPath(_T("/"));
	}
	// TODO (virtuoso#1#): declare and make use of constant in some wxString that need it

	return notes;
}

wxString AgenderCal::GetNoteText(wxString note)
{
	return wxConfig::Get()->Read(GetFullPath(note),wxEmptyString);
}

void AgenderCal::SetNoteText(wxString note,wxString text)
{
	wxConfig::Get()->Write(GetFullPath(note),text);
}

wxArrayString AgenderCal::Find(wxString FindString)
{
	wxArrayString found;
	// TODO (virtuoso#1#): implement!!!
	return found;
}

wxArrayInt AgenderCal::GetDaysWithNotes()
{
	wxArrayInt days;
	// TODO (virtuoso#1#): agregar algoritmo analizando grupos
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
		if (wxConfig::Get()->HasGroup(dateStr) && wxConfig::Get()->GetNumberOfEntries(dateStr))
			days.Add(i);
	}
	return days;
}

void AgenderCal::RmNote(wxString note)
{
	wxConfig::Get()->DeleteEntry(GetFullPath(note),true);
	//wxLogMessage(_T("deleted : %s"),GetFullPath(note).c_str());
}

bool AgenderCal::RenameNote(wxString OldName,wxString NewName)
{
	wxString noteVal;
	if (!wxConfig::Get()->Read(GetFullPath(OldName),&noteVal))
		return false;
	wxConfig::Get()->DeleteEntry(GetFullPath(OldName),true);
	wxConfig::Get()->Write(GetFullPath(NewName),noteVal);
	return true;
}

bool AgenderCal::HasNote(wxString note)
{
	return wxConfig::Get()->HasEntry(GetFullPath(note));
}

bool AgenderCal::MakeSticky(wxString note)
 {
	wxString stickyNote(wxString::Format(_T("%s/%s"),stickPath,note.c_str()));
	wxConfig::Get()->Write(stickyNote,GetNoteText(note));
	RmNote(note);
	return true;
}

wxString AgenderCal::GetFullPath(wxString note)
{
	int indx = 0;
	if (RmStickySimb(&note))
	{
		return wxString::Format(_T("%s/%s") ,stickPath,note.c_str());
	}
	return m_date.Format(_T("/%Y-%m-%d/")) + note;
}

bool AgenderCal::IsSticky(wxString note)
{
	if (RmStickySimb(&note))
		return wxConfig::Get()->HasEntry(wxString::Format(_T("%s/%s"),stickPath,note.c_str()));
	return false;

}

bool AgenderCal::UnStick(wxString note)
{
	wxString NormalNote(GetFullPath(note.BeforeLast('$')));
	wxConfig::Get()->Write(NormalNote,GetNoteText(note));
	RmNote(note);
	return true;
}

bool AgenderCal::RmStickySimb(wxString* note)
{
	if (int indx = note->Find(stickSymb) != wxNOT_FOUND)
	{
		*note = note->BeforeLast('$');
		return true;
	}
	return false;
}


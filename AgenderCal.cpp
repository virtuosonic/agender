#include "AgenderCal.h"

#include <wx/config.h>
#include <wx/textfile.h>
#include <wx/log.h>

AgenderCal::AgenderCal(wxDateTime date)
{
	m_date = date;
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
	if (!wxConfig::Get()->HasGroup(m_date.Format(_T("%Y-%m-%d"))))
		return notes;
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
	return notes;
}

wxString AgenderCal::GetNoteText(wxString note)
{
	wxString fullnote(m_date.Format(_T("/%Y-%m-%d/")) + note);
	return wxConfig::Get()->Read(fullnote,wxEmptyString);
}

void AgenderCal::SetNoteText(wxString note,wxString text)
{
	wxString fullnote(m_date.Format(_T("/%Y-%m-%d/")) + note);
	wxConfig::Get()->Write(fullnote,text);
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
	for (int i = 1;i < count;i++)
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
	wxString dateStr(m_date.Format(_T("/%Y-%m-%d/")));
	wxConfig::Get()->DeleteEntry(dateStr + note,true);
}

bool AgenderCal::RenameNote(wxString OldName,wxString NewName)
{
	wxString noteVal;
	if (!wxConfig::Get()->Read(OldName,&noteVal))
		return false;
	wxConfig::Get()->DeleteEntry(OldName,true);
	wxConfig::Get()->Write(NewName,noteVal);
	return true;
}

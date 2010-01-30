/***************************************************************
 * Name:      AgenderCal.h
 * Purpose:   Defines AgenderCal Class
 * Author:    Gabriel Espinoza (virtuosonic@users.sourceforge.net)
 * Copyright: Gabriel Espinoza
 * License: GPL 3
 **************************************************************/

#ifndef AGENDERCAL_H_INCLUDED
#define AGENDERCAL_H_INCLUDED

#include <wx/datetime.h>
#include <wx/string.h>
#include <wx/arrstr.h>
#include <wx/dynarray.h>

enum {
	AG_NORMAL,
	AG_STICKY,
	AG_STICKYW
};

class AgenderCal
{
	public:
		AgenderCal(wxDateTime date);
		~AgenderCal();
		void SetDate(wxDateTime date);
		wxDateTime GetDate();
		wxArrayString GetNotes();
		bool HasNote(wxString note);
		wxString GetNoteText(wxString note);
		void SetNoteText(wxString note,wxString text);
		wxArrayString Find(wxString FindString);
		wxArrayInt GetDaysWithNotes();
		void RmNote(wxString note);
		bool RenameNote(wxString OldName,wxString NewName);
	private:
		wxDateTime m_date;
};

#endif // AGENDERCAL_H_INCLUDED

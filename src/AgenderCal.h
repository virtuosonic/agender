/***************************************************************
 * Name:      AgenderCal.h
 * Purpose:   Defines AgenderCal Class
 * Author:    Gabriel Espinoza (virtuosonic@users.sourceforge.net)
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/

#ifndef AGENDERCAL_H_INCLUDED
#define AGENDERCAL_H_INCLUDED

#include <wx/datetime.h>
#include <wx/string.h>
#include <wx/arrstr.h>
#include <wx/dynarray.h>
#include <wx/fileconf.h>

//i hate globals

namespace Agender
{
#define stickSymb _T("$(sticky)")
class AgenderCal
{
	public:
		AgenderCal(wxDateTime date,wxString file);
		~AgenderCal();
		void SetDate(wxDateTime date);
		wxDateTime GetDate();
		wxArrayString GetNotes();
		bool HasNote(wxString note);
		wxString GetNoteText(wxString note);
		void SetNoteText(wxString note,wxString text);
		wxArrayInt GetDaysWithNotes();
		//wxDatesArray GetDatesWithNotes();
		void RmNote(wxString note);
		bool RenameNote(wxString OldName,wxString NewName);
		bool MakeSticky(wxString note);
		bool UnStick(wxString note);
		bool IsSticky(wxString note);
		//pending
		wxArrayString Find(wxString FindString);
	private:
		wxDateTime m_date;
		wxString GetFullPath(wxString note);
		bool RmStickySimb(wxString* note);
		static const wxChar* stickPath;
		wxFileConfig* cfg;
};
}//namespace Agender
#endif // AGENDERCAL_H_INCLUDED

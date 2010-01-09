#ifndef AGENDERCAL_H_INCLUDED
#define AGENDERCAL_H_INCLUDED

#include <wx/datetime.h>
#include <wx/string.h>
#include <wx/arrstr.h>
#include <wx/dynarray.h>

class AgenderCal
{
	public:
		AgenderCal(wxDateTime date);
		~AgenderCal();
		void SetDate(wxDateTime date);
		wxDateTime GetDate();
		wxArrayString GetNotes();
		wxString GetNoteText(wxString note);
		void SetNoteText(wxString note,wxString text);
		wxArrayString Find(wxString FindString);
		wxArrayInt GetDaysWithNotes();
		void RmNote(wxString note);
	private:
		wxDateTime m_date;
};

#endif // AGENDERCAL_H_INCLUDED

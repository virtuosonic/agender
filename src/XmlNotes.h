/***************************************************************
 * Name:      XmlNotes.h
 * Purpose:   New notes implementation
 * Author:    Gabriel Espinoza
 * Created:   2010-11-11
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef _XMLNOTES_H_
#define _XMLNOTES_H_

#include <wx/string.h>
#include <wx/dynarray.h>
#include <wx/xml/xml.h>
#include <wx/datetime.h>
#include <wx/platform.h>//for __VISUALC__

//disable a wxArray related warning
#ifdef __VISUALC__
#pragma warning(disable: 4284)
#endif

#define stickSymb _T("$(sticky)")

namespace Agender
{
class  AgCal;
class AgNote
{
	public:
		AgNote(wxXmlNode* node);
		~AgNote();
		const wxString GetName();
		const wxString GetText();
		void SetName(wxString name);
		void SetText(wxString text);
	private:
		wxXmlNode* m_node;
		friend class AgCal;
};

WX_DEFINE_ARRAY(AgNote*,AgNotesArray);
class AgDate
{
	public:
		AgDate(wxDateTime date,AgCal* cal);
		~AgDate();
		const AgNotesArray GetNotes();
		bool HasNote(const wxString& note);
		bool AddNote(const wxString& note);
		bool DeleteNote(const wxString& note);
		AgNote* GetNote(const wxString& note);
		wxDateTime GetDate() {
			return m_date;
		}
	private:
		wxXmlNode* GetNode();
		wxXmlNode* CreateNode();
		AgNote* DetachNote(const wxString& note);
		wxXmlNode* m_node;
		AgCal* m_cal;
		wxDateTime m_date;
		AgNotesArray notes;
		friend class AgCal;
};

WX_DEFINE_ARRAY(AgDate*,AgDatesArray);
WX_DECLARE_OBJARRAY(wxDateTime,wxDatesArray);
class AgCal
{
	public:
		//build from a file
		AgCal(const wxString& file=wxEmptyString);
		//build from a xml doc
		AgCal(wxXmlDocument& doc);
		//destroy
		~AgCal();
		//get unique instance
		static AgCal* Get();
		static AgCal* Set(AgCal* cal);
		//write changes
		void Flush();
		//set current date
		bool SetDate(wxDateTime date);
		//get date object
		AgDate* GetDate();
		//returns days in current month
		wxArrayInt GetDaysWithNotes();
		//return ALL dates
		wxDatesArray GetDatesWithNotes();
		//StickyNotes
		const AgNotesArray GetStickyNotes();
		bool MakeSticky(wxString note);
		bool UnStick(wxString note);
		AgNote* GetStickyNote(wxString note);
		//import export to file
		void Import(wxString file);
		void Export(wxString file);
	private:
		wxXmlDocument m_doc;
		AgDate* m_date;
		wxString m_file;
		AgNotesArray snotes;
		static AgCal* g_Cal;
		void CreateXml();
		void CreateStickyNode();
		void LoadXml();
		inline void LoadStickyNotes();
		bool ImportXml(wxString file);
		bool Import1x(wxString file);
		wxXmlNode* m_dates;
		wxXmlNode* m_sticky;
		friend class AgDate;
};
}//namespace Agender
#endif // _XMLNOTES_H_

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

#define stickSymb _T("$(sticky)")

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
		bool Stick(bool stick);
		bool IsSticky(){return false;}
	private:
		wxXmlNode* m_node;
		bool m_sticky;
};

WX_DEFINE_ARRAY(AgNote*,AgNotesArray);
class AgDate
{
	public:
		AgDate(wxDateTime date,AgCal* cal);
		~AgDate();
		const AgNotesArray GetNotes();
		bool HasNote(wxString note);
		bool AddNote(wxString note);
		bool DeleteNote(wxString note);
		AgNote* GetNote(wxString note);
		wxDateTime GetDate() {return m_date;}
	private:
		wxXmlNode* GetNode();
		wxXmlNode* CreateNode();
		wxXmlNode* m_node;
		AgCal* m_cal;
		wxDateTime m_date;
		AgNotesArray notes;
	friend class AgCal;
};

WX_DEFINE_ARRAY(AgDate*,AgDatesArray);
class AgCal
{
	public:
		AgCal();
		~AgCal();
		//get unique instance
		static AgCal* Get();
		//write changes
		void Flush();
		bool SetDate(wxDateTime date);
		/*const*/ AgDate* GetDate();
		wxArrayInt GetDaysWithNotes();
	private:
		wxXmlDocument m_doc;
		AgDate* m_date;
		/*const*/ wxString m_file;
		static AgCal* g_Cal;
		void CreateXml();
		void LoadXml();
		void Import(wxString file);
		wxXmlNode* m_dates;
	friend class AgDate;
};

#endif // _XMLNOTES_H_

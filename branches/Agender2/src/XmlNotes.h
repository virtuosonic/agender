/***************************************************************
 * Name:      XmlNotes.h
 * Purpose:   Xml notes
 * Author:    Gabriel Espinoza
 * Created:   2010-10-09
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef _XMLNOTES_H_
#define _XMLNOTES_H_

#include "AgenderCal.h"
#include <wx/xml/xml.h>

class XmlNotes
{
	public:
		XmlNotes();
		~XmlNotes();
		//
		void SetDate(wxDateTime date);
		wxDateTime GetDate();
		//
		bool Flush();
		//
		wxArrayString GetNotes();
		bool HasNote(wxString note);
		wxString GetNoteText(wxString note);
		void SetNoteText(wxString note,wxString text);
		wxArrayInt GetDaysWithNotes();
		void RmNote(wxString note);
		bool RenameNote(wxString OldName,wxString NewName);
		bool MakeSticky(wxString note);
		bool UnStick(wxString note);
		bool IsSticky(wxString note);
	private:
		wxXmlDocument m_doc;
		wxXmlNode* noteNode;
		wxString m_file;
		//private methods
		void InitXml();
		void Import();
		wxXmlNode* GetDateNode();
		wxXmlNode* GetNoteNode(wxString note);
		wxXmlNode* GetStickyNoteNode(wxString note);

};

#endif // _XMLNOTES_H_

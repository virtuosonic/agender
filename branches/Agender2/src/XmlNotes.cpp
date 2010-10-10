/***************************************************************
 * Name:      XmlNotes.cpp
 * Purpose:   Xml notes
 * Author:    Gabriel Espinoza
 * Created:   2010-10-09
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#include "XmlNotes.h"
#include <wx/filename.h>
#include <wx/stdpaths.h>

XmlNotes::XmlNotes()
{
	wxFileName fname;
	fname.AsignDir(wxStandardPaths::GetUserConfigDir());
	fname.SetName(_T("agender.xml"))
	if (wxFileExists(fname.GetFullPath()))
		m_doc.Load(fname.GetFullPath());
	else
		InitXml();
}

XmlNotes::~XmlNotes()
{

}

bool XmlNotes::IsSticky(wxString note)
{

}

bool XmlNotes::UnStick(wxString note)
{

}

bool XmlNotes::MakeSticky(wxString note)
{

}

bool XmlNotes::RenameNote(wxString OldName,wxString NewName)
{

}

void XmlNotes::RmNote(wxString note)
{

}

wxArrayInt XmlNotes::GetDaysWithNotes()
{

}

void XmlNotes::SetNoteText(wxString note,wxString text)
{

}

wxString XmlNotes::GetNoteText(wxString note)
{

}

bool XmlNotes::HasNote(wxString note)
{

}

wxArrayString XmlNotes::GetNotes()
{

}

void XmlNotes::InitXml()
{
	wxString attr(_T("1"));
	m_doc.SetRoot(new wxXmlNode(NULL,wxXML_ELEMENT_NODE,
			_T("Agender")));
	m_doc.GetRoot().AddAttribute(_T("version"),&attr);
	m_doc.GetRoot().AddChild(new wxXmlNode(m_doc.GetRoot(),
			wxXML_ELEMENT_NODE,_T("notes")));
}


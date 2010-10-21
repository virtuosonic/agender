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
	noteNode = NULL;
	wxFileName fname;
	fname.AsignDir(wxStandardPaths::GetUserDataDir());
	fname.SetName(_T("agender.xml"))
	m_file = fname.GetFullPath()
	if (wxFileExists(m_file))
		m_doc.Load(m_file);
	else
		InitXml();
	if (!noteNode)
	{
		wxXmlNode* node = m_doc.GetRoot()->GetChildren();
		while (node)
		{
			if (node->GetName() == _T("notes"))
				noteNode = node;
			else
				node = node->GetNext();
		}
	}
}

XmlNotes::~XmlNotes()
{
	Flush();
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
	noteNode = new wxXmlNode(m_doc.GetRoot(),
			wxXML_ELEMENT_NODE,_T("notes"));
}

bool XmlNotes::Flush()
{
	m_doc.Save(m_file);
	return true;
}

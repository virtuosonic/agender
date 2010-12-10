/***************************************************************
 * Name:      XmlNotes.cpp
 * Purpose:   New notes implementation
 * Author:    Gabriel Espinoza
 * Created:   2010-11-11
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifdef __BORLANDC__
#pragma hdrstop
#endif

#include "AgenderMain.h"
#include "XmlNotes.h"

#include <wx/filename.h>
#include <wx/stdpaths.h>

AgCal* AgCal::g_Cal = NULL;
#define Ag_1_0 wxStandardPaths::Get().GetConfigDataDir() + _T(".Agender-current user.txt")
#define Ag_1_1_9 wxGetHomeDir() + _T(".Agender-current user.txt")

// TODO (virtuoso#1#): implement sticky notes

AgCal::AgCal()
{
	wxFileName fname;
	fname.AssignDir(wxStandardPaths::Get().GetUserDataDir());
	fname.SetName(_T("agender"));
	fname.SetExt(_T("xml"));
	m_file = fname.GetFullPath();
	if (wxFileExists(m_file))
		LoadXml();
	else
		CreateXml();
	m_date = new AgDate(wxDateTime::Now(),this);
}

AgCal::~AgCal()
{
	Flush();
}

AgCal* AgCal::Get()
{
	if (g_Cal == NULL)
		g_Cal = new AgCal;
	return g_Cal;
}


void AgCal::Flush()
{
	m_doc.Save(m_file);
}

void AgCal::CreateXml()
{
	wxXmlNode* root = new wxXmlNode(wxXML_ELEMENT_NODE,_T("Agender"));
	m_dates = new wxXmlNode(root,wxXML_ELEMENT_NODE,_T("dates"));
	new wxXmlNode(root,wxXML_COMMENT_NODE,wxEmptyString,
		_T("in this file Agender saves your notes, so be careful with it"));
	root->AddProperty(_T("version"),__AGENDER_VERSION__);
	m_doc.SetRoot(root);
}

void AgCal::LoadXml()
{
	m_doc.Load(m_file);
	wxXmlNode* child = m_doc.GetRoot()->GetChildren();
	while (child)
	{
		if (child->GetName() == _T("dates"))
			m_dates = child;
		child = child->GetNext();
	}
}

bool AgCal::SetDate(wxDateTime date)
{
	if (m_date)
		delete m_date;
	m_date = new AgDate(date,this);
	return true;
}

AgDate* AgCal::GetDate()
{
	return m_date;
}

wxArrayInt AgCal::GetDaysWithNotes()
{
	wxArrayInt days;
	wxXmlNode* child = m_dates->GetChildren();
	while (child)
	{
		if (child->GetName() == _T("date"))
		{
			long datemonth = wxDateTime::Inv_Month;
			long dateyear = wxDateTime::Inv_Year;
			wxString str;
			str = child->GetPropVal(_T("year"),wxEmptyString);
			str.ToLong(&dateyear);
			str = child->GetPropVal(_T("month"),wxEmptyString);
			str.ToLong(&datemonth);
			if (dateyear == m_date->GetDate().GetYear() && datemonth == m_date->GetDate().GetMonth())
			{
				long dateday = 0;
				str = child->GetPropVal(_T("day"),wxEmptyString);
				str.ToLong(&dateday);
				days.Add(dateday);
			}
		}
		child = child->GetNext();
	}
	return days;
}

void AgCal::Import(wxString file)
{
	// TODO (virtuoso#1#): implement import
}

AgDate::AgDate(wxDateTime date,AgCal* cal)
{
	m_date = date;
	m_cal = cal;
	m_node = GetNode();
	if (m_node)
	{
		wxXmlNode* child = m_node->GetChildren();
		while (child)
		{
			if (child->GetName() == _T("note") )
			{
				AgNote* a_note = new AgNote(child);
				notes.Add(a_note);
			}
			child = child->GetNext();
		}
	}}

AgDate::~AgDate()
{
	if (m_node)
	{
		wxXmlNode* child  = m_node->GetChildren();
		if (!child)
		{
			m_cal->m_dates->RemoveChild(m_node);
			delete m_node;
		}
	}
}

wxXmlNode* AgDate::GetNode()
{
	wxXmlNode* child = m_cal->m_dates->GetChildren();
	while (child)
	{
		if (child->GetName() == _T("date"))
		{
			long datemonth = wxDateTime::Inv_Month;
			long dateyear = wxDateTime::Inv_Year;
			long dateday = 0;
			wxString str;
			str = child->GetPropVal(_T("year"),wxEmptyString);
			str.ToLong(&dateyear);
			str = child->GetPropVal(_T("month"),wxEmptyString);
			str.ToLong(&datemonth);
			str = child->GetPropVal(_T("day"),wxEmptyString);
			str.ToLong(&dateday);
			if (dateyear == m_date.GetYear() &&
				datemonth == m_date.GetMonth() &&
				dateday == m_date.GetDay())
					return child;
		}
		child = child->GetNext();
	}
	return NULL;
}

wxXmlNode* AgDate::CreateNode()
{
	wxXmlNode* datenode = new wxXmlNode(m_cal->m_dates,
			wxXML_ELEMENT_NODE,_T("date"));
	datenode->AddProperty(_T("year"),wxString::Format(_T("%i"),m_date.GetYear()));
	datenode->AddProperty(_T("month"),wxString::Format(_T("%i"),m_date.GetMonth()));
	datenode->AddProperty(_T("day"),wxString::Format(_T("%i"),m_date.GetDay()));
	return datenode;
}

const AgNotesArray AgDate::GetNotes()
{
	return notes;
}

bool AgDate::HasNote(wxString note)
{
	if (!m_node || note.IsEmpty())
		return false;
	wxXmlNode* child = m_node->GetChildren();
	while (child)
	{
		if (child->GetName() == _T("note") &&
			child->GetPropVal(_T("name"),wxEmptyString) == note)
			return true;
		child = child->GetNext();
	}
	return false;
}

bool AgDate::AddNote(wxString note)
{
	if (HasNote(note))
		return false;
	if (!m_node)
		m_node = CreateNode();
	wxXmlNode* notenode = new wxXmlNode(m_node,
			wxXML_ELEMENT_NODE,_T("note"));
	notenode->AddProperty(_T("name"),note);
	AgNote* a_note = new AgNote(notenode);
	notes.Add(a_note);
	return true;
}

bool AgDate::DeleteNote(wxString note)
{
	if (!m_node)
		return false;
	wxXmlNode* child  = m_node->GetChildren();
	while (child )
	{
		if (child->GetName() == _T("note") &&
			child->GetPropVal(_T("name"),wxEmptyString) == note)
		{
			for (unsigned int i = 0;i < notes.GetCount();i++)
			{
				if (notes[i]->GetName() == note)
				{
					m_node->RemoveChild(child);
					AgNote* ag_note = notes[i];
					notes.RemoveAt(i);
					delete child;
					delete ag_note;
					return true;
				}
			}
		}
		child  = child ->GetNext();
	}
	//check if m_node is empty
	child  = m_node->GetChildren();
	if (!child)
	{
		m_cal->m_dates->RemoveChild(m_node);
		delete m_node;
	}
	return false;
}

AgNote* AgDate::GetNote(wxString note)
{
	for (unsigned int i = 0;i < notes.GetCount();i++)
	{
		if (notes[i]->GetName() == note)
			return notes[i];
	}
	return NULL;
}

AgNote::AgNote(wxXmlNode* node)
{
	m_node = node;
}

AgNote::~AgNote()
{

}

const wxString AgNote::GetName()
{
	return m_node->GetPropVal(_T("name"),wxEmptyString);
}

const wxString AgNote::GetText()
{
	wxXmlNode* child = m_node->GetChildren();
	while (child)
	{
		if (child->GetName() == _T("message"))
		{
			child = child->GetChildren();
			if (child)
				return child->GetContent();
			else
				return wxEmptyString;
		}
		child =child->GetNext();
	}
	return wxEmptyString;
}

void AgNote::SetName(wxString name)
{
	//if exists
	if (m_node->HasProp(_T("name")))
	{
		wxXmlProperty* prop = m_node->GetProperties();
		while (prop)
		{
			if (prop->GetName() == _T("name"))
			{
				prop->SetValue(name);
				return;
			}
			prop =prop->GetNext();
		}

	}
	//if doesn't exists
	else
		m_node->AddProperty(_T("name"),name);
}

void AgNote::SetText(wxString text)
{
	wxXmlNode* child = m_node->GetChildren();
	wxXmlNode* message = NULL;
	while (child !=NULL && message == NULL)
	{
		if (child->GetName() == _T("message"))
			message = child;
		child =child->GetNext();
	}
	if (!message)
		message = new wxXmlNode(m_node,wxXML_ELEMENT_NODE,_T("message"));
	wxXmlNode* content = message->GetChildren();
	if (!content)
		content = new wxXmlNode(message,wxXML_TEXT_NODE,wxEmptyString);
	content->SetContent(text);
}

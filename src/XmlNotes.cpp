/***************************************************************
 * Name:      XmlNotes.cpp
 * Purpose:   New notes implementation
 * Author:    Gabriel Espinoza
 * Created:   2010-11-11
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/

#include "XmlNotes.h"
#include "AgenderMain.h"
#include <wx/filefn.h>
#include <wx/stdpaths.h>

const wxString AgCal::m_file = wxStandardPaths::Get().GetUserDataDir() + wxFILE_SEP_PATH + _T("agender.xml");
AgCal* AgCal::g_Cal = NULL;

AgCal::AgCal()
{
	if (wxFileExists(m_file))
		LoadXml();
	else
		CreateXml();
	m_date = new AgDate(wxDateTime::Now());
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
	m_date = new AgDate(date);
	return true;
}

const AgDate* AgCal::GetDate()
{
	return m_date;
}

wxArrayInt AgCal::GetDaysWithNotes()
{
	wxArrayInt days;
	// TODO (virtuoso#1#): implement
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
	}	return days;
}

void Import(wxString file)
{
	// TODO (virtuoso#1#): implement
}

AgDate::AgDate(wxDateTime date)
{
	m_date = date;
	m_node = GetNode();
}

AgDate::~AgDate()
{

}

wxXmlNode* AgDate::GetNode()
{
	wxXmlNode* child = AgCal::Get()->m_dates->GetChildren();
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
	wxXmlNode* datenode = new wxXmlNode(AgCal::Get()->m_dates,
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
	if (!m_node)
		return false;
	wxXmlNode* child = m_node->GetChildren();
	while (child)
	{
		if (child->GetName() == note)
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
	AgNote* a_note = new AgNote(notenode)
	notes.Add(a_note)	return true
}

bool AgDate::DeleteNote(wxString note)
{
	if (!m_node)
		return false;
	wxXmlNode* child  = m_node->GetChildren();
	while (child )
	{
		child
		if (child->GetName() == _T("note") &&
			child->GetPropVal(_T("name"),wxEmptyString) == note)
		{

// TODO (virtuoso#1#): eliminar child		}
		child  = child ->GetNext();
	}
}



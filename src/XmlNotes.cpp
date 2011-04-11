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
#include "AgenderCal.h"

#include <wx/filename.h>
#include <wx/stdpaths.h>
#include <wx/log.h>

#include <wx/arrimpl.cpp>
WX_DEFINE_OBJARRAY(wxDatesArray);

AgCal* AgCal::g_Cal = NULL;
#define Ag_1_0 wxStandardPaths::Get().GetConfigDataDir() + _T(".Agender-current user.txt")
#define Ag_1_1_9 wxGetHomeDir() + _T(".Agender-current user.txt")

// TODO (virtuoso#1#): implement sticky notes

AgCal::AgCal(const wxString& file)
{
	if (file.IsEmpty())
	{
		wxFileName fname;
		fname.AssignDir(wxStandardPaths::Get().GetUserDataDir());
		fname.SetName(_T("agender"));
		fname.SetExt(_T("xml"));
		m_file = fname.GetFullPath();
	}
	else
	{
		m_file = file;
	}
	if (wxFileExists(m_file))
		LoadXml();
	else
		CreateXml();
	m_date = new AgDate(wxDateTime::Now(),this);
}

AgCal::AgCal(wxXmlDocument& doc)
{
	m_doc = doc;
	m_dates = 0;
	m_date = 0;
	if (m_doc.GetRoot()->GetName() != wxT("Agender"))
	{
		//wLogError(_T("Not an agender xml file"));
		// TODO (gabriel#2#): change for throw
		return;
	}
	// TODO (gabriel#3#): move to a fuction!
	wxXmlNode* child = m_doc.GetRoot()->GetChildren();
	while (child)
	{
		if (child->GetName() == _T("dates"))
			m_dates = child;
		child = child->GetNext();
	}
	m_date = new AgDate(wxDateTime::Now(),this);
}

AgCal::~AgCal()
{
	if (this == g_Cal)
		Flush();
}

AgCal* AgCal::Get()
{
	if (g_Cal == NULL)
		g_Cal = new AgCal;
	return g_Cal;
}

AgCal* AgCal::Set(AgCal* cal)
{
	AgCal* old = g_Cal;
	g_Cal = cal;
	return old;
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
	              _("in this file Agender saves your notes, so be careful with it"));
	root->AddProperty(_T("version"),__AGENDER_VERSION__);
	m_doc.SetRoot(root);
	CreateStickyNode();
}

/** @brief CreateStickyNode
  *
  * @todo: document this function
  */
void AgCal::CreateStickyNode()
{
	m_sticky = new wxXmlNode(m_doc.GetRoot(),wxXML_ELEMENT_NODE,_T("dates"));
}

const AgNotesArray AgCal::GetStickyNotes()
{
	return snotes;
}

bool AgCal::MakeSticky(wxString note)
{
	AgNote* s_note = GetDate()->DetachNote(note);
	s_note->m_node->SetParent(m_sticky);
	snotes.Add(s_note);
	return true;
}

bool AgCal::UnStick(wxString note)
{

	return false;
}

AgNote* AgCal::GetStickyNote(wxString note)
{
	return 0;
}

void AgCal::LoadXml()
{
	m_doc.Load(m_file);
	wxXmlNode* child = m_doc.GetRoot()->GetChildren();
	while (child)
	{
		if (child->GetName() == _T("dates"))
		{
			m_dates = child;
			child = 0;
		}
		else
			child = child->GetNext();
	}
	LoadStickyNotes();
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

wxDatesArray AgCal::GetDatesWithNotes()
{
	wxDatesArray dates;
	wxXmlNode* child = m_dates->GetChildren();
	while (child)
	{
		if (child->GetName() == _T("date"))
		{
			//set
			long datemonth = wxDateTime::Inv_Month;
			long dateyear = wxDateTime::Inv_Year;
			long dateday = -1;
			wxString str;
			//read
			str = child->GetPropVal(_T("year"),wxEmptyString);
			str.ToLong(&dateyear);
			str = child->GetPropVal(_T("month"),wxEmptyString);
			str.ToLong(&datemonth);
			str = child->GetPropVal(_T("day"),wxEmptyString);
			str.ToLong(&dateday);
			//date
			wxDateTime date(dateday,(wxDateTime::Month)datemonth,dateyear);
			//add
			dates.Add(date);
		}
		child = child->GetNext();
	}
	return dates;
}


/** @brief Import1x
  *
  * @todo: document this function
  */
bool AgCal::Import1x(wxString file)
{
	AgenderCal import_cal(wxDateTime::Now(),file);
	if (true /*import_cal.IsOK()*/)
	{
		wxDatesArray d_array = import_cal.GetDatesWithNotes();
		//error
		if (d_array.GetCount() == 0)
			return false;
		for (unsigned i = 0; i < d_array.GetCount(); i++)
		{
			//get the notes in the date we are traversing
			import_cal.SetDate(d_array[i]);
			wxArrayString n_array = import_cal.GetNotes();
			//copy this date to this
			AgDate* new_date = new AgDate(import_cal.GetDate(),this);
			for (unsigned j = 0; j < n_array.GetCount(); j++)
			{
				//if note doesn't exist in this copy it
				if (!new_date->HasNote(n_array[j]))
				{
					new_date->AddNote(n_array[j]);
					new_date->GetNote(n_array[j])->SetText(import_cal.GetNoteText(n_array[j]));
				}
			}
			//clean memory
			delete new_date;
		}
		//success
		Flush();
		return true;
	}
	return false;
}

bool AgCal::ImportXml(wxString file)
{
	//import the requested file
	wxXmlDocument import_doc;
	if (import_doc.Load(file))
	{
		AgCal import_cal(import_doc);
		//gets ALL dates that have a note
		wxDatesArray d_array = import_cal.GetDatesWithNotes();
		for (unsigned i = 0; i < d_array.GetCount(); i++)
		{
			//get the notes in the date we are traversing
			import_cal.SetDate(d_array[i]);
			AgNotesArray n_array = import_cal.GetDate()->GetNotes();
			//copy this date to this
			AgDate* new_date = new AgDate(import_cal.GetDate()->GetDate(),this);
			for (unsigned j = 0; j < n_array.GetCount(); j++)
			{
				//if note doesn't exist in this copy it
				if (!new_date->HasNote(n_array[j]->GetName()))
				{
					new_date->AddNote(n_array[j]->GetName());
					new_date->GetNote(n_array[j]->GetName())->SetText(n_array[j]->GetText());
				}
			}
			//clean memory
			delete new_date;
		}
		//success
		Flush();
		return true;
	}
	//failed
	return false;
}

void AgCal::Import(wxString file)
{
	if (!ImportXml(file))
	{
		wxLogMessage(_T("Not xml"));
		if (!Import1x(file))
		{
			wxLogError(_T("not a valid Agender file"));
			return;
		}
	}
	// TODO (gabriel#1#): send a message to update the gui
	wxLogMessage(_T("Finished importing file: '%s'"),file.c_str());
}

void AgCal::Export(wxString file)
{
	m_doc.Save(file);
}

void AgCal::LoadStickyNotes()
{
	wxXmlNode* child = m_doc.GetRoot()->GetChildren();
	while (child)
	{
		if (child->GetName() == _T("sticky"))
		{
			m_sticky = child;
			wxXmlNode* note = child->GetChildren();
			while (note)
			{
				if (note->GetName() == _T("note"))
				{
					snotes.Add(new AgNote(note));
				}
				note = note->GetNext();
			}
			return;
		}
		else
			child = child->GetNext();
	}
	CreateStickyNode();
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
	}
}

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

AgNote* AgDate::DetachNote(const wxString& note)
{
	AgNote* d_note = GetNote(note);
	notes.Remove(d_note);
	return d_note;
}

const AgNotesArray AgDate::GetNotes()
{
	return notes;
}

bool AgDate::HasNote(const wxString& note)
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

bool AgDate::AddNote(const wxString& note)
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

bool AgDate::DeleteNote(const wxString& note)
{
	if (!m_node)
		return false;
	wxXmlNode* child  = m_node->GetChildren();
	while (child )
	{
		if (child->GetName() == _T("note") &&
		        child->GetPropVal(_T("name"),wxEmptyString) == note)
		{
			for (unsigned int i = 0; i < notes.GetCount(); i++)
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

AgNote* AgDate::GetNote(const wxString& note)
{
	for (unsigned int i = 0; i < notes.GetCount(); i++)
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

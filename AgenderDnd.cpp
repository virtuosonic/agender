/***************************************************************
 * Name:      AgenderDnd.cpp
 * Purpose:   Code for Drag & Drop support
 * Author:    Gabriel Espinoza
 * Copyright: Gabriel Espinoza
 * License: GPL 3
 **************************************************************/
#include "AgenderDnd.h"

#if wxUSE_DRAG_AND_DROP

wxDragResult NoteTarget::OnData(wxCoord x,wxCoord y,wxDragResult def)
{
	if (!GetData())
		return wxDragError;
	NoteTarget* pNote = NULL;
	pNote = (NoteTarget*)m_dataObject;
	if (pNote == NULL)
		return wxDragNone;
	//
	return def;
}

bool NoteDataObject::SetData(const wxDataFormat& format,size_t len,const void* buf)
{

}

bool NoteDataObject::GetDataHere(const wxDataFormat& format,void* pBuf)
{

}

size_t NoteDataObject::GetDataSize(const wxDataFormat& format)
{

}

void NoteDataObject::GetAllFormats(wxDataFormat* formats,Direction dir)
{
	wxDataFormat fmtTxt(wxDF_TEXT);
	wxDataFormat fmtTxt(_T("AgNote"));
}

}

size_t NoteDataObject::GetFormatCount(Direction dir)
{
	return 2;
}

wxDataFormat NoteDataObject::GetPreferedFormat(Direction dir)
{

}

 NoteDataObject::~NoteDataObject()
{

}

 NoteDataObject::NoteDataObject(const wxString& note, const wxString& noteText) : m_note(note),
	m_noteText(noteText)
{
}

#endif //wxUSE_DRAG_AND_DROP

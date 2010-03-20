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

NoteDataObject::NoteDataObject(wxString noteName,wxString noteText)
{
	m_noteName = noteName;
	m_noteText = noteText;
}

bool NoteDataObject::SetData(const wxDataFormat& format, size_t len,const void* buf)
{

}

bool NoteDataObject::GetDataHere(const wxDataFormat& format,void* pBuf)
{

}

size_t NoteDataObject::GetDataSize(const wxDataFormat& format)
{

}

void NoteDataObject::GetAllFormats(wxDataFormat *formats,Direction dir)
{

}

size_t NoteDataObject::GetFormatCount(Direction dir)
{
	return 1;
}

wxDataFormat NoteDataObject::GetPreferredFormat(Direction WXUNUSED(dir))
{
	return m_agFormat;
}





#endif //wxUSE_DRAG_AND_DROP

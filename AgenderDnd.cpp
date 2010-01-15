#include "AgenderDnd.h"

#if wxUSE_DRAG_AND_DROP

wxDragResult NoteTarget::OnData(wxCoord x,wxCoord y,wxDragResult def)
{
	if (!GetData())
		return wxDragError;
	NoteTarget* pNote = NULL;
	note = (NoteTarget*)m_dataObject;
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

}

size_t NoteDataObject::GetFormatCount(Direction dir)
{

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

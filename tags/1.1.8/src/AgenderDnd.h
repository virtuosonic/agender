/***************************************************************
 * Name:      AgenderDnd.h
 * Purpose:   Defines Classes for using Drag & Drop
 * Author:    Gabriel Espinoza (virtuosonic@users.sourceforge.net)
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/

#ifndef AGENDERDND_H_INCLUDED
#define AGENDERDND_H_INCLUDED

#include <wx/defs.h>

#if wxUSE_DRAG_AND_DROP

#include <wx/dnd.h>
#include <wx/datetime.h>

struct notedmp
{
	wxString name;
	wxString text;
};

class NoteDataObject : public wxDataObject
{
	public:
		NoteDataObject(wxString noteName,wxString noteText);
		//no destructor needed?
		virtual wxDataFormat GetPreferredFormat(Direction WXUNUSED(dir));
		virtual size_t GetFormatCount(Direction dir);
		virtual void GetAllFormats(wxDataFormat *formats,Direction dir);
		virtual size_t GetDataSize(const wxDataFormat& format);
		virtual bool GetDataHere(const wxDataFormat& format,void* pBuf);
		virtual bool SetData(const wxDataFormat& format, size_t len,const void* buf);
	private:
		wxString m_noteName,m_noteText;
		wxDataFormat m_agFormat;
};

class NoteTarget : public wxDropTarget
{
		virtual wxDragResult OnEnter(wxCoord x,wxCoord y,wxDragResult def);
		virtual void OnLeave();
		virtual wxDragResult OnData(wxCoord x,wxCoord y,wxDragResult def);
};

#endif //wxUSE_DRAG_AND_DROP
#endif // AGENDERDND_H_INCLUDED

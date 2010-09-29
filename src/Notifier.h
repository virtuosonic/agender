/***************************************************************
 * Name:      Notifier.h
 * Purpose:   Defines Notifier Class
 * Author:    Gabriel Espinoza (virtuosonic@users.sourceforge.net)
 * Created:   2010-09-24
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef _NOTIFIER_H_
#define _NOTIFIER_H_

#include <wx/timer.h>
#include <wx/datetime.h>
#include <wx/dynarray.h>

//WX_DEFINE_ARRAY_PTR(wxDateSpan*,DateSpanArray)

class Notifier : public wxTimer
{
	public:
		Notifier();
		~Notifier();
		void Notify();
	private:
		void GetNext();
};

#endif // _NOTIFIER_H_

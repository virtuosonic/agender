/***************************************************************
 * Name:      wxAutoStart.h
 * Purpose:   Defines for AutoStart
 * Author:    Gabriel Espinoza
 * Created:   2010-09-06
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#ifndef _WXAUTOSTART_H_
#define _WXAUTOSTART_H_

#include <wx/platform.h>

class AutoStart
{
	public:
		AutoStart();
		~AutoStart();
		bool Get();//not implemented
		/*set auto start to on or off*/
		bool Set(bool on);
	private:
		void OutputError();
#if defined __UNIX__ && !defined __APPLE__
		//freedesktop.org
		bool SetXDG();
		bool UnSetXDG();
		//Fluxbox
		bool SetFluxbox();
		bool UnSetFluxbox();
		//IceWM
		bool SetIceWM();
		bool UnSetIceWM();
		//Windows
#elif defined __WXMSW__
		bool SetWindows();
		bool UnSetWindows();
#endif
		//members
};

#endif // _WXAUTOSTART_H_

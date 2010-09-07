/***************************************************************
 * Name:      wxAutoStart.h
 * Purpose:   Defines for AutoStart
 * Author:    Gabriel Espinoza
 * Created:   2010-09-06
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#include "wxAutoStart.h"
#include <wx/string.h>
#include <wx/textfile.h>
#include <wx/intl.h>
#include <wx/utils.h>
#ifdef __WXMSW__
#include <wx/msw/registry.h>
#endif//__WXMSW__

 AutoStart::AutoStart()
{

}

AutoStart::~AutoStart()
{

}

void AutoStart::OutputError()
{
	wxString::Format(
				_("AutoStart is only available under Windows, Fluxbox "
				   " and Unix desktops that follow the freedesktop.org standards. "//how sadly! =(
				   "If you add support for any other system, please send patches "
				   "to the patch tracker in the Agender project page at "
				   "http://sourceforge.net/projects/agender/ or you can also help "
				   "donating hardware that runs your favorite system."));
}

bool AutoStart::Get()
{
	return false;
}

bool AutoStart::Set(bool on)
{
	#if defined __UNIX__ && !defined __APPLE__
	if (on)
		return SetFluxbox() || SetIceWM() || SetXDG();
	else
		return UnSetFluxbox() || UnSetIceWM() || UnSetXDG();
	#elif defined __WXMSW__
	if (on)
		return SetWindows();
	else
		return UnSetWindows();
	#else
		OutputError();
		return false;
	#endif
}

#ifdef __WXMSW__
bool AutoStart::SetWindows()
{
	//we use the windows registry
	wxRegKey key;
	key.SetName(_T("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	wxString AgenderValue;
	key.QueryValue(_T("Agender"),AgenderValue);
	if (!key.HasValue(_T("Agender")) || AgenderValue != wxStandardPaths::Get().GetExecutablePath())
		key.SetValue(_T("Agender"),wxStandardPaths::Get().GetExecutablePath());
	return true;
}

bool AutoStart::UnSetWindows()
{
	wxRegKey key;
	key.SetName(_T("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	if (key.HasValue(_T("Agender")))
			key.DeleteValue(_T("Agender"));
}
#endif

#if defined __UNIX__ && !defined __APPLE__
bool AutoStart::SetFluxbox()
{
	wxString  fluxFile;fluxFile << wxGetHomeDir() << _T("/.fluxbox/startup");
	wxTextFile startflux;
	if (startflux.Open(fluxFile))
	{
		wxString command;
		int indx = -1;
		bool alreadyThere = false;
		for (command = startflux.GetLastLine(); startflux.GetCurrentLine() > 0;
				command = startflux.GetPrevLine())
		{
			if (command.Matches(_T("exec*fluxbox*")))
				indx = startflux.GetCurrentLine();
			if (command.Matches(_T("Agender &")))
				alreadyThere = true;
		}
		if (indx > -1 && !alreadyThere)
		{
			startflux.InsertLine(_T("Agender &"),indx);
			startflux.Write();
		}
		startflux.Close();
	}
	return true;
}

bool AutoStart::UnSetFluxbox()
{
	wxString  fluxFile;fluxFile << wxGetHomeDir() << _T("/.fluxbox/startup");
	//clean fluxbox startup script
	wxTextFile startflux;
	if (startflux.Open(fluxFile))
	{
		wxString command;
		for (command = startflux.GetLastLine(); startflux.GetCurrentLine() > 0;
				command = startflux.GetPrevLine())
		{
			if (command.Matches(_T("Agender &")))
			{
				startflux.RemoveLine(startflux.GetCurrentLine());
			}
		}
		startflux.Write();
		startflux.Close();
	}
	return true;
}

bool AutoStart::SetXDG()
{
	wxString desktopFile;desktopFile << wxGetHomeDir() << _T(".config/autostart/Agender.desktop");
	//freedesktop.org
	if (!wxFileExists(desktopFile))
	{
		//lets use the easyest way
		wxTextFile desktop;
		desktop.Create(desktopFile);
		desktop.AddLine(_T("[Desktop Entry]"));
		desktop.AddLine(_T("Type=Application"));
		desktop.AddLine(_T("Name=Agender"));
		desktop.AddLine(_T("Exec=Agender"));
		desktop.AddLine(_T("Icon=Agender"));
		desktop.Write(wxTextFileType_Unix);//needed?
		desktop.Close();
	}
	return true;
}

bool AutoStart::UnSetXDG()
{
	wxString desktopFile;desktopFile << wxGetHomeDir() << _T(".config/autostart/Agender.desktop");
	if (wxFileExists(desktopFile))
			wxRemoveFile(desktopFile);
	return true;
}

bool AutoStart::SetIceWM()
{
	wxString  IceFile;IceFile << wxGetHomeDir() << _T("/.icewm/startup");
	//add a command to run Agender to the icewm  startup script
	wxTextFile startice;
	if (startice.Open(IceFile))
	{
		wxString command;
		bool alreadyThere = false;
		for (command = startice.GetLastLine(); startice.GetCurrentLine() > 0;
				command = startice.GetPrevLine())
		{
			if (command.Matches(_T("Agender &")))
				alreadyThere = true;
		}
		if (!alreadyThere)
		{
			startice.AddLine(_T("Agender &"));
			startice.Write();
		}
		startice.Close();
	}
	return true;
}

bool AutoStart::UnSetIceWM()
{
	wxString  IceFile;IceFile << wxGetHomeDir() << _T("/.icewm/startup");
	//clean icewm startup script
	wxTextFile startice;
	if (startice.Open(IceFile))
	{
		wxString command;
		for (command = startice.GetLastLine(); startice.GetCurrentLine() > 0;
				command = startice.GetPrevLine())
		{
			if (command.Matches(_T("Agender &")))
			{
				startice.RemoveLine(startice.GetCurrentLine());
			}
		}
		startice.Write();
		startice.Close();
	}
	return true;
}
#endif

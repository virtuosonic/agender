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
#include <wx/utils.h>
#include <wx/msgdlg.h>
#include <wx/log.h>
#include <wx/app.h>
#include <wx/stdpaths.h>

#if defined __UNIX__ && !defined __APPLE__
#include <wx/textfile.h>
#endif//__UNIX__ && !defined __APPLE__

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
	wxMessageBox(wxString::Format(
	                 _("AutoStart is only available under %s \
			and Unix desktops that follow the freedesktop.org standards. \
			If you add support for any other system, please send patches \
			to the patch tracker in the Agender project page at \
			http://sourceforge.net/projects/agender/ or you can also help \
			donating hardware that runs your favorite system."),
	                 _T("Windows, Fluxbox, IceWM")),
	             _("Error setting auto start"));
	/*how sadly! =(*/
}

bool AutoStart::Get()
{
	return true;
}

bool AutoStart::Set(bool on)
{
#if defined __UNIX__ && !defined __APPLE__
	if (on)
	{
		bool return_value[3];
		return_value[0] = SetFluxbox();
		return_value[1] = SetIceWM();
		return_value[2] = SetXDG();
		if (!return_value[0] && !return_value[1] && !return_value[2])
			OutputError();
		return return_value[0] ||return_value[1] ||return_value[2];
	}
	else
	{
		bool return_value[3];
		return_value[0] = UnSetFluxbox();
		return_value[1] = UnSetIceWM();
		return_value[2] = UnSetXDG();
		return return_value[0] ||return_value[1] ||return_value[2];
	}
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
	wxString AutoStartValue;
	key.QueryValue(wxTheApp->GetAppName(),AutoStartValue);
	if (!key.HasValue(wxTheApp->GetAppName()) || AutoStartValue != wxStandardPaths::Get().GetExecutablePath())
		key.SetValue(wxTheApp->GetAppName(),wxStandardPaths::Get().GetExecutablePath());
	return true;
}

bool AutoStart::UnSetWindows()
{
	wxRegKey key;
	key.SetName(_T("HKEY_CURRENT_USER\\Software\\Microsoft\\Windows\\CurrentVersion\\Run"));
	if (key.HasValue(wxTheApp->GetAppName()))
		key.DeleteValue(wxTheApp->GetAppName());
	return true;
}

#elif defined __UNIX__ && !defined __APPLE__
bool AutoStart::SetFluxbox()
{
	wxString  fluxFile;
	fluxFile << wxGetHomeDir() << _T("/.fluxbox/startup");
	wxLogMessage(_T("Adding \"Agender &\" to %s"),fluxFile.c_str());
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
			{
				alreadyThere = true;
				wxLogMessage(_T("Already there at line: %i"),startflux.GetCurrentLine());
			}
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
	wxString  fluxFile;
	fluxFile << wxGetHomeDir() << _T("/.fluxbox/startup");
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
	wxString desktopFile;
	desktopFile << wxGetHomeDir()
	            << _T("/.config/autostart/")
	            << wxTheApp->GetAppName()
	            << _T(".desktop");
	wxLogMessage(_T("Creating %s"),desktopFile.c_str());
	//freedesktop.org
	if (!wxFileExists(desktopFile))
	{
		//lets use the easyest way
		wxTextFile desktop;
		desktop.Create(desktopFile);
		desktop.AddLine(_T("[Desktop Entry]"));
		desktop.AddLine(_T("Type=Application"));
		desktop.AddLine(_T("Name=Agender"));
		desktop.AddLine(_T("Exec=Agender --session-start"));
		desktop.AddLine(_T("Icon=Agender"));
		desktop.Write(wxTextFileType_Unix);//needed?
		desktop.Close();
	}
	else
	{
		wxLogMessage(_T("The file exists"));
	}
	return true;
}

bool AutoStart::UnSetXDG()
{
	wxString desktopFile;
	desktopFile << wxGetHomeDir()
	            << _T("/.config/autostart/")
	            << wxTheApp->GetAppName()
	            << _T(".desktop");
	if (wxFileExists(desktopFile))
		wxRemoveFile(desktopFile);
	return true;
}

bool AutoStart::SetIceWM()
{
	wxString  IceFile;
	IceFile << wxGetHomeDir() << _T("/.icewm/startup");
	//add a command to run Agender to the icewm  startup script
	wxLogMessage(_T("Adding \"Agender &\" to %s"),IceFile.c_str());
	wxTextFile startice;
	if (startice.Open(IceFile))
	{
		wxString command;
		bool alreadyThere = false;
		for (command = startice.GetLastLine(); startice.GetCurrentLine() > 0;
		        command = startice.GetPrevLine())
		{
			if (command.Matches(_T("Agender &")))
			{
				alreadyThere = true;
				wxLogMessage(_T("Already there at line: %i"),startice.GetCurrentLine());
			}
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
	wxString  IceFile;
	IceFile << wxGetHomeDir() << _T("/.icewm/startup");
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

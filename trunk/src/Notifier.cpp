/***************************************************************
 * Name:      Notifier.cpp
 * Purpose:   Code for Notes Notifications
 * Author:    Gabriel Espinoza
 * Created:   2010-09-24
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#include "Notifier.h"
#include <wx/log.h>
#include <wx/config.h>
#include <wx/sound.h>

// TODO (virtuoso#1#): implement notifications

class Alarm : public wxTimer
{
	void Notify()
	{
		wxLogVerbose(_T("ringing"));
		wxSound::Play(wxString(_T("../share/14262_xyzr_kx_alarm_clock.wav")));
	}
};

Notifier::Notifier()
{
	m_alarm = new Alarm;
}

Notifier::~Notifier()
{
	delete m_alarm;
}

void Notifier::Notify()
{
	bool test_bool;
	wxConfig::Get()->Read(_T("/notify"),&test_bool,false);
	if (test_bool)
	{
		wxLogVerbose(_T("runing"));
		m_alarm->Start(5000);
	}
}

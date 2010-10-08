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

Notifier::Notifier()
{

}

Notifier::~Notifier()
{

}

void Notifier::Notify()
{
	bool test_bool;
	wxConfig::Get()->Read(_T("/notify"),&test_bool,false);
	if (test_bool)
	{
		wxLogVerbose(_T("runing"));
	}
}

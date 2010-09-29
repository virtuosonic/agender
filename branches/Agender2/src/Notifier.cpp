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

Notifier::Notifier()
{

}

Notifier::~Notifier()
{

}

void Notifier::Notify()
{
	wxLogVerbose(_T("runing"));
}

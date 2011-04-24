/***************************************************************
 * Name:      AboutDialog.cpp
 * Purpose:   New about dialog
 * Author:    Gabriel Espinoza
 * Created:   2010-12-31
 * Copyright: Gabriel Espinoza
 * License: GPLv3+
 **************************************************************/
#include "AboutDialog.h"
//#include "version.h"

#include <wx/build.h>
#include <wx/stdpaths.h>
#include <wx/filename.h>
#include <wx/image.h>

#include "version.h"

//(*InternalHeaders(AboutDialog)
#include <wx/intl.h>
#include <wx/string.h>
//*)

namespace Agender {

//(*IdInit(AboutDialog)
const long AboutDialog::ID_STATICBITMAP1 = wxNewId();
const long AboutDialog::ID_HTMLWINDOW1 = wxNewId();
const long AboutDialog::ID_HTMLWINDOW3 = wxNewId();
const long AboutDialog::ID_HTMLWINDOW4 = wxNewId();
const long AboutDialog::ID_TEXTCTRL1 = wxNewId();
const long AboutDialog::ID_NOTEBOOK1 = wxNewId();
//*)

BEGIN_EVENT_TABLE(AboutDialog,wxDialog)
	EVT_HTML_LINK_CLICKED(AboutDialog::ID_HTMLWINDOW1,AboutDialog::OnLink)
	EVT_HTML_LINK_CLICKED(AboutDialog::ID_HTMLWINDOW3,AboutDialog::OnLink)
	EVT_HTML_LINK_CLICKED(AboutDialog::ID_HTMLWINDOW4,AboutDialog::OnLink)
	//(*EventTable(AboutDialog)
	//*)
END_EVENT_TABLE()

AboutDialog::AboutDialog(wxAboutDialogInfo& info,wxWindow* parent)
{
	//(*Initialize(AboutDialog)
	wxHtmlWindow* HtmlWindow3;
	wxNotebook* Notebook1;
	wxStaticBitmap* StaticBitmap1;
	wxHtmlWindow* HtmlWindow4;
	wxHtmlWindow* HtmlWindow1;
	wxTextCtrl* TextCtrl1;
	wxFlexGridSizer* FlexGridSizer1;

	Create(parent, wxID_ANY, _("About Agender"), wxDefaultPosition, wxDefaultSize, wxDEFAULT_DIALOG_STYLE, _T("wxID_ANY"));
	SetClientSize(wxSize(390,344));
	FlexGridSizer1 = new wxFlexGridSizer(0, 1, 0, 0);
	StaticBitmap1 = new wxStaticBitmap(this, ID_STATICBITMAP1, wxNullBitmap, wxDefaultPosition, wxDefaultSize, 0, _T("ID_STATICBITMAP1"));
	FlexGridSizer1->Add(StaticBitmap1, 1, wxBOTTOM|wxEXPAND|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	Notebook1 = new wxNotebook(this, ID_NOTEBOOK1, wxDefaultPosition, wxSize(370,288), 0, _T("ID_NOTEBOOK1"));
	HtmlWindow1 = new wxHtmlWindow(Notebook1, ID_HTMLWINDOW1, wxDefaultPosition, wxSize(335,237), wxHW_SCROLLBAR_AUTO, _T("ID_HTMLWINDOW1"));
	HtmlWindow3 = new wxHtmlWindow(Notebook1, ID_HTMLWINDOW3, wxPoint(159,6), wxDefaultSize, wxHW_SCROLLBAR_AUTO, _T("ID_HTMLWINDOW3"));
	HtmlWindow4 = new wxHtmlWindow(Notebook1, ID_HTMLWINDOW4, wxPoint(-46,17), wxDefaultSize, wxHW_SCROLLBAR_AUTO, _T("ID_HTMLWINDOW4"));
	TextCtrl1 = new wxTextCtrl(Notebook1, ID_TEXTCTRL1, wxEmptyString, wxPoint(272,14), wxDefaultSize, wxTE_AUTO_SCROLL|wxTE_MULTILINE|wxTE_READONLY|wxTE_AUTO_URL, wxDefaultValidator, _T("ID_TEXTCTRL1"));
	Notebook1->AddPage(HtmlWindow1, _("Info"), false);
	Notebook1->AddPage(HtmlWindow3, _("Thanks"), false);
	Notebook1->AddPage(HtmlWindow4, _("Donate"), false);
	Notebook1->AddPage(TextCtrl1, _("License"), false);
	FlexGridSizer1->Add(Notebook1, 1, wxALL|wxALIGN_CENTER_HORIZONTAL|wxALIGN_CENTER_VERTICAL, 5);
	SetSizer(FlexGridSizer1);
	FlexGridSizer1->SetSizeHints(this);
	//*)
	//licence
	TextCtrl1->SetValue(info.GetLicence());
	//info
	{
		wxString infoStr;
		infoStr << _T("<html><body>")
		<< _T("<center><h2>")
		<< info.GetName()
		<< _T(" ")
		<< info.GetVersion()
		<< _T("</h2>")
		<< _T("<h5>")
		<< info.GetCopyrightToDisplay()
		<< _T("</h5>")
		<< _T("<a href=http://agender.sourceforge.net>Agender website</a> ")
		<< _T("<a href=http://virtuosonicplusplus.blogspot.com>virtuosonic++</a>")
		<< _T("</center>")
		<< _T("<h6>")
		<< _("A cross-platform schedule tool!")
		<< _T("</h6>")
		<< _T("<p align=justify>")
		<< _("Agender is a small cross-platform schedule tool where you asociate some notes with a date or with no date in particular if  you mark the note as sticky, you simply start it  and it will create a taskbar icon and stay in the background, without anoying you, it can also be configured to run on login.")
		<< _T("</p>")
		<< _T("<br><br>")
		<< _T("<strong>")
		<< _T("Licensed to: ")
		<< _T("</strong>")
		<< wxGetUserName()
		<< _T("<br><br>")
		<< _T("<strong>")
		<< _("Build: ")
		<< _T("</strong>")
		<< __TDATE__
		<< _T(" ")
		<< __TTIME__
		<< _T("<br>")
		<< _T("<strong>")
		<< _("Revision: ")
		<< _T("</strong>")
		<< _T(" svn")
		<< wxString::FromAscii(SVN_REVISION)
		<< _T(" ")
		<< wxString::FromAscii(SVN_DATE)
		<< _T("<br>")
		<< _T("<strong>")
		<< _T("Runing on: ")
		<< _T("</strong>")
		<< wxGetOsDescription()
		<< _T("<br>")
		<< wxVERSION_STRING
		<< _T(" ")
		<< _T(__WX_BO_UNICODE)
		<< _T(__WX_BO_COMPILER)
		<< _T("</body></html>");
		HtmlWindow1->SetPage(infoStr);
	}
	//thanks
	{
		wxString thStr;
		thStr  << _T("<html><body>")
		<< _T("<h5>Hackers</h5>")
		<< _T("<ul>")
		<< _T("<li>Gabriel Espinoza <virtuosonic@users.sourceforge.net> - Created the powerful Agender")
		<< _T("<li>Jason Cervantes - helped with multiuser in the windows installer")
		<< _T("<li>Greg Fraley (GrenadeGuy) - Created a deb package of Agender 1.1.5")
		<< _T("</ul>")
		<< _T("<h5>Translators</h5>")
		<< _T("<ul>")
		<< _T("<li>Gabriel Espinoza <virtuosonic@users.sourceforge.net> : spanish")
		<< _T("<li>Ester Espinoza : deutsch")
		<< _T("<li>Florian Haag <fhaag@users.sourceforge.net> : deutsch")
		<< _T("<li>Daniel Daows : japanese")
		<< _T("<li>Miguel Haruki Yamaguchi <mhy@users.sourceforge.net> : japanese")
		<< _T("<li>Pedro Silva <pbsilva@users.sourceforge.net> : portuguese")
		<< _T("<li>Georgios Petsagourakis : greek")
		<< _T("<li>Rickard Hedlund <bigricke@hotmail.com> : swedish")
		<< _T("<li>Bruno Mace : french")
		<< _T("<li>Ianar&eacute; S&eacute;vi : french")
		<< _T("<li>senoutouya <senoutouya@gmail.com> : chinese")
		<< _T("<li>Adi D. <nevvermind@users.sourceforge.net> : romanian")
		<< _T("<li>Itamar Shoham <itsho@users.sourceforge.net> : hebrew")
		<< _T("</ul>")
		<< _T("<h5>Sounds</h5>")
		<< _T("<ul>")
		<< _T("<li>xyzr_kx from Freesound Project")
		<< _T("</ul>")
		<< _T("</<body></html>");
		HtmlWindow3->SetPage(thStr);
	}
	//donate

	{
		wxString donateStr;
		donateStr << _T("<html><body><h5>")
		<< _T("<p align=justify>")
		<< _("If you like Agender consider making a donation, that way you will help the development of Agender")
		<< _T("</p>")
		<< _T("</h5><a href=http://sourceforge.net/donate/index.php?group_id=271084>")
		<< _T("<img src=\"")
		<< wxStandardPaths::Get().GetResourcesDir()
		<< wxFILE_SEP_PATH
		<< _T("project-support.jpg\">")
		<< _T("</a>")
		<< _T("</<body></html>");
		HtmlWindow4->SetPage(donateStr);
//		, we will also add you to the
//Hall of Fame and link to your website if you like so, you can also help reporting
//<a href="http://sourceforge.net/tracker/?group_id=271084&atid=1152801">bugs</a>,
//posting a <a href="http://sourceforge.net/projects/agender/">review</a> or
//<a href="http://sourceforge.net/apps/mediawiki/agender/index.php?title=Translating">
//translating</a> it to more languages
	}
	//bitmap
	StaticBitmap1->SetBitmap(wxBitmap(wxStandardPaths::Get().GetResourcesDir()+
			wxFILE_SEP_PATH+wxT("hdr.png"),wxBITMAP_TYPE_PNG));
	FlexGridSizer1->Fit(this);
}

AboutDialog::~AboutDialog()
{
	//(*Destroy(AboutDialog)
	//*)
}

/** @brief OnLink
  *
  * @todo: document this function
  */
void AboutDialog::OnLink(wxHtmlLinkEvent& event)
{
	wxLaunchDefaultBrowser(event.GetLinkInfo().GetHref());
}
}//namespace Agender

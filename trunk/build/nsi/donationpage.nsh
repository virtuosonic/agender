#!/usr/bin/makensis
;Name: donationpage.nsh
;Purpose: code for donate page
;Author: Gabriel Espinoza
;License: GPLv3+
;Created: 10-mar-2011

;
;	requires:
;		MUI2.nsh
;
;
;	Usage:
;
;		!define DONATE_LINK "http://virtuosonic.users.sf.net"
;		!insertmacro VS_PAGE_DONATE
;

!macro VS_PAGE_DONATE
	Page custom DonateDialog DonateLeave
!macroend



Var donateDialog
Var Label
Var Button
Var Check
Var Checkbox_State

Function DonateDialog
	;title
	!insertmacro MUI_HEADER_TEXT "Make a donation" "Put some coffee in this hacker veins."
	;create
	nsDialogs::Create 1018
	Pop $donateDialog
	${If} $donateDialog == error
		Abort
	${EndIf}
	;label
	${NSD_CreateLabel} 0 0 100% 40u "Agender is free of charge, \
	but if you want you can invite me a coffee via paypal, \
	to tell me how much you like it."
	Pop $Label
	;button
	${NSD_CreateButton} 120u 50u 70u 18u "Donate now!"
	Pop $Button
	${NSD_OnClick} $Button OnDonateButton
	;checkboxxxxxxxxxxx
	${NSD_CreateCheckBox} 0 90% 100% 12u "Maybe later(check this to continue with the install)"
	Pop $Check
	${If} $Checkbox_State == ${BST_CHECKED}
		${NSD_Check} $Check
	${Else}
		GetDlgItem $0 $HWNDPARENT 1
		EnableWindow $0 0
	${EndIf}
	${NSD_OnClick} $Check OnCheck

	nsDialogs::Show

FunctionEnd

Function OnCheck
	${NSD_GetState} $Check $Checkbox_State
	${If} $Checkbox_State == ${BST_CHECKED}
		GetDlgItem $0 $HWNDPARENT 1
		EnableWindow $0 1
	${EndIf}
FunctionEnd

Function DonateLeave
	${NSD_GetState} $Check $Checkbox_State
FunctionEnd

Function OnDonateButton
	ExecShell "open" ${DONATE_LINK}
	GetDlgItem $0 $HWNDPARENT 1
	EnableWindow $0 1
FunctionEnd

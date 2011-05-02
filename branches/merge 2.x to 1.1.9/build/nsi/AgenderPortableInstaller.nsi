#!/usr/bin/makensis
;Name: AgenderPortableInstaller.nsi
;Purpose: Installs the portable edition of Agender
;Author: Gabriel Espinoza
;License: GPLv3+
;Created: 09-mar-2011

!include "MUI2.nsh"
!include "shareddefinitions.nsh"
!include "donationpage.nsh"
!cd "..\.."
!tempfile PACKHDRTEMP
!packhdr "${PACKHDRTEMP}" '"${UPX}" -9 "${PACKHDRTEMP}"'
;pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "gpl-3.0.txt"
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro VS_PAGE_DONATE
!insertmacro MUI_PAGE_INSTFILES
; Finish page
;!define MUI_FINISHPAGE_RUN "$INSTDIR\Agender Portable.exe"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\App\Readme.txt"
!define MUI_FINISHPAGE_LINK "Visit our website and support the development of Agender"
!define MUI_FINISHPAGE_LINK_LOCATION "${PRODUCT_WEB_SITE}"
!insertmacro MUI_PAGE_FINISH
; Language files
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "Spanish"
!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "Japanese"
!insertmacro MUI_LANGUAGE "Swedish"
!insertmacro MUI_LANGUAGE "Greek"
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "Portuguese"
!insertmacro MUI_LANGUAGE "TradChinese"
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_LANGUAGE "Romanian"
!insertmacro MUI_LANGUAGE "Hebrew"
; ReserveFiles
!insertmacro MUI_RESERVEFILE_LANGDLL
; MUI end ------
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}, Portable Edition"
OutFile "${PRODUCT_NAME} Portable-${PRODUCT_VERSION}.exe"
InstallDir  "\Agender"
ShowInstDetails show

InstType "Full"
InstType "Minimal"
InstType "Minimal+Detected language translation"
;version information
VIProductVersion "1.0.0.0"
VIAddVersionKey "ProductName" ${PRODUCT_NAME}
VIAddVersionKey "Comments" "A cross-platform schedule tool"
VIAddVersionKey "CompanyName" ${PRODUCT_PUBLISHER}
VIAddVersionKey "LegalCopyright" "Copyright © 2009-2011 Gabriel Espinoza"
VIAddVersionKey "FileDescription" "The ${PRODUCT_NAME} installer"
VIAddVersionKey "FileVersion" ${PRODUCT_VERSION}
VIAddVersionKey "ProductVersion" ${PRODUCT_VERSION}

Section "Agender" SEC01
	SectionIn RO
	SetOverwrite ifdiff
	;launcher
	SetOutPath "$INSTDIR"
	File "Agender Portable.exe"
	;executable
	SetOutPath "$INSTDIR\App"
	File "${Ag_EXE}"
	File "${C_RUNTIME}"
	;Icon
	File "share\project-support.jpg"
	File "share\hdr.png"
	;please read it
	File "Readme.txt"
	File "gpl-3.0.txt"
	File "ChangeLog.txt"
SectionEnd

!macro langSection l_iso l_name
	Section "${l_name}" sec_${l_iso}
		SectionIn 1
		SetOutPath "$INSTDIR\App\${l_iso}"
		File /oname=Agender.mo "po\${l_iso}.mo"
	SectionEnd
!macroend

SectionGroup "Translations" SEC02
	;translations
	!insertmacro langSection zh_CN "Chinese (Simplified)"
	!insertmacro langSection zh_HK "Chinese (Traditional)"
	!insertmacro langSection he "Hebrew"
	!insertmacro langSection fr "French"
	!insertmacro langSection de "German"
	!insertmacro langSection el "Greek"
	!insertmacro langSection ja "Japanese"
	!insertmacro langSection pt "Portuguese"
	!insertmacro langSection ro "Romanian"
	!insertmacro langSection es "Spanish"
	!insertmacro langSection sv "Swedish"
SectionGroupEnd

!macro SetInstType2Lang l_id sec finish
	StrCmp $LANGUAGE ${l_id} detected${l_id} ndetected${l_id}
		detected${l_id}:
			SectionSetInstTypes ${sec} 5
			Goto ${finish}
		ndetected${l_id}:
!macroend

Function .onInit
	;single instance checker
	System::Call 'kernel32::CreateMutexA(i 0, i 0, t "AgenderInstallMutex") i .r1 ?e'
	Pop $R0
	StrCmp $R0 0 +2
		Abort
	;lang
	!insertmacro MUI_LANGDLL_DISPLAY
	!insertmacro SetInstType2Lang ${LANG_SPANISH} ${sec_es} finishlangset
	!insertmacro SetInstType2Lang ${LANG_FRENCH} ${sec_fr} finishlangset
	!insertmacro SetInstType2Lang ${LANG_GERMAN} ${sec_de} finishlangset
	!insertmacro SetInstType2Lang ${LANG_GREEK} ${sec_el} finishlangset
	!insertmacro SetInstType2Lang ${LANG_JAPANESE} ${sec_ja} finishlangset
	!insertmacro SetInstType2Lang ${LANG_PORTUGUESE} ${sec_pt} finishlangset
	!insertmacro SetInstType2Lang ${LANG_ROMANIAN} ${sec_ro} finishlangset
	!insertmacro SetInstType2Lang ${LANG_TRADCHINESE} ${sec_zh_CN} finishlangset
	!insertmacro SetInstType2Lang ${LANG_SIMPCHINESE} ${sec_zh_HK} finishlangset
	!insertmacro SetInstType2Lang ${LANG_SWEDISH} ${sec_sv} finishlangset
	!insertmacro SetInstType2Lang ${LANG_HEBREW} ${sec_he} finishlangset
	finishlangset:
FunctionEnd

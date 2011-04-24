#!/usr/bin/makensis
;Name: Agender.nsi
;Purpose: Agender's win32 installer
;Author: Gabriel Espinoza
;License: GPLv3+


SetCompressor /SOLID lzma
!include "shareddefinitions.nsh"
;MultiUser
!define MULTIUSER_EXECUTIONLEVEL Highest
!define MULTIUSER_MUI
!define MULTIUSER_INSTALLMODE_COMMANDLINE
!define MULTIUSER_INSTALLMODE_INSTDIR ${PRODUCT_NAME}
;headers
!include "MUI2.nsh"
!include "MultiUser.nsh"
!include "FileFunc.nsh"
!include "Memento.nsh"
!include "donationpage.nsh"
!insertmacro GetParent
;change to topdir
!cd "..\.."
;compress with upx
!tempfile PACKHDRTEMP
!packhdr "${PACKHDRTEMP}" '"${UPX}" -9 "${PACKHDRTEMP}"'
!execute '"${UPX}" -9 ${Ag_EXE}'

;constants (don't touch)
!define PRODUCT_EMAIL "agender-support@lists.sourceforge.net"
!define PRODUCT_CFG_REGKEY "Software\Virtuosonic\Agender"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\Agender.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
;Memento
!define MEMENTO_REGISTRY_ROOT "SHCTX"
!define MEMENTO_REGISTRY_KEY "${PRODUCT_CFG_REGKEY}"
;pages
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "gpl-3.0.txt"
!insertmacro MULTIUSER_PAGE_INSTALLMODE
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro VS_PAGE_DONATE
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\Agender.exe"
!define MUI_FINISHPAGE_RUN_PARAMETERS "/nt"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\Readme.txt"
!define MUI_FINISHPAGE_LINK "Visit our website and support the development of Agender"
!define MUI_FINISHPAGE_LINK_LOCATION "${PRODUCT_WEB_SITE}"
!insertmacro MUI_PAGE_FINISH
; Uninstaller pages
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_COMPONENTS
!insertmacro MUI_UNPAGE_INSTFILES
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
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "${PRODUCT_NAME}-${PRODUCT_VERSION}.exe"
InstallDir  ${MULTIUSER_INSTALLMODE_INSTDIR}
ShowInstDetails show
ShowUnInstDetails show
AllowSkipFiles off

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
	;install
	SetOutPath "$INSTDIR"
	SetOverwrite ifdiff
	;executable
	File "${Ag_EXE}"
	;shortcuts
	CreateDirectory "$SMPROGRAMS\Agender"
	CreateShortCut "$SMPROGRAMS\Agender\Agender.lnk" "$INSTDIR\Agender.exe"
	;Icon
	File "share\project-support.jpg"
	File "share\hdr.png"
	;please read it
	File "Readme.txt"
	File "gpl-3.0.txt"
	File "ChangeLog.txt"
	SetAutoClose false
SectionEnd

${MementoSection} "Desktop shortcut" SEC03
	SectionIn 1
	CreateShortCut "$DESKTOP\Agender.lnk" "$INSTDIR\Agender.exe"
${MementoSectionEnd}

${MementoSection} "AutoStart" SEC04
    SectionIn 1 2 3
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "Agender" "$INSTDIR\Agender.exe"
${MementoSectionEnd}

!macro langSection l_iso l_name
	${MementoSection} "${l_name}" sec_${l_iso}
		SectionIn 1
		SetOutPath "$INSTDIR\${l_iso}"
		File /oname=Agender.mo "po\${l_iso}.mo"
	${MementoSectionEnd}
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

${MementoSectionDone}

;hidden Sections
Section -CleanGarbage
	;clean garbage from old versions
	Delete "$INSTDIR\*.mo"
	Delete "$INSTDIR\zh_CN\wxstd.mo"
	Delete "$INSTDIR\zh_HK\wxstd.mo"
	Delete "$INSTDIR\fr\wxstd.mo"
	Delete "$INSTDIR\he\wxstd.mo"
	Delete "$INSTDIR\de\wxstd.mo"
	Delete "$INSTDIR\el\wxstd.mo"
	Delete "$INSTDIR\ja\wxstd.mo"
	Delete "$INSTDIR\ja\wxstd.mo"
	Delete "$INSTDIR\pt\wxstd.mo"
	Delete "$INSTDIR\es\wxstd.mo"
	Delete "$INSTDIR\sv\wxstd.mo"
	Delete "$INSTDIR\mingwm10.dll"
	Delete "$INSTDIR\agender48.png"
	Delete "$INSTDIR\bin\libgcc_s_sjlj-1.dll"
SectionEnd

Section -AdditionalIcons
	;website link
	WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
	CreateShortCut "$SMPROGRAMS\Agender\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
	;donate link
	WriteIniStr "$INSTDIR\donate.url" "InternetShortcut" "URL" ${DONATE_LINK}
	CreateShortCut "$SMPROGRAMS\Agender\Donate.lnk" "$INSTDIR\donate.url"
	;etc
	CreateShortCut "$SMPROGRAMS\Agender\Uninstall.lnk" "$INSTDIR\uninst.exe"
	CreateShortCut "$SMPROGRAMS\Agender\License.lnk" "$INSTDIR\gpl-3.0.txt"
	CreateShortCut "$SMPROGRAMS\Agender\Readme.lnk" "$INSTDIR\Readme.txt"
	CreateShortCut "$SMPROGRAMS\Agender\ChangeLog.lnk" "$INSTDIR\ChangeLog.txt"
	;se7en
	Push $R0
	ReadRegStr $R0 HKLM "SOFTWARE\Microsoft\Windows NT\CurrentVersion" CurrentVersion
	StrCmp $R0 "6.1" 0 +2
		CreateShortCut "$QUICKLAUNCH\Agender.lnk" "$INSTDIR\Agender.exe"
	Pop $R0
SectionEnd

Section -Post
	WriteUninstaller "$INSTDIR\uninst.exe"
	WriteRegStr "SHCTX" "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\Agender.exe"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "InstallLocation" "$INSTDIR\Agender.exe"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "InstallSource" "$EXEPATH"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "Comments" "Agender rocks!"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "QuietUninstallString" "$INSTDIR\uninst.exe /S"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\Agender.exe"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "Contact" "${PRODUCT_EMAIL}"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "Readme" "$INSTDIR\Readme.txt"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "URLUpdateInfo" "${PRODUCT_WEB_SITE}/?page=Downloads"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "HelpLink" "${PRODUCT_WEB_SITE}/?page=Help"
SectionEnd

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
	;mandatory
	!insertmacro MULTIUSER_INIT
	${MementoSectionRestore}
	;InstallDir
	Push $0
	ReadRegStr $0 "SHCTX" "${PRODUCT_DIR_REGKEY}" ""
	StrCmp $0 "" +3 0
		${GetParent} $0 $0
		StrCpy $INSTDIR $0
	Pop $0
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

Function un.onInit
	!insertmacro MULTIUSER_UNINIT
	;check for connection
	Dialer::GetConnectedState
	Pop $R0
	StrCmp $R0 "offline" nowebsite ;if offline jump out
    ;if silent do nothing, else open website
	IfSilent nowebsite
		ExecShell "open" "http://sourceforge.net/tracker/?group_id=271084"
	nowebsite:
FunctionEnd


Function .onInstSuccess
	;check for connection
	Dialer::GetConnectedState
	Pop $R0
	StrCmp $R0 "offline" nowebsite ;if offline jump out
    ;if silent do nothing, else open website
	IfSilent nowebsite
		ExecShell "open" ${PRODUCT_WEB_SITE}
	nowebsite:
	${MementoSectionSave}
FunctionEnd

;Assign language strings to sections
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SEC01} "Agender (required)."
    !insertmacro MUI_DESCRIPTION_TEXT ${SEC02} "Translation files; only the ones you install now will be available."
    !insertmacro MUI_DESCRIPTION_TEXT ${SEC03} "Create a Desktop shortcut."
    !insertmacro MUI_DESCRIPTION_TEXT ${SEC04} "Run on login."
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;Uninstaller a.k.a. ...
;I HATE UR SOFTWARE!!!

Section Uninstall unSEC01
	RMDir /r "$INSTDIR"
	Delete "$DESKTOP\Agender.lnk"
	RMDir /r "$SMPROGRAMS\Agender"
	;remove registry entries
	DeleteRegKey "SHCTX"  "${PRODUCT_UNINST_KEY}"
	DeleteRegKey "SHCTX" "${PRODUCT_DIR_REGKEY}"
	DeleteRegKey HKLM "${PRODUCT_CFG_REGKEY}"
	SetAutoClose false
SectionEnd

Section /o "un.User Data" unSEC02
	DeleteRegKey HKCU "${PRODUCT_CFG_REGKEY}"
	SetShellVarContext current
	RMDir /r "$APPDATA\Agender"
SectionEnd

;Assign language strings to sections
!insertmacro MUI_UNFUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${unSEC01} "Uninstall this crapware :P"
    !insertmacro MUI_DESCRIPTION_TEXT ${unSEC02} "Delete your notes and configuration"
!insertmacro MUI_UNFUNCTION_DESCRIPTION_END

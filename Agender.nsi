#!/usr/bin/makensis
;Name: Agender.nsi
;Purpose: Agender's win32 installer
;Author: Gabriel Espinoza
;License: GPLv3+

;compress with upx, reduces size by around 200 kb!
!tempfile PACKHDRTEMP
!define UPX "C:\Archivos de programa\upx307w\upx.exe"
!packhdr "${PACKHDRTEMP}" '${UPX} -9 "${PACKHDRTEMP}"'
!execute '${UPX} -9 src\bin\vc6\Agender.exe'

;this defines are configurable, change them when needed
!define WX_VERSION 2.8.11
!define WX_DIR "..\wxWidgets-${WX_VERSION}"
!define PRODUCT_VERSION "2.0"
;constants (don't touch)
!define PRODUCT_NAME "Agender"
!define PRODUCT_PUBLISHER "Virtuosonic"
!define PRODUCT_WEB_SITE "http://agender.sourceforge.net"
!define PRODUCT_EMAIL "agender-support@lists.sourceforge.net"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\Agender.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"

SetCompressor /SOLID lzma
;MultiUser
!define MULTIUSER_EXECUTIONLEVEL Highest
!define MULTIUSER_MUI
!define MULTIUSER_INSTALLMODE_COMMANDLINE
!define MULTIUSER_INSTALLMODE_INSTDIR ${PRODUCT_NAME}
!include "MUI2.nsh"
!include "MultiUser.nsh"
!include "FileFunc.nsh"
!insertmacro GetParent
; MUI Settings
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"
;pages
!define MUI_WELCOMEPAGE_TEXT "This wizard will install Agender ${PRODUCT_VERSION}, if you're updating, before continuing close Agender."
!insertmacro MUI_PAGE_WELCOME
!insertmacro MUI_PAGE_LICENSE "gpl-3.0.txt"
!insertmacro MULTIUSER_PAGE_INSTALLMODE
!insertmacro MUI_PAGE_DIRECTORY
!insertmacro MUI_PAGE_COMPONENTS
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\Agender.exe"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\Readme.txt"
!define MUI_FINISHPAGE_LINK "Visit our website and support the development of Agender"
!define MUI_FINISHPAGE_LINK_LOCATION "${PRODUCT_WEB_SITE}"
!insertmacro MUI_PAGE_FINISH
; Uninstaller pages
!insertmacro MUI_UNPAGE_WELCOME
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

InstType "Full"
InstType "Minimal"
InstType "Minimal+Detected language translation"
;version information
VIProductVersion "1.0.0.0"
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductName" ${PRODUCT_NAME}
VIAddVersionKey /LANG=${LANG_ENGLISH} "Comments" "A cross-platform schedule tool"
VIAddVersionKey /LANG=${LANG_ENGLISH} "CompanyName" ${PRODUCT_PUBLISHER}
VIAddVersionKey /LANG=${LANG_ENGLISH} "LegalCopyright" "Copyright © 2009-2011 Gabriel Espinoza"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileDescription" "The Agender installer"
VIAddVersionKey /LANG=${LANG_ENGLISH} "FileVersion" ${PRODUCT_VERSION}
VIAddVersionKey /LANG=${LANG_ENGLISH} "ProductVersion" ${PRODUCT_VERSION}

Section "Agender" SEC01
	SectionIn RO
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
	;install
	SetOutPath "$INSTDIR"
	SetOverwrite ifdiff
	;executable
	File "src\bin\vc6\Agender.exe"
	;c runtime
	;File "C:\Archivos de programa\Microsoft Visual Studio 9.0\VC\redist\x86\Microsoft.VC90.CRT\msvcr90.dll"
	;shortcuts
	CreateDirectory "$SMPROGRAMS\Agender"
	CreateShortCut "$SMPROGRAMS\Agender\Agender.lnk" "$INSTDIR\Agender.exe"
	;Icon
	File "share\project-support.jpg"
	File "share\hdr.png"
	;please read it
	File "Readme.txt"
	File "gpl-3.0.txt"
	SetAutoClose false
SectionEnd

Section "Desktop shortcut" SEC03
	SectionIn 1
	CreateShortCut "$DESKTOP\Agender.lnk" "$INSTDIR\Agender.exe"
SectionEnd

Section "AutoStart" SEC04
    SectionIn 1 2 3
    WriteRegStr HKCU "Software\Microsoft\Windows\CurrentVersion\Run" "Agender" "$INSTDIR\Agender.exe"
SectionEnd

!macro langSection l_iso l_name
	Section "${l_name}" sec_${l_iso}
		SectionIn 1
		SetOutPath "$INSTDIR\${l_iso}"
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

Section -AdditionalIcons
	WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
	CreateShortCut "$SMPROGRAMS\Agender\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
	CreateShortCut "$SMPROGRAMS\Agender\Uninstall.lnk" "$INSTDIR\uninst.exe"
	CreateShortCut "$SMPROGRAMS\Agender\License.lnk" "$INSTDIR\gpl-3.0.txt"
	CreateShortCut "$SMPROGRAMS\Agender\Readme.lnk" "$INSTDIR\Readme.txt"
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
	IntCmp $LANGUAGE ${l_id} detected${l_id} ndetected${l_id}
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
	;InstallDir
	Push $0
	ReadRegStr $0 "SHCTX" "${PRODUCT_DIR_REGKEY}" ""
	StrCmp $0 "" +3 0
		${GetParent} $0 $0
		StrCpy $INSTDIR $0
	Pop $0
	;lang
	!insertmacro MUI_LANGDLL_DISPLAY
	!insertmacro SetInstType2Lang 1034 ${sec_es} finishlangset
	!insertmacro SetInstType2Lang 1036 ${sec_fr} finishlangset
	!insertmacro SetInstType2Lang 1031 ${sec_de} finishlangset
	!insertmacro SetInstType2Lang 1032 ${sec_el} finishlangset
	!insertmacro SetInstType2Lang 1041 ${sec_ja} finishlangset
	!insertmacro SetInstType2Lang 2070 ${sec_pt} finishlangset
	!insertmacro SetInstType2Lang 1048 ${sec_ro} finishlangset
	!insertmacro SetInstType2Lang 2052 ${sec_zh_CN} finishlangset
	!insertmacro SetInstType2Lang 1023 ${sec_zh_HK} finishlangset
	!insertmacro SetInstType2Lang 1053 ${sec_sv} finishlangset
	!insertmacro SetInstType2Lang 1037 ${sec_he} finishlangset
	finishlangset:
FunctionEnd

Function un.onInit
	!insertmacro MULTIUSER_UNINIT
FunctionEnd


Function .onInstSuccess
	IfSilent +2 0
		ExecShell "open" ${PRODUCT_WEB_SITE}
FunctionEnd

;Language strings
LangString DESC_Required ${LANG_ENGLISH} "Agender (required)."
LangString DESC_Po ${LANG_ENGLISH} "Translation files, only the ones you install now will be available."
LangString DESC_DShortCut ${LANG_ENGLISH} "Create a Desktop shortcut."
LangString DESC_startup ${LANG_ENGLISH} "Run on login."
;spanish
LangString DESC_Required ${LANG_SPANISH} "Agender (requerido)."
LangString DESC_Po ${LANG_SPANISH} "Traducciones, solo las que instales ahora estaran disponibles."
LangString DESC_DShortCut ${LANG_SPANISH} "Crear acceso directo en el Escritorio."
LangString DESC_startup ${LANG_SPANISH} "Ejecutar al inicio de sesion."

;Assign language strings to sections
!insertmacro MUI_FUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${SEC01} $(DESC_Required)
    !insertmacro MUI_DESCRIPTION_TEXT ${SEC02} $(DESC_Po)
    !insertmacro MUI_DESCRIPTION_TEXT ${SECO3} $(DESC_DShortCut)
    !insertmacro MUI_DESCRIPTION_TEXT ${SEC04} $(DESC_startup)
!insertmacro MUI_FUNCTION_DESCRIPTION_END

;Uninstaller a.k.a. ...
;I HATE UR SOFTWARE!!!

!macro DeleteLang l_id
	Delete "$INSTDIR\${l_id}\Agender.mo"
	RMDir "$INSTDIR\${l_id}"
!macroend

Section Uninstall
	Delete "$INSTDIR\${PRODUCT_NAME}.url"
	Delete "$INSTDIR\uninst.exe"
	;c runtime
	Delete "$INSTDIR\Agender.exe"
	Delete "$INSTDIR\Readme.txt"
	Delete "$INSTDIR\gpl-3.0.txt"
	Delete "$INSTDIR\project-support.jpg"
	Delete "$INSTDIR\hdr.jpg"
	;remove shortcuts
	Delete "$SMPROGRAMS\Agender\Uninstall.lnk"
	Delete "$SMPROGRAMS\Agender\Website.lnk"
	Delete "$DESKTOP\Agender.lnk"
	Delete "$SMPROGRAMS\Agender\Agender.lnk"
	Delete "$SMPROGRAMS\Agender\License.lnk"
	Delete "$SMPROGRAMS\Agender\Readme.lnk"
	;remove translations
	!insertmacro DeleteLang es
	!insertmacro DeleteLang de
	!insertmacro DeleteLang ja
	!insertmacro DeleteLang pt
	!insertmacro DeleteLang fr
	!insertmacro DeleteLang el
	!insertmacro DeleteLang sv
	!insertmacro DeleteLang zh_HK
	!insertmacro DeleteLang zh_CN
	!insertmacro DeleteLang ro
	!insertmacro DeleteLang he
	;remove our dir
	RMDir "$SMPROGRAMS\Agender"
	RMDir "$INSTDIR"
	;remove registry entries
	DeleteRegKey "SHCTX"  "${PRODUCT_UNINST_KEY}"
	DeleteRegKey "SHCTX" "${PRODUCT_DIR_REGKEY}"
	SetAutoClose false
SectionEnd


;Language strings
LangString DESC_Uninstall ${LANG_ENGLISH} "Uninstall this crapware :P"

;Assign language strings to sections
!insertmacro MUI_UNFUNCTION_DESCRIPTION_BEGIN
    !insertmacro MUI_DESCRIPTION_TEXT ${Uninstall} $(DESC_Uninstall)
!insertmacro MUI_UNFUNCTION_DESCRIPTION_END

#!/usr/bin/makensis
;Name: Agender.nsi
;Purpose: Agender's win32 installer
;Author: Gabriel Espinoza
;License: GPLv3+

;this file needs some hacking, if you are using m$w  please help
;TODO: add support for multiple users
;TODO: add support for shared version of wxWidgets

;this defines are configurable, change them when needed
!define WX_LIBS 0
!define WX_UNICODE 1
!define WX_MONOLITHIC 1
!define WX_VERSION 2.8.11
!define WX_DIR "/home/virtuoso/C++/wxWidgets-${WX_VERSION}"
;NSIS
!define VS_SYSTEMDLL 1
;Mingw
!define MINGW_RUNTIME 1
!define SJLJ_EXCEPTIONS 0
!define MINGW_DIR "/home/virtuoso/mingw32"
;!define MINGW_DIR "/usr/i686-pc-mingw32/sys-root/mingw"
;!define MINGW_DIR "C:\Archivos de Programa\codeblocks\MINGW"
;!define MINGW_DIR "C:\MINGW"
!define PRODUCT_VERSION "1.1.8"
;constants
!define PRODUCT_NAME "Agender"
!define PRODUCT_PUBLISHER "Virtuosonic"
!define PRODUCT_WEB_SITE "http://agender.sourceforge.net"
!define PRODUCT_DIR_REGKEY "Software\Microsoft\Windows\CurrentVersion\App Paths\Agender.exe"
!define PRODUCT_UNINST_KEY "Software\Microsoft\Windows\CurrentVersion\Uninstall\${PRODUCT_NAME}"
!define PRODUCT_UNINST_ROOT_KEY "HKLM"

SetCompressor lzma

!include "MUI.nsh"

; MUI Settings
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"
; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "gpl-3.0.txt"
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
;Components page
!insertmacro MUI_PAGE_COMPONENTS
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\Agender.exe"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\Readme.txt"
!insertmacro MUI_PAGE_FINISH
; Uninstaller pages
!insertmacro MUI_UNPAGE_WELCOME
!insertmacro MUI_UNPAGE_INSTFILES
; Language files
!insertmacro MUI_LANGUAGE "Spanish"
!insertmacro MUI_LANGUAGE "English"
!insertmacro MUI_LANGUAGE "German"
!insertmacro MUI_LANGUAGE "Japanese"
!insertmacro MUI_LANGUAGE "Swedish"
!insertmacro MUI_LANGUAGE "Greek"
!insertmacro MUI_LANGUAGE "French"
!insertmacro MUI_LANGUAGE "Portuguese"
!insertmacro MUI_LANGUAGE "TradChinese"
!insertmacro MUI_LANGUAGE "SimpChinese"
!insertmacro MUI_LANGUAGE "Romanian"
; ReserveFiles
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; MUI end ------
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "${PRODUCT_NAME}-${PRODUCT_VERSION}.exe"
InstallDir "$PROGRAMFILES\${PRODUCT_NAME}"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show

InstType "Full"
InstType "Minimal"
InstType "Minimal+Detected language translation"

Section "Agender" SEC01
	SectionIn 1 2 3 RO
	SetOutPath "$INSTDIR"
	SetOverwrite ifdiff
	;executable
	File "Agender.exe"
	;shortcuts
	CreateDirectory "$SMPROGRAMS\Agender"
	CreateShortCut "$SMPROGRAMS\Agender\Agender.lnk" "$INSTDIR\Agender.exe"
	CreateShortCut "$DESKTOP\Agender.lnk" "$INSTDIR\Agender.exe"
	;compiler runtime
	!if ${MINGW_RUNTIME}
		File "${MINGW_DIR}\bin\mingwm10.dll"
	!endif
	!if ${SJLJ_EXCEPTIONS}
		File "${MINGW_DIR}\bin\libgcc_s_sjlj-1.dll"
	!endif
	;please read it
	File "Readme.txt"
	File "gpl-3.0.txt"
	SetAutoClose false
SectionEnd

SectionGroup "Translations" SEC02
	;translations
	Section "Chinese (Simplified)" sec_zh_CN
		SectionIn 1
		SetOutPath "$INSTDIR\zh_CN"
		File /oname=Agender.mo "po\zh_CN.mo"
		File /oname=wxstd.mo "${WX_DIR}\locale\zh_CN.mo"
	SectionEnd
	Section "Chinese (Traditional)" sec_zh_HK
		SectionIn 1
		SetOutPath "$INSTDIR\zh_HK"
		File /oname=Agender.mo "po\zh_HK.mo"
		File /oname=wxstd.mo "${WX_DIR}\locale\zh_TW.mo"
	SectionEnd
	Section "French" sec_fr
		SectionIn 1
		SetOutPath "$INSTDIR\fr"
		File /oname=Agender.mo "po\fr.mo"
		File /oname=wxstd.mo "${WX_DIR}\locale\fr.mo"
	SectionEnd
	Section "German" sec_de
		SectionIn 1
		SetOutPath "$INSTDIR\de"
		File /oname=Agender.mo "po\de.mo"
		File /oname=wxstd.mo "${WX_DIR}\locale\de.mo"
	SectionEnd
	Section "Greek" sec_el
		SectionIn 1
		SetOutPath "$INSTDIR\el"
		File /oname=Agender.mo "po\el.mo"
		File /oname=wxstd.mo "${WX_DIR}\locale\el.mo"
	SectionEnd
	Section "Japanese" sec_ja
		SectionIn 1
		SetOutPath "$INSTDIR\ja"
		File /oname=Agender.mo "po\ja.mo"
		File /oname=wxstd.mo "${WX_DIR}\locale\ja.mo"
	SectionEnd
	Section "Portuguese" sec_pt
		SectionIn 1
		SetOutPath "$INSTDIR\pt"
		File /oname=Agender.mo "po\pt.mo"
		File /oname=wxstd.mo "${WX_DIR}\locale\pt.mo"
	SectionEnd
	Section "Romanian" sec_ro
		SectionIn 1
		SetOutPath "$INSTDIR\ro"
		File /oname=Agender.mo "po\ro.mo"
		;File /oname=wxstd.mo "${WX_DIR}\locale\ro.mo"
	SectionEnd
	Section "Spanish" sec_es
		SectionIn 1
		SetOutPath "$INSTDIR\es"
		File /oname=Agender.mo "po\es.mo"
		File /oname=wxstd.mo "${WX_DIR}\locale\es.mo"
	SectionEnd
	Section "Swedish" sec_sv
		SectionIn 1
		SetOutPath "$INSTDIR\sv"
		File /oname=Agender.mo "po\sv.mo"
		File /oname=wxstd.mo "${WX_DIR}\locale\sv.mo"
	SectionEnd
SectionGroupEnd

Section -AdditionalIcons
	WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
	CreateShortCut "$SMPROGRAMS\Agender\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
	CreateShortCut "$SMPROGRAMS\Agender\Uninstall.lnk" "$INSTDIR\uninst.exe"
	CreateShortCut "$SMPROGRAMS\Agender\License.lnk" "$INSTDIR\gpl-3.0.txt"
	CreateShortCut "$SMPROGRAMS\Agender\Readme.lnk" "$INSTDIR\Readme.txt"
SectionEnd

Section -Post
	WriteUninstaller "$INSTDIR\uninst.exe"
	WriteRegStr HKLM "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\Agender.exe"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\Agender.exe"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
	WriteRegStr ${PRODUCT_UNINST_ROOT_KEY} "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
SectionEnd

!macro SetInstType2Lang l_id sec finish
	IntCmp $LANGUAGE ${l_id} ${l_id}detected ${l_id}ndetected
		${l_id}detected:
			SectionSetInstTypes ${sec} 5
			Goto ${finish}
		${l_id}ndetected:
!macroend

Function .onInit
	;single instance checker
	!if ${VS_SYSTEMDLL}
		System::Call 'kernel32::CreateMutexA(i 0, i 0, t "AgenderInstallMutex") i .r1 ?e'
		Pop $R0
		StrCmp $R0 0 +2
			Abort
	!endif
	;lang
	!insertmacro MUI_LANGDLL_DISPLAY
	;Spanish
	IntCmp $LANGUAGE 1034 esch nesch
		esch:
			SectionSetInstTypes ${sec_es} 5
			Goto finishlangset
		nesch:
	;English
	IntCmp $LANGUAGE 1033 ench nench
		ench:
			SectionSetInstTypes ${sec_es} 5
			Goto finishlangset
		nench:
	;French
	IntCmp $LANGUAGE 1036 frch nfrch
		frch:
			SectionSetInstTypes ${sec_fr} 5
			Goto finishlangset
		nfrch:
	;German
	IntCmp $LANGUAGE 1031 dech ndech
		dech:
			SectionSetInstTypes ${sec_de} 5
			Goto finishlangset
		ndech:
	;Greek
	IntCmp $LANGUAGE 1032 elch nelch
		elch:
			SectionSetInstTypes ${sec_el} 5
			Goto finishlangset
		nelch:
	;Japanese
	IntCmp $LANGUAGE 1041 jach njach
		jach:
			SectionSetInstTypes ${sec_ja} 5
			Goto finishlangset
		njach:
	;Portuguese
	IntCmp $LANGUAGE 2070 ptch nptch
		ptch:
			SectionSetInstTypes ${sec_pt} 5
			Goto finishlangset
		nptch:
	;Romanian
	IntCmp $LANGUAGE 1048 roch nroch
		roch:
			SectionSetInstTypes ${sec_ro} 5
			Goto finishlangset
		nroch:
	;SimpChinese
	IntCmp $LANGUAGE 2052 zh_CNch nzh_CNch
		zh_CNch:
			SectionSetInstTypes ${sec_zh_CN} 5
			Goto finishlangset
		nzh_CNch:
	;TradChinese
	IntCmp $LANGUAGE 1023 zh_HKch nzh_HKch
		zh_HKch:
			SectionSetInstTypes ${sec_zh_HK} 5
			Goto finishlangset
		nzh_HKch:
	;Swedish
	IntCmp $LANGUAGE 1053 svch nsvch
		svch:
			SectionSetInstTypes ${sec_sv} 5
			Goto finishlangset
		nsvch:
	finishlangset:
FunctionEnd

Section Uninstall
	Delete "$INSTDIR\${PRODUCT_NAME}.url"
	Delete "$INSTDIR\uninst.exe"
	;runtime
	!if ${MINGW_RUNTIME}
		Delete "$INSTDIR\mingwm10.dll"
	!endif
	!if ${SJLJ_EXCEPTIONS}
		Delete "$INSTDIR\bin\libgcc_s_sjlj-1.dll"
	!endif
	Delete "$INSTDIR\Agender.exe"
	Delete "$INSTDIR\Readme.txt"
	Delete "$INSTDIR\gpl-3.0.txt"
	;remove shortcuts
	Delete "$SMPROGRAMS\Agender\Uninstall.lnk"
	Delete "$SMPROGRAMS\Agender\Website.lnk"
	Delete "$DESKTOP\Agender.lnk"
	Delete "$SMPROGRAMS\Agender\Agender.lnk"
	Delete "$SMPROGRAMS\Agender\License.lnk"
	Delete "$SMPROGRAMS\Agender\Readme.lnk"
	;remove translations
	;spanish
	Delete "$INSTDIR\es\Agender.mo"
	Delete "$INSTDIR\es\wxstd.mo"
	RMDir "$INSTDIR\es"
	;german
	Delete "$INSTDIR\de\Agender.mo"
	Delete "$INSTDIR\de\wxstd.mo"
	RMDir "$INSTDIR\de"
	;japanese
	Delete "$INSTDIR\ja\Agender.mo"
	Delete "$INSTDIR\ja\wxstd.mo"
	RMDir "$INSTDIR\ja"
	;portuguese
	Delete "$INSTDIR\pt\Agender.mo"
	Delete "$INSTDIR\pt\wxstd.mo"
	RMDir "$INSTDIR\pt"
	;french
	Delete "$INSTDIR\fr\Agender.mo"
	Delete "$INSTDIR\fr\wxstd.mo"
	RMDir "$INSTDIR\fr"
	;greek
	Delete "$INSTDIR\el\Agender.mo"
	Delete "$INSTDIR\el\wxstd.mo"
	RMDir "$INSTDIR\el"
	;swedish
	Delete "$INSTDIR\sv\Agender.mo"
	Delete "$INSTDIR\sv\wxstd.mo"
	RMDir "$INSTDIR\sv"
	;chinese traditional/hongkong
	Delete "$INSTDIR\zh_HK\Agender.mo"
	Delete "$INSTDIR\zh_HK\wxstd.mo"
	RMDir "$INSTDIR\zh_HK"
	;chinese simplified
	Delete "$INSTDIR\zh_CN\Agender.mo"
	Delete "$INSTDIR\zh_CN\wxstd.mo"
	RMDir "$INSTDIR\zh_CN"
	;remove our dir
	RMDir "$SMPROGRAMS\Agender"
	RMDir "$INSTDIR"
	;remove registry entries
	DeleteRegKey "${PRODUCT_UNINST_ROOT_KEY}"  "${PRODUCT_UNINST_KEY}"
	DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
	SetAutoClose false
SectionEnd

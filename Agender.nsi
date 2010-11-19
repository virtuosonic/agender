#!/usr/bin/makensis
;Name: Agender.nsi
;Purpose: Agender's win32 installer
;Author: Gabriel Espinoza
;License: GPLv3+

;compress with upx, reduces size by around 200 kb!
!tempfile PACKHDRTEMP
!define UPX "/usr/bin/upx"
;!define UPX "C:\Program Files\UPX\upx.exe"
!packhdr "${PACKHDRTEMP}" '${UPX} -9 "${PACKHDRTEMP}"'

;this defines are configurable, change them when needed
!define WX_LIBS 0
!define WX_UNICODE 1
!define WX_MONOLITHIC 1
!define WX_VERSION 2.8.11
!define WX_DIR "/home/virtuoso/C++/wxWidgets-${WX_VERSION}"
;NSIS
;do we have the system.dll plugin
!define VS_SYSTEMDLL 1
;Mingw
!define MINGW_RUNTIME 1
!define SJLJ_EXCEPTIONS 1
!define MINGW_DIR "/usr/i686-pc-mingw32/sys-root/mingw"
;!define MINGW_DIR "/home/virtuoso/mingw32"
;!define MINGW_DIR "C:\Archivos de Programa\codeblocks\MINGW"
;!define MINGW_DIR "C:\MINGW"
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
; MUI Settings
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\modern-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\modern-uninstall.ico"
; Welcome page
!insertmacro MUI_PAGE_WELCOME
; License page
!insertmacro MUI_PAGE_LICENSE "gpl-3.0.txt"
;MultiUserPage
!insertmacro MULTIUSER_PAGE_INSTALLMODE
; Directory page
!insertmacro MUI_PAGE_DIRECTORY
;Components page
!insertmacro MUI_PAGE_COMPONENTS
; Instfiles page
!insertmacro MUI_PAGE_INSTFILES
; Finish page
!define MUI_FINISHPAGE_RUN "$INSTDIR\Agender.exe"
!define MUI_FINISHPAGE_SHOWREADME "$INSTDIR\Readme.txt"
!define MUI_FINISHPAGE_LINK "${PRODUCT_NAME} Website"
!define MUI_FINISHPAGE_LINK_LOCATION "${PRODUCT_WEB_SITE}"
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

Section "Agender" SEC01
	SectionIn RO
	SetOutPath "$INSTDIR"
	SetOverwrite ifdiff
	;executable
	File "Agender.exe"
	;shortcuts
	CreateDirectory "$SMPROGRAMS\Agender"
	CreateShortCut "$SMPROGRAMS\Agender\Agender.lnk" "$INSTDIR\Agender.exe"
	;compiler runtime
	!if ${MINGW_RUNTIME}
		File "${MINGW_DIR}\bin\mingwm10.dll"
	!endif
	!if ${SJLJ_EXCEPTIONS}
		File "${MINGW_DIR}\bin\libgcc_s_sjlj-1.dll"
	!endif
	;Icon
	File "share\agender48.png"
	;please read it
	File "Readme.txt"
	File "gpl-3.0.txt"
	SetAutoClose false
SectionEnd

Section "Desktop shortcut" SEC03
	SectionIn 1
	CreateShortCut "$DESKTOP\Agender.lnk" "$INSTDIR\Agender.exe"
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
	Section "Hebrew" sec_he
		SectionIn 1
		SetOutPath "$INSTDIR\he"
		File /oname=Agender.mo "po\he.mo"
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
	WriteRegStr "SHCTX" "${PRODUCT_DIR_REGKEY}" "" "$INSTDIR\Agender.exe"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "DisplayName" "$(^Name)"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "UninstallString" "$INSTDIR\uninst.exe"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "DisplayIcon" "$INSTDIR\Agender.exe"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "DisplayVersion" "${PRODUCT_VERSION}"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "URLInfoAbout" "${PRODUCT_WEB_SITE}"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "Publisher" "${PRODUCT_PUBLISHER}"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "Contact" "${PRODUCT_EMAIL}"
	WriteRegStr "SHCTX" "${PRODUCT_UNINST_KEY}" "Readme" "$INSTDIR\Readme.txt"
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
	!if ${VS_SYSTEMDLL}
		System::Call 'kernel32::CreateMutexA(i 0, i 0, t "AgenderInstallMutex") i .r1 ?e'
		Pop $R0
		StrCmp $R0 0 +2
			Abort
	!endif
	!insertmacro MULTIUSER_INIT
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

Section Uninstall
	Delete "$INSTDIR\${PRODUCT_NAME}.url"
	Delete "$INSTDIR\uninst.exe"
	;runtime
	!if ${MINGW_RUNTIME}
		Delete "$INSTDIR\mingwm10.dll"
	!endif
	!if ${SJLJ_EXCEPTIONS}
		Delete "$INSTDIR\libgcc_s_sjlj-1.dll"
	!endif
	Delete "$INSTDIR\Agender.exe"
	Delete "$INSTDIR\Readme.txt"
	Delete "$INSTDIR\gpl-3.0.txt"
	Delete "$INSTDIR\agender48.png"
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
	;romanian
	Delete "$INSTDIR\ro\Agender.mo"
	RMDir "$INSTDIR\ro"
	;hebrew
	Delete "$INSTDIR\he\Agender.mo"
	RMDir "$INSTDIR\he"
	;remove our dir
	RMDir "$SMPROGRAMS\Agender"
	RMDir "$INSTDIR"
	;remove registry entries
	DeleteRegKey "SHCTX"  "${PRODUCT_UNINST_KEY}"
	DeleteRegKey "SHCTX" "${PRODUCT_DIR_REGKEY}"
	SetAutoClose false
SectionEnd

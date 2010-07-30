;Name: Agender.nsi
;Purpose: Agender's win32 installer
;Author: Gabriel Espinoza
;License: GPLv3+

;this file needs some hacking, if you are using m$w  please help

;this defines are configurable, change them when needed
!define MINGW_RUNTIME 1
!define MINGW_DIR "/usr/i686-pc-mingw32/sys-root/mingw"
;!define MINGW_DIR "C:\Archivos de Programa\codeblocks\MINGW"
;!define MINGW_DIR "C:\MINGW"
!define PRODUCT_VERSION "1.1.6"
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
; ReserveFiles
!insertmacro MUI_RESERVEFILE_INSTALLOPTIONS
; MUI end ------
Name "${PRODUCT_NAME} ${PRODUCT_VERSION}"
OutFile "${PRODUCT_NAME}-${PRODUCT_VERSION}.exe"
InstallDir "$PROGRAMFILES\${PRODUCT_NAME}"
InstallDirRegKey HKLM "${PRODUCT_DIR_REGKEY}" ""
ShowInstDetails show
ShowUnInstDetails show
;lang
Function .onInit
	!insertmacro MUI_LANGDLL_DISPLAY
FunctionEnd

Section "Agender" SEC01
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
		File "${MINGW_DIR}\bin\libgcc_s_sjlj-1.dll"
	!endif
	;please read it
	File "Readme.txt"
	File "gpl-3.0.txt"
	;translations
	SetOutPath "$INSTDIR\"
	File "po\es.mo"
	File "po\de.mo"
	File "po\ja.mo"
	File "po\pt.mo"
	File "po\fr.mo"
	File "po\el.mo"
	File "po\sv.mo"
	File "po\zh.mo"
	SetAutoClose false
SectionEnd

Section -AdditionalIcons
	WriteIniStr "$INSTDIR\${PRODUCT_NAME}.url" "InternetShortcut" "URL" "${PRODUCT_WEB_SITE}"
	CreateShortCut "$SMPROGRAMS\Agender\Website.lnk" "$INSTDIR\${PRODUCT_NAME}.url"
	CreateShortCut "$SMPROGRAMS\Agender\Uninstall.lnk" "$INSTDIR\uninst.exe"
	CreateShortCut "$SMPROGRAMS\Agender\License.lnk" "$INSTDIR\gpl-3.0.txt"
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

Section Uninstall
	Delete "$INSTDIR\${PRODUCT_NAME}.url"
	Delete "$INSTDIR\uninst.exe"
	!if ${MINGW_RUNTIME}
		Delete "$INSTDIR\mingwm10.dll"
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
	;remove translations
	Delete "$INSTDIR\es.mo"
	Delete "$INSTDIR\de.mo"
	Delete "$INSTDIR\ja.mo"
	Delete "$INSTDIR\pt.mo"
	Delete "$INSTDIR\fr.mo"
	Delete "$INSTDIR\el.mo"
	Delete "$INSTDIR\sv.mo"
	Delete "$INSTDIR\zh.mo"
	;remove our dir
	RMDir "$SMPROGRAMS\Agender"
	RMDir "$INSTDIR"
	;remove registry entries
	DeleteRegKey "${PRODUCT_UNINST_ROOT_KEY}"  "${PRODUCT_UNINST_KEY}"
	DeleteRegKey HKLM "${PRODUCT_DIR_REGKEY}"
	SetAutoClose false
SectionEnd

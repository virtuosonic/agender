#!/usr/bin/makensis
;Name: shareddefinitions.nsi
;Purpose: shared constants between Agender's scripts
;Author: Gabriel Espinoza
;License: GPLv3+
;Created: 09-mar-2011
;this defines are configurable, change them when needed
!define WX_VERSION 2.8.11
!define WX_DIR "..\wxWidgets-${WX_VERSION}"
!define PRODUCT_VERSION "1.2"
!define UPX "C:\Archivos de programa\upx307w\upx.exe"
!define Ag_EXE "src\bin\Release\Agender.exe"
!define C_RUNTIME "C:\Archivos de programa\Microsoft Visual Studio 9.0\VC\redist\x86\Microsoft.VC90.CRT\msvcr90.dll"
;!define Ag_EXE "src\bin\mingw32\Agender.exe"
;constants (don't touch)
!define PRODUCT_NAME "Agender"
!define PRODUCT_PUBLISHER "Virtuosonic"
!define PRODUCT_WEB_SITE "http://agender.sourceforge.net"
!define DONATE_LINK "http://sourceforge.net/donate/index.php?group_id=271084"
; MUI Settings
!define MUI_ICON "${NSISDIR}\Contrib\Graphics\Icons\orange-install.ico"
!define MUI_UNICON "${NSISDIR}\Contrib\Graphics\Icons\orange-uninstall.ico"
!define MUI_HEADERIMAGE
!define MUI_HEADERIMAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Header\orange.bmp"
!define MUI_HEADERIMAGE_UNBITMAP "${NSISDIR}\Contrib\Graphics\Header\orange-uninstall.bmp"
!define MUI_WELCOMEFINISHPAGE_BITMAP "${NSISDIR}\Contrib\Graphics\Wizard\orange.bmp"
!define MUI_UNWELCOMEFINISHPAGE_BITMAP  "${NSISDIR}\Contrib\Graphics\Wizard\orange-uninstall.bmp"


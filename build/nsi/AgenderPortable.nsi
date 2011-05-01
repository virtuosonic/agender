#!/usr/bin/makensis
;Name: AgenderPortable.nsi
;Purpose: Agender Portable Launcher
;Author: Gabriel Espinoza
;License: GPLv3+
;Created: 09-mar-2011

!include "shareddefinitions.nsh"
!cd "..\.."
!tempfile PACKHDRTEMP
!packhdr "${PACKHDRTEMP}" '"${UPX}" -9 "${PACKHDRTEMP}"'

SetCompressor /SOLID lzma
OutFile "${PRODUCT_NAME} Portable.exe"
SilentInstall Silent
AutoCloseWindow True
RequestExecutionLevel user
Icon "src\Agender.ico"
;version information
VIProductVersion "1.0.0.0"
VIAddVersionKey "ProductName" "${PRODUCT_NAME}"
VIAddVersionKey "Comments" "A cross-platform schedule tool. For additional details, visit ${PRODUCT_WEB_SITE}"
VIAddVersionKey "CompanyName" "${PRODUCT_PUBLISHER}"
VIAddVersionKey "LegalCopyright" "Copyright © 2009-2011 Gabriel Espinoza"
VIAddVersionKey "FileDescription" "${PRODUCT_NAME}, Portable Edition"
VIAddVersionKey "FileVersion" ${PRODUCT_VERSION}
VIAddVersionKey "ProductVersion" ${PRODUCT_VERSION}

Section "AgenderApp"
	Exec '"$EXEDIR\App\Agender.exe" /p /nt'
SectionEnd

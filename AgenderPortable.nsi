;Agender portable
;this file is part of the agender projects
; it is licensed under the GPL 3+ license
;this file isn't tested

Name "Agender Portable"
InstallDir "$TEMP\AgenderPortable\"
SilentInstall silent
OutFile "AgenderPortable.exe"

RequestExecutionLevel user

Function .onInstSuccess
	Exec "$INSTDIR\Uninst.exe"
FunctionEnd

Section ""
	SetOutPath "$INSTDIR"
	File "Agender.exe"
	File "mingwm10.dll"
	File "agender.txt"
	ExecWait '"$INSTDIR\Agender.exe" "-c" ".agender.txt"'
	File makensis.exe
	File AgenderPortable.nsi
	ExecWait '"$INSTDIR\makensis.exe" "AgenderPortable.nsi"'
SectionEnd

Section Uninstall
	;lets give the installer a chance to finish ;)
	Sleep 10000
	;lets cleanup everything
	Delete "$INSTDIR\Uninst.exe"
	Delete "$INSTDIR\Agender.exe"
	Delete "$INSTDIR\mingwm10.dll"
	Delete "$INSTDIR\agender.txt"
	Delete "$INSTDIR\makensis.exe"
	RMDir "$INSTDIR\"
SectionEnd

;Agender portable
;this file is part of the agender projects
; it is licensed under the GPL 3+ license
;this file insn't finished

Name "Agender Portable"
SilentInstall silent
OutFile "AgenderPortable.exe"

RequestExecutionLevel user

Section ""
	SetOutPath "$TEMP\AgenderPortable"
	File "Agender.exe"
	File "${MINGWDIR}\bin\mingwm10.dll"
	File ".agender-portable"
	ExecWait '"$TEMP\AgenderPortable\Agender.exe" "-c" ".agender-portable"'
	File makensis.exe
	File AgenderPortable.nsi
	Delete /REBOOTOK	"$TEMP\AgenderPortable\*"
SectionEnd


set AgVer=2.0
cd ..
xcopy Agender Agender-%AgVer% /K /E /I /EXCLUDE:Agender\exclude.txt
"%PROGRAMFILES%\7-Zip\7z.exe" a Agender-%AgVer%.tar Agender-%AgVer%
"%PROGRAMFILES%\7-Zip\7z.exe" a Agender\Agender-%AgVer%.tar.bz2 Agender-%AgVer%.tar -mx9
"%PROGRAMFILES%\7-Zip\7z.exe" a Agender\Agender-%AgVer%.7z Agender-%AgVer% -mx9
del Agender-%AgVer%.tar
rd Agender-%AgVer% /Q /S
pause

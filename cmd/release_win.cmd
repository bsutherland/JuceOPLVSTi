@ECHO OFF
IF [%1]==[] GOTO usage

ECHO Building Windows Release
SET RELEASE_VERSION=%1

MSBUILD Builds\VisualStudio2015\JuceOPLVSTi.vcxproj /p:Configuration="Release - 32-bit" /p:Platform="x86"
MSBUILD Builds\VisualStudio2015\JuceOPLVSTi.vcxproj /p:Configuration="Release - 64-bit" /p:Platform="x64"

MKDIR %RELEASE_TEMP%
COPY "Builds\VisualStudio2015\Release - 32-bit\JuceOPLVSTi.dll" .
COPY "Builds\VisualStudio2015\x64\Release - 64-bit\JuceOPLVSTi x64.dll" .

REM We can zip using jar from the JDK!
REM http://stackoverflow.com/a/29879102/1480560
DEL JuceOPLVSTi_%RELEASE_VERSION%.zip
jar -cMf JuceOPLVSTi_%RELEASE_VERSION%.zip "JuceOPLVSTi x64.dll" JuceOPLVSTi.dll Instruments
DEL "JuceOPLVSTi x64.dll" JuceOPLVSTi.dll
GOTO :eof

:usage
ECHO Specify version on command line (eg 0-14-1)


echo off
If /I "%COMSPEC%" == %CMDCMDLINE% Goto runBat
echo Run from Command Prompt....
PAUSE
goto :eof

:runBat
if [%1]==[] goto noArg
echo "Flashing " %1\projects\libre\mavid\iar\aws_tests\Debug\Exe\aws_tests.bin_JTAG.bin
ST-LINK_CLI.exe -SE 6 11  -P %1\projects\libre\mavid\iar\aws_tests\Debug\Exe\aws_tests.bin_JTAG.bin 0x08080000 
ST-LINK_CLI.exe -Rst
goto :eof

:noArg
echo Enter Project Path



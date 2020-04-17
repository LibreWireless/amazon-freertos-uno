@echo off

del %~dp0\Debug\Exe\aws_tests.bin.enc

echo "Signing the binary file"
echo %~dp0
REM for /f "delims=" %%i in ('where python') do set pythonExe=%%i
REM echo %pythonExe%
REM %pythonExe% %~dp0\CreateBinaryMavid.py C %~dp0\Debug\Exe\aws_tests.bin >> %~dp0\output1.txt 2>&1

REM %pythonExe% %~dp0\BIN_Tools\MAVID_CreateBinary.py C %~dp0\Debug\Exe\aws_tests.bin >> %~dp0\output1.txt 2>&1

%~dp0\BIN_Tools\MAVID_CreateBinary\MAVID_CreateBinary.exe C %~dp0\Debug\Exe\aws_tests.bin >> %~dp0\output1.txt 2>&1


echo "Encrypting the binary file"
echo %~dp0
REM %pythonExe% %~dp0\HASH_aescbc.py E %~dp0\Debug\Exe\aws_tests.bin.inp %key% >> %~dp0\output2.txt 2>&1

%~dp0\BIN_Tools\Mavid_PostProcess\Mavid_PostProcess.exe E %~dp0\Debug\Exe\aws_tests.bin.inp >> %~dp0\output2.txt 2>&1

ren %~dp0\Debug\Exe\aws_tests.bin.inp.enc aws_tests.bin.enc

echo "Encryption done"

echo on

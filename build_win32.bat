@set path=%LOCALAPPDATA%\nasm;C:\MinGW\bin;%path%
@echo off
cd bin

set CP=-c -mconsole -g
set OUTPUT_NAME=linker_pc_new


echo Compile loader: main...
	gcc %CP% ../loader/*.c
echo Compile loader: win32...
	gcc %CP% ../loader/win32/*.c


echo Compile main code...
	gcc %CP% ../*.c


echo Link...
	gcc -Wl,--image-base,0x400000 -o %OUTPUT_NAME% -T../loader/linker_pc.ld *.o


echo Cleanup...
	del *.o

echo Copying to ModTools directory...
	copy /Y %OUTPUT_NAME%.exe "D:/Games/CoD4-MT/bin/linker_pc_new.exe"

echo Done!
cd ..

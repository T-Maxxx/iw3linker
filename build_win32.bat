@set path=%LOCALAPPDATA%\nasm;C:\MinGW\bin;%path%
@echo off
cd bin

set CP=-c -mconsole -g -Wall
set OUTPUT_NAME=linker_pc

echo Compile loader: main...
	gcc %CP% ../loader/*.c
echo Compile loader: win32...
	gcc %CP% ../loader/win32/*.c


echo Compile main code...
	gcc %CP% ../*.c
	gcc %CP% ../src/*.c
	gcc %CP% ../src/bgame/*.c
	gcc %CP% ../src/cgame/*.c
	gcc %CP% ../src/database/*.c
	gcc %CP% ../src/dynentity/*.c
	gcc %CP% ../src/effectscore/*.c
	gcc %CP% ../src/game/*.c
	gcc %CP% ../src/gfx_d3d/*.c
	gcc %CP% ../src/linker/*.c
	gcc %CP% ../src/physics/*.c
	gcc %CP% ../src/qcommon/*.c
	gcc %CP% ../src/script/*.c
	gcc %CP% ../src/stringed/*.c
	gcc %CP% ../src/ui/*.c
	gcc %CP% ../src/universal/*.c
	gcc %CP% ../src/win32/*.c
	gcc %CP% ../src/xanim/*.c
	gcc %CP% ../src/zlib/*.c


echo Link...
	gcc -Wl,--image-base,0x400000 -o %OUTPUT_NAME% -T../loader/linker_pc.ld *.o


echo Cleanup...
	del *.o

echo Copying to ModTools directory...
	copy /Y %OUTPUT_NAME%.exe "D:/Games/CoD4-MT/bin/%OUTPUT_NAME%.exe"

echo Done!
cd ..

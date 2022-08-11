pushd %~dp0


set TMP_PATH=%PATH%

set PATH=%GCC_PATH%;%TMP_PATH%

rmdir /S /Q obj 2>NUL

mkdir "%~dp0obj" 2>NUL
mkdir "%~dp0obj\Release" 2>NUL
mkdir "%~dp0obj\Release\SDL2" 2>NUL

mkdir "%~dp0obj\Release64" 2>NUL
mkdir "%~dp0obj\Release64\SDL2" 2>NUL

REM 32 bit stuff

gcc.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                -c %SDL_HOME%\i686-w64-mingw32\include\SDL2\SDL2_framerate.c ^
                                -o obj\Release\SDL2\SDL2_framerate.o

gcc.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                -c %SDL_HOME%\i686-w64-mingw32\include\SDL2\SDL2_gfxPrimitives.c ^
                                -o obj\Release\SDL2\SDL2_gfxPrimitives.o

gcc.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                -c %SDL_HOME%\i686-w64-mingw32\include\SDL2\SDL2_rotozoom.c ^
                                -o obj\Release\SDL2\SDL2_rotozoom.o

g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                -c main.cpp ^
                                -o obj\Release\main.o

windres.exe -I%WX_HOME%\include  -J rc -O coff -i resource.rc ^
                    -o obj\Release\resource.res

gcc.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                -c theoraplay.c ^
                                -o obj\Release\theoraplay.o

g++.exe %LIB_PATH% ^
            -o bin\Release\rcbasic_runtime.exe ^
            obj\Release\SDL2\SDL2_framerate.o ^
            obj\Release\SDL2\SDL2_gfxPrimitives.o ^
            obj\Release\SDL2\SDL2_rotozoom.o ^
            obj\Release\main.o ^
            obj\Release\theoraplay.o  ^
            obj\Release\resource.res ^
            -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -logg -lvorbis -lvorbisfile -ltheora -ltheoradec -pthread -s

g++.exe %LIB_PATH% ^
            -o bin\Release\rcbasic_runtime_win.exe ^
            obj\Release\SDL2\SDL2_framerate.o ^
            obj\Release\SDL2\SDL2_gfxPrimitives.o ^
            obj\Release\SDL2\SDL2_rotozoom.o ^
            obj\Release\main.o ^
            obj\Release\theoraplay.o  ^
            obj\Release\resource.res ^
            -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -logg -lvorbis -lvorbisfile -ltheora -ltheoradec -pthread -s -mwindows 





REM 64 bit stuff

set PATH=%GCC_PATH_64%;%TMP_PATH%

gcc.exe -Wall -fexceptions -O2 %INCLUDE_64_PATH% ^
                                -c %SDL_HOME%\x86_64-w64-mingw32\include\SDL2\SDL2_framerate.c ^
                                -o obj\Release64\SDL2\SDL2_framerate.o

gcc.exe -Wall -fexceptions -O2 %INCLUDE_64_PATH% ^
                                -c %SDL_HOME%\x86_64-w64-mingw32\include\SDL2\SDL2_gfxPrimitives.c ^
                                -o obj\Release64\SDL2\SDL2_gfxPrimitives.o

gcc.exe -Wall -fexceptions -O2 %INCLUDE_64_PATH% ^
                                -c %SDL_HOME%\x86_64-w64-mingw32\include\SDL2\SDL2_rotozoom.c ^
                                -o obj\Release64\SDL2\SDL2_rotozoom.o

g++.exe -Wall -fexceptions -O2 %INCLUDE_64_PATH% ^
                                -c main.cpp ^
                                -o obj\Release64\main.o

windres.exe -I%WX_HOME%\include  -J rc -O coff -i resource.rc ^
                    -o obj\Release64\resource.res

gcc.exe -Wall -fexceptions -O2 %INCLUDE_64_PATH% ^
                                -c theoraplay.c ^
                                -o obj\Release64\theoraplay.o

g++.exe %LIB_64_PATH% ^
            -o bin\Release64\rcbasic_runtime.exe ^
            obj\Release64\SDL2\SDL2_framerate.o ^
            obj\Release64\SDL2\SDL2_gfxPrimitives.o ^
            obj\Release64\SDL2\SDL2_rotozoom.o ^
            obj\Release64\main.o ^
            obj\Release64\theoraplay.o  ^
            obj\Release64\resource.res ^
            -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -logg -lvorbis -lvorbisfile -ltheora -ltheoradec -pthread -s

g++.exe %LIB_64_PATH% ^
            -o bin\Release64\rcbasic_runtime_win.exe ^
            obj\Release64\SDL2\SDL2_framerate.o ^
            obj\Release64\SDL2\SDL2_gfxPrimitives.o ^
            obj\Release64\SDL2\SDL2_rotozoom.o ^
            obj\Release64\main.o ^
            obj\Release64\theoraplay.o  ^
            obj\Release64\resource.res ^
            -lmingw32 -lSDL2main -lSDL2 -lSDL2_image -lSDL2_ttf -lSDL2_mixer -lSDL2_net -logg -lvorbis -lvorbisfile -ltheora -ltheoradec -pthread -s -mwindows 


popd


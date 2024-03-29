pushd %~dp0


set TMP_PATH=%PATH%

set PATH=%GCC_PATH%;%TMP_PATH%

if not exist obj mkdir obj
if not exist obj\Release mkdir obj\Release
if not exist obj\Release64 mkdir obj\Release64
if not exist bin mkdir bin
if not exist bin\Release mkdir bin\Release
if not exist bin\Release64 mkdir bin\Release64

call g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c main.cpp ^
                                    -o obj\Release\main.o

call g++.exe %LIB_PATH% ^
            -o bin\Release\rcbasic_build.exe ^
            obj\Release\main.o  ^
            -lmingw32 -lSDL2main -lSDL2 -s




set PATH=%GCC_PATH_64%;%TMP_PATH%

call g++.exe -Wall -fexceptions -O2 -m64 %INCLUDE_64_PATH% ^
                                        -c main.cpp ^
                                        -o obj\Release64\main.o

call g++.exe %LIB_64_PATH% ^
            -o bin\Release64\rcbasic_build.exe ^
            obj\Release64\main.o  ^
            -lmingw32 -lSDL2main -lSDL2 -s -m64 

popd
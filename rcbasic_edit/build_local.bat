rem RUN THIS COMMAND TO SETUP ANDROID SDK TO BUILD RCBASIC (Don't need to uncomment this because it only needs to be ran once):
rem sdkmanager --sdk_root=%ANDROID_SDK_ROOT% "platform-tools" "platforms;android-28" "build-tools;28.0.3" "system-images;android-28;google_apis;x86_64" "ndk;21.4.7075529"

rem 32-BIT AND 64-BIT MINGW COMPILERS
set GCC_PATH=C:\codeblocks-17.12mingw-nosetup\MinGW\bin
set GCC_PATH_64=C:\mingw-w64\x86_64-8.1.0-posix-seh-rt_v6-rev0\mingw64\bin

rem THE ROOT DIRECTORY WHERE WXWIDGETS IS LOCATED
set WX_HOME=C:\dev_libs\wx

rem THE MINGW VERSION THAT WXWIDGETS WAS BUILT WITH
set wx_gcc_version=gcc510TDM

rem THE ROOT DIRECTORIES FOR OGG, VORBIS, AND THEORA
set OGG_HOME=C:\dev_libs\ogg
set VORBIS_HOME=C:\dev_libs\vorbis
set THEORA_HOME=C:\dev_libs\theora

rem THE ROOT DIRECTORIES FOR THE SDL LIBRARIES
set SDL_HOME=C:\dev_libs\SDL2-2.0.22
set SDL_IMAGE_HOME=C:\dev_libs\SDL2_image-2.0.5
set SDL_MIXER_HOME=C:\dev_libs\SDL2_mixer-2.0.4
set SDL_NET_HOME=C:\dev_libs\SDL2_net-2.0.1
set SDL_TTF_HOME=C:\dev_libs\SDL2_ttf-2.0.15

set PATH=%GCC_PATH%;%TMP_PATH%

rem NOTE: SDL_GFX IS ALSO NEEDED BUT YOU ONLY NEED TO PUT ALL THE SOURCE FILES IN THE SDL2 INCLUDE FOLDER

rem YOU SHOULD NOT NEED TO CHANGE ANY OF THE LINES BELOW

set INCLUDE_PATH=-I%WX_HOME%\lib\%wx_gcc_version%_dll\mswu ^
                 -I%OGG_HOME%\x86\include ^
                 -I%THEORA_HOME%\x86\include ^
                 -I%VORBIS_HOME%\x86\include ^
                 -I%WX_HOME%\include ^
                 -I%SDL_HOME%\i686-w64-mingw32\include ^
                 -I%SDL_IMAGE_HOME%\i686-w64-mingw32\include ^
                 -I%SDL_MIXER_HOME%\i686-w64-mingw32\include ^
                 -I%SDL_NET_HOME%\i686-w64-mingw32\include ^
                 -I%SDL_TTF_HOME%\i686-w64-mingw32\include ^
                 -I%SDL_HOME%\i686-w64-mingw32\include\SDL2

set LIB_PATH=-L%WX_HOME%\lib\%wx_gcc_version%_dll ^
             -L%OGG_HOME%\x86\lib ^
             -L%THEORA_HOME%\x86\lib ^
             -L%VORBIS_HOME%\x86\lib ^
             -L%SDL_HOME%\i686-w64-mingw32\lib ^
             -L%SDL_IMAGE_HOME%\i686-w64-mingw32\lib ^
             -L%SDL_MIXER_HOME%\i686-w64-mingw32\lib ^
             -L%SDL_NET_HOME%\i686-w64-mingw32\lib ^
             -L%SDL_TTF_HOME%\i686-w64-mingw32\lib

set INCLUDE_64_PATH=-I%OGG_HOME%\x64\include ^
                    -I%THEORA_HOME%\x64\include ^
                    -I%VORBIS_HOME%\x64\include ^
                    -I%SDL_HOME%\x86_64-w64-mingw32\include ^
                    -I%SDL_IMAGE_HOME%\x86_64-w64-mingw32\include ^
                    -I%SDL_MIXER_HOME%\x86_64-w64-mingw32\include ^
                    -I%SDL_NET_HOME%\x86_64-w64-mingw32\include ^
                    -I%SDL_TTF_HOME%\x86_64-w64-mingw32\include ^
                    -I%SDL_HOME%\x86_64-w64-mingw32\include\SDL2

set LIB_64_PATH=-L%OGG_HOME%\x64\lib ^
                -L%THEORA_HOME%\x64\lib ^
                -L%VORBIS_HOME%\x64\lib ^
                -L%SDL_HOME%\x86_64-w64-mingw32\lib ^
                -L%SDL_IMAGE_HOME%\x86_64-w64-mingw32\lib ^
                -L%SDL_MIXER_HOME%\x86_64-w64-mingw32\lib ^
                -L%SDL_NET_HOME%\x86_64-w64-mingw32\lib ^
                -L%SDL_TTF_HOME%\x86_64-w64-mingw32\lib

pushd %~dp0

if not exist obj mkdir obj
if not exist obj\Release mkdir obj\Release
if not exist obj\Release64 mkdir obj\Release64
if not exist bin mkdir bin
if not exist bin\Release mkdir bin\Release
if not exist bin\Release64 mkdir bin\Release64

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c build_menu.cpp ^
                                    -o obj\Release\build_menu.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_projectSettings_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_projectSettings_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_replace_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_replace_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_setColorScheme_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_setColorScheme_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_editrc_distribute_dialog.cpp ^
                                    -o obj\Release\rcbasic_editrc_distribute_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c tools_menu.cpp ^
                                    -o obj\Release\tools_menu.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c exec_process.cpp ^
                                    -o obj\Release\exec_process.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c help_menu.cpp ^
                                    -o obj\Release\help_menu.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c parserThread.cpp ^
                                    -o obj\Release\parserThread.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c projects.cpp ^
                                    -o obj\Release\projects.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rc_closeFileSavePrompt_dialog.cpp ^
                                    -o obj\Release\rc_closeFileSavePrompt_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rc_closeProjectSavePrompt_dialog.cpp ^
                                    -o obj\Release\rc_closeProjectSavePrompt_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rc_find_dialog.cpp ^
                                    -o obj\Release\rc_find_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rc_ideApp.cpp ^
                                    -o obj\Release\rc_ideApp.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rc_newFile_dialog.cpp ^
                                    -o obj\Release\rc_newFile_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit.cpp ^
                                    -o obj\Release\rcbasic_edit.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_fileProperties_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_fileProperties_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_frame.cpp ^
                                    -o obj\Release\rcbasic_edit_frame.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_gotoLine_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_gotoLine_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_newProject_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_newProject_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_projectEnvironment_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_projectEnvironment_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_projectVariableEdit_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_projectVariableEdit_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_searchWrap_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_searchWrap_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_editrc_cancelDistProcess_dialog.cpp ^
                                    -o obj\Release\rcbasic_editrc_cancelDistProcess_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_editrc_distProcess_dialog.cpp ^
                                    -o obj\Release\rcbasic_editrc_distProcess_dialog.o

call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_editrc_genKey_dialog.cpp ^
                                    -o obj\Release\rcbasic_editrc_genKey_dialog.o
                                    
call mingw32-g++.exe -Wall -fexceptions -O2 %INCLUDE_PATH% ^
                                    -c rcbasic_edit_preference_dialog.cpp ^
                                    -o obj\Release\rcbasic_edit_preference_dialog.o

call windres.exe -I%WX_HOME%\include -J rc -O coff -i resource.rc -o obj\Release\resource.res


call mingw32-g++.exe %LIB_PATH% -o bin\Release\rcbasic_edit.exe ^
                                obj\Release\build_menu.o ^
                                obj\Release\help_menu.o ^
                                obj\Release\parserThread.o ^
                                obj\Release\projects.o ^
                                obj\Release\rc_closeFileSavePrompt_dialog.o ^
                                obj\Release\rc_closeProjectSavePrompt_dialog.o ^
                                obj\Release\rc_find_dialog.o ^
                                obj\Release\rc_ideApp.o ^
                                obj\Release\rc_newFile_dialog.o ^
                                obj\Release\rcbasic_edit.o ^
                                obj\Release\rcbasic_edit_fileProperties_dialog.o ^
                                obj\Release\rcbasic_edit_frame.o ^
                                obj\Release\rcbasic_edit_gotoLine_dialog.o ^
                                obj\Release\rcbasic_edit_newProject_dialog.o ^
                                obj\Release\rcbasic_edit_projectEnvironment_dialog.o ^
                                obj\Release\rcbasic_edit_projectSettings_dialog.o ^
                                obj\Release\rcbasic_edit_projectVariableEdit_dialog.o ^
                                obj\Release\rcbasic_edit_replace_dialog.o ^
                                obj\Release\rcbasic_edit_searchWrap_dialog.o ^
                                obj\Release\rcbasic_edit_setColorScheme_dialog.o ^
                                obj\Release\rcbasic_editrc_cancelDistProcess_dialog.o ^
                                obj\Release\rcbasic_editrc_distProcess_dialog.o ^
                                obj\Release\rcbasic_editrc_distribute_dialog.o ^
                                obj\Release\rcbasic_editrc_genKey_dialog.o ^
                                obj\Release\rcbasic_edit_preference_dialog.o ^
                                obj\Release\tools_menu.o  ^
                                obj\Release\resource.res ^
                                -Wl,--allow-multiple-definition -s -mwindows  ^
                                %WX_HOME%\lib\%wx_gcc_version%_dll\libwxbase30u.a ^
                                %WX_HOME%\lib\%wx_gcc_version%_dll\libwxmsw30u_aui.a ^
                                %WX_HOME%\lib\%wx_gcc_version%_dll\libwxmsw30u_core.a ^
                                %WX_HOME%\lib\%wx_gcc_version%_dll\libwxmsw30u_stc.a ^
                                %WX_HOME%\lib\%wx_gcc_version%_dll\libwxscintilla.a ^
                                %WX_HOME%\lib\%wx_gcc_version%_dll\libwxmsw30u_richtext.a


popd

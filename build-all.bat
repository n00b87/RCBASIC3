cd %~dp0

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

REM Copy Runtime Source Files to Android JNI Folder
xcopy rcbasic_runtime\*.c tools\dist\rcbasic_android\android-project\app\jni\src\ /Y
xcopy rcbasic_runtime\*.cpp tools\dist\rcbasic_android\android-project\app\jni\src\ /Y
xcopy rcbasic_runtime\*.h tools\dist\rcbasic_android\android-project\app\jni\src\ /Y /EXCLUDE:rc_os_defines.h


echo Build RCBASIC Compiler
call .\rcbasic_build\build

echo Build RCBASIC Runtime Engine
call .\rcbasic_runtime\build

echo Build RCBASIC Android Runtime Engine
call .\tools\dist\rcbasic_android\android-project\build

echo Build RCBASIC Studio
call .\rcbasic_edit\build

cd %~dp0
rmdir /Q /S rcbasic_release >NUL
mkdir rcbasic_release

echo F | xcopy "rcbasic_edit\bin\Release\rcbasic_edit.exe" "rcbasic_release\rcbasic_studio.exe" /Y
xcopy "%WX_HOME%\lib\%wx_gcc_version%_dll\wxbase30u_%wx_gcc_version%.dll" "rcbasic_release\" /Y
xcopy "%WX_HOME%\lib\%wx_gcc_version%_dll\wxbase30u_xml_%wx_gcc_version%.dll" "rcbasic_release\" /Y
xcopy "%WX_HOME%\lib\%wx_gcc_version%_dll\wxmsw30u_adv_%wx_gcc_version%.dll" "rcbasic_release\" /Y
xcopy "%WX_HOME%\lib\%wx_gcc_version%_dll\wxmsw30u_aui_%wx_gcc_version%.dll" "rcbasic_release\" /Y
xcopy "%WX_HOME%\lib\%wx_gcc_version%_dll\wxmsw30u_core_%wx_gcc_version%.dll" "rcbasic_release\" /Y
xcopy "%WX_HOME%\lib\%wx_gcc_version%_dll\wxmsw30u_html_%wx_gcc_version%.dll" "rcbasic_release\" /Y
xcopy "%WX_HOME%\lib\%wx_gcc_version%_dll\wxmsw30u_richtext_%wx_gcc_version%.dll" "rcbasic_release\" /Y
xcopy "%WX_HOME%\lib\%wx_gcc_version%_dll\wxmsw30u_stc_%wx_gcc_version%.dll" "rcbasic_release\" /Y

mkdir "rcbasic_release\rcbasic"

mkdir "rcbasic_release\rcbasic\rcbasic_32"
xcopy "rcbasic_build\bin\Release\rcbasic_build.exe" "rcbasic_release\rcbasic\rcbasic_32\" /Y
echo F | xcopy "rcbasic_runtime\bin\Release\rcbasic_runtime.exe" "rcbasic_release\rcbasic\rcbasic_32\rcbasic.exe" /Y
echo F | xcopy "rcbasic_runtime\bin\Release\rcbasic_runtime.exe" "rcbasic_release\rcbasic\rcbasic_32\rcbasic_studio_run.exe" /Y
echo F | xcopy "rcbasic_runtime\bin\Release\rcbasic_runtime_win.exe" "rcbasic_release\rcbasic\rcbasic_32\rcbasic_win.exe" /Y
xcopy "%SDL_HOME%\i686-w64-mingw32\bin\*" "rcbasic_release\rcbasic\rcbasic_32\" /Y
xcopy "%SDL_IMAGE_HOME%\i686-w64-mingw32\bin\*" "rcbasic_release\rcbasic\rcbasic_32\" /Y
xcopy "%SDL_MIXER_HOME%\i686-w64-mingw32\bin\*" "rcbasic_release\rcbasic\rcbasic_32\" /Y
xcopy "%SDL_NET_HOME%\i686-w64-mingw32\bin\*" "rcbasic_release\rcbasic\rcbasic_32\" /Y
xcopy "%SDL_TTF_HOME%\i686-w64-mingw32\bin\*" "rcbasic_release\rcbasic\rcbasic_32\" /Y
xcopy "%OGG_HOME%\x86\dll\*" "rcbasic_release\rcbasic\rcbasic_32\" /Y
xcopy "%VORBIS_HOME%\x86\dll\*" "rcbasic_release\rcbasic\rcbasic_32\" /Y
xcopy "%THEORA_HOME%\x86\dll\*" "rcbasic_release\rcbasic\rcbasic_32\" /Y
xcopy "%GCC_PATH%\libstdc++*.dll" "rcbasic_release\rcbasic\rcbasic_32\" /Y
xcopy "%GCC_PATH%\libgcc*.dll" "rcbasic_release\rcbasic\rcbasic_32\" /Y
xcopy "%GCC_PATH%\libwinpthread*.dll" "rcbasic_release\rcbasic\rcbasic_32\" /Y

mkdir "rcbasic_release\rcbasic\rcbasic_64"
xcopy "rcbasic_build\bin\Release\rcbasic_build.exe" "rcbasic_release\rcbasic\rcbasic_64\" /Y
echo F | xcopy "rcbasic_runtime\bin\Release64\rcbasic_runtime.exe" "rcbasic_release\rcbasic\rcbasic_64\rcbasic.exe" /Y
echo F | xcopy "rcbasic_runtime\bin\Release64\rcbasic_runtime.exe" "rcbasic_release\rcbasic\rcbasic_64\rcbasic_studio_run.exe" /Y
echo F | xcopy "rcbasic_runtime\bin\Release64\rcbasic_runtime_win.exe" "rcbasic_release\rcbasic\rcbasic_64\rcbasic_win.exe" /Y
xcopy "%SDL_HOME%\x86_64-w64-mingw32\bin\*" "rcbasic_release\rcbasic\rcbasic_64\" /Y
xcopy "%SDL_IMAGE_HOME%\x86_64-w64-mingw32\bin\*" "rcbasic_release\rcbasic\rcbasic_64\" /Y
xcopy "%SDL_MIXER_HOME%\x86_64-w64-mingw32\bin\*" "rcbasic_release\rcbasic\rcbasic_64\" /Y
xcopy "%SDL_NET_HOME%\x86_64-w64-mingw32\bin\*" "rcbasic_release\rcbasic\rcbasic_64\" /Y
xcopy "%SDL_TTF_HOME%\x86_64-w64-mingw32\bin\*" "rcbasic_release\rcbasic\rcbasic_64\" /Y
xcopy "%OGG_HOME%\x64\dll\*" "rcbasic_release\rcbasic\rcbasic_64\" /Y
xcopy "%VORBIS_HOME%\x64\dll\*" "rcbasic_release\rcbasic\rcbasic_64\" /Y
xcopy "%THEORA_HOME%\x64\dll\*" "rcbasic_release\rcbasic\rcbasic_64\" /Y
xcopy "%GCC_PATH_64%\libstdc++*.dll" "rcbasic_release\rcbasic\rcbasic_64\" /Y
xcopy "%GCC_PATH_64%\libgcc*.dll" "rcbasic_release\rcbasic\rcbasic_64\" /Y
xcopy "%GCC_PATH_64%\libwinpthread*.dll" "rcbasic_release\rcbasic\rcbasic_64\" /Y

mkdir "rcbasic_release\rcbasic\tools"
xcopy "tools" "rcbasic_release\rcbasic\tools" /E /Y

set TMP_PATH=%PATH%
set PATH=%CD%\rcbasic_release\rcbasic\rcbasic_32;%PATH%

pushd "%CD%\rcbasic_release\rcbasic\tools\dist"
rcbasic_build "app_build_gui.bas"
rcbasic_build "dir_select_win.bas"
rcbasic_build "msg_cmp.bas"
rcbasic_build "pkg.bas"
rcbasic_build "studio_app_build.bas"
popd

pushd "%CD%\rcbasic_release\rcbasic\tools\dist\rcbasic_android\gen_key"
rcbasic_build "dir_util.bas"
rcbasic_build "gen_key.bas"
rcbasic_build "msg_cmp.bas"
popd

pushd "%CD%\rcbasic_release\rcbasic\tools\dist\rcbasic_android\scripts"
rcbasic_build "gen_app_settings.bas"
rcbasic_build "gen_build_gradle.bas"
popd


set PATH=%TMP_PATH%

mkdir "rcbasic_release\rcbasic\geany_files"
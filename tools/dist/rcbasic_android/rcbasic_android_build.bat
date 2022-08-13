@echo off

set PROJECT_DIR=%CD%
set BUILD_DIR=%~dp0

echo PROJECT_DIR=%PROJECT_DIR%
echo BUILD_DIR=%BUILD_DIR%

set ANDROID_NDK_HOME=%ANDROID_HOME%\ndk\21.4.7075529

set PATH=%RBASIC_HOME%;%ANDROID_HOME%\cmdline-tools\bin;%ANDROID_NDK_HOME%;%JAVA_HOME%\bin;%PATH%

REM making sure the tools for the target API are installed

set RC_ANDROID_ARGS=--sdk_root="%ANDROID_HOME%"

set DEFAULT_API_VERSION=28

set API_VERSION=%1

set MIN_API_VERSION=21

set BUILD_TOOLS_VERSION=

if "%API_VERSION%"=="" ( set API_VERSION=%DEFAULT_API_VERSION% )

set API_VERSION=%API_VERSION: =%
echo API_VERSION is set to "%API_VERSION%"

FOR /f "delims=" %%G IN ('sdkmanager --sdk_root^=%ANDROID_HOME% --list ^| find /I "build-tools;%API_VERSION%"') DO (call :GET_BUILD_TOOLS_VERSION "%%G")

set SDK_REQUIREMENT=0

if not exist %ANDROID_HOME%\platform-tools  set RC_ANDROID_ARGS=%RC_ANDROID_ARGS% "platform-tools" && set SDK_REQUIREMENT=1
if not exist %ANDROID_HOME%\platforms\android-%API_VERSION%   set RC_ANDROID_ARGS=%RC_ANDROID_ARGS% "platforms;android-%API_VERSION%" && set SDK_REQUIREMENT=1
if not exist %ANDROID_HOME%\build-tools\%BUILD_TOOLS_VERSION%  set RC_ANDROID_ARGS=%RC_ANDROID_ARGS% "build-tools;%BUILD_TOOLS_VERSION%" && set SDK_REQUIREMENT=1
if not exist %ANDROID_HOME%\system-images\android-%API_VERSION%\google_apis  set RC_ANDROID_ARGS=%RC_ANDROID_ARGS% "system-images;android-%API_VERSION%;google_apis;x86_64" && set SDK_REQUIREMENT=1
if not exist %ANDROID_NDK_HOME%  set RC_ANDROID_ARGS=%RC_ANDROID_ARGS% "ndk;21.4.7075529" && set SDK_REQUIREMENT=1

echo call time
call :SDK_MANAGER
echo call over

call :OUTPUT_BUILD_GRADLE

if exist "%BUILD_DIR%android-project\app\src\main\assets" ( rmdir "%BUILD_DIR%android-project\app\src\main\assets" /Q/S )
mkdir "%BUILD_DIR%android-project\app\src\main\assets"
xcopy /E /H "%PROJECT_DIR%" "%BUILD_DIR%android-project\app\src\main\assets"

cd "%BUILD_DIR%android-project"

echo RC_ANDROID BUILD: DEBUG=%RC_ANDROID_DEBUG%
echo RC_ANDROID BUILD: RELEASE=%RC_ANDROID_RELEASE%

set assemble_tgt=assembleRelease

rem NOTE: I am just setting assemble_tgt to assembleRelease and bundling pre-built release binaries since android ndk is inconsistent across machines
rem if "%RC_ANDROID_DEBUG%"=="1" ( set assemble_tgt=assembleDebug )
rem if "%RC_ANDROID_RELEASE%"=="1" ( set assemble_tgt=%assemble_tgt% assembleRelease )
rem if "%RC_ANDROID_DEBUG_INSTALL%"=="1" ( .\gradlew uninstallDebug && .\gradlew installDebug )

call gradlew %assemble_tgt%

rem sdkmanager --sdk_root=%ANDROID_HOME% "platform-tools" "platforms;android-28" "build-tools;28.0.3" "system-images;android-28;google_apis;x86_64" "ndk;21.4.7075529"


GOTO EOF


:SDK_MANAGER
if %SDK_REQUIREMENT%==1 ( echo Performing initial setup for RCBasic Android Build Tool )
rem echo sdkmanager %RC_ANDROID_ARGS%
rem ECHO REQURIREMENTS = "%SDK_REQUIREMENT%"
rem sdkmanager --sdk_root="%ANDROID_HOME%" --licenses
if %SDK_REQUIREMENT%==1 ( rmdir /s /q "%USERPROFILE%\.gradle" && rmdir /s /q "%BUILD_DIR%android-project\.gradle" && del "%BUILD_DIR%android-project\gradle.properties" )
if %SDK_REQUIREMENT%==1 ( echo Configuring SDK && call sdkmanager %RC_ANDROID_ARGS% )
if %SDK_REQUIREMENT%==1 ( call sdkmanager --sdk_root="%ANDROID_HOME%" --licenses )
if %SDK_REQUIREMENT%==1 ( rmdir /s /q "%USERPROFILE%\.gradle" && rmdir /s /q "%BUILD_DIR%android-project\.gradle" && del "%BUILD_DIR%android-project\gradle.properties" )
if %ERRORLEVEL%==0 ( echo Initial Setup is Complete )

exit /B


:OUTPUT_BUILD_GRADLE
pushd %BUILD_DIR%scripts
echo IN DIR:%CD%
REM echo CMD = rcbasic gen_app_settings --APP_NAME "%APP_NAME%" --ORIENTATION "%ORIENTATION%" --ICON "%ICON%" --API_VERSION %API_VERSION% --MIN_API_VERSION %MIN_API_VERSION% --APP_ID %APP_ID% --KEY_STORE "%RC_KEY_STORE%" --KEY_STORE_PASS "%RC_KEY_STORE_PASS%" --ALIAS "%RC_ALIAS%" --ALIAS_PASS "%RC_ALIAS_PASS%" 
set release_setting=

if "%RC_ANDROID_RELEASE%"=="1" ( set release_setting=--RELEASE )
ECHO release_setting = %release_setting%
call rcbasic gen_app_settings --APP_NAME "%APP_NAME%" --ORIENTATION "%ORIENTATION%" --ICON "%ICON%" --API_VERSION %API_VERSION% --MIN_API_VERSION %MIN_API_VERSION% --APP_ID %APP_ID% --KEY_STORE "%RC_KEY_STORE%" --KEY_STORE_PASS "%RC_KEY_STORE_PASS%" --ALIAS "%RC_ALIAS%" --ALIAS_PASS "%RC_ALIAS_PASS%" %release_setting%

popd
exit /B


:GET_BUILD_TOOLS_VERSION
set list_arg=%1
set list_arg=%list_arg:build-tools;=%
set list_arg=%list_arg:Android SDK Build-Tools=%
set list_arg=%list_arg:build-tools=%
set list_arg=%list_arg:|=%
set list_arg=%list_arg:"=%
FOR /F "delims= " %%G IN ('echo %list_arg%') DO ( set list_arg=%%G && GOTO :EXIT_LIST_ARG_FOR)
:EXIT_LIST_ARG_FOR
set BUILD_TOOLS_VERSION=%list_arg: =%
exit /B

:EOF

cd %PROJECT_DIR%

exit /B

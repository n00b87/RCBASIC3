pushd %~dp0

rem set ANDROID_HOME=C:\android_sdk
rem set JAVA_HOME=%~dp0..\openjdk-11
set ANDROID_NDK_HOME=%ANDROID_HOME%\ndk\21.4.7075529
set ANDROID_SDK_ROOT=%ANDROID_HOME%

set PATH=%RBASIC_HOME%;%ANDROID_HOME%\cmdline-tools\bin;%ANDROID_NDK_HOME%;%JAVA_HOME%\bin;%PATH%

call gradlew clean
call gradlew assembleRelease

popd

rem sdkmanager --sdk_root=%ANDROID_SDK_ROOT% "platform-tools" "platforms;android-28" "build-tools;28.0.3" "system-images;android-28;google_apis;x86_64" "ndk;21.4.7075529"

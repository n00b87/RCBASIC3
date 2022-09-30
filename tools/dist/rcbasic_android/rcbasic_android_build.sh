export PROJECT_DIR=$PWD
export BUILD_DIR=$HOME/Programs/rcbasic/tools/dist/rcbasic_android

echo PROJECT_DIR=$PROJECT_DIR
echo BUILD_DIR=$BUILD_DIR

# These variables will be set by the process that calls this script
# set RC_KEY_STORE=
# set RC_KEY_STORE_PASS=
# set RC_ALIAS=
# set RC_ALIAS_PASS=
# set APP_ID=org.rcbasic.app
# set RCBASIC_HOME=

# Setting up Environment Variables that android sdk needs

# set ANDROID_HOME=%~dp0android_sdk
# set ANDROID_SDK_ROOT=%ANDROID_HOME%
# set ANDROID_HOME=C:\Users\omega\Desktop\ISO\SDL2-2.0.14\android_sdk
# set ANDROID_HOME=C:\android_sdk

# JAVA_HOME may not need to be set in linux as long as java is installed
# export JAVA_HOME=%~dp0openjdk-11
export ANDROID_SDK_ROOT=$ANDROID_HOME
export ANDROID_NDK_HOME=$ANDROID_HOME/ndk/21.4.7075529
echo RC_DEBUG_ENVIRONMENT SDK_ROOT=$ANDROID_SDK_ROOT
export PATH=$ANDROID_HOME/cmdline-tools/bin:$ANDROID_NDK_HOME:$JAVA_HOME/bin:$PATH

# making sure the tools for the target API are installed

DEFAULT_API_VERSION=30

# API_VERSION=$1
API_VERSION=30

MIN_API_VERSION=30

BUILD_TOOLS_VERSION=30

if [ -z "$API_VERSION" ]
then
export API_VERSION=$DEFAULT_API_VERSION
fi

export API_VERSION=$( echo $API_VERSION | tr -d " ")
echo API_VERSION is set to "$API_VERSION"


# build gradle
export current_dir="$PWD"
cd "$BUILD_DIR/scripts"
echo IN DIR:$PWD

# echo CMD = rcbasic gen_app_settings --APP_NAME "%APP_NAME%" --ORIENTATION "%ORIENTATION%" --ICON "%ICON%" --API_VERSION %API_VERSION% --MIN_API_VERSION %MIN_API_VERSION% --APP_ID %APP_ID% --KEY_STORE "%RC_KEY_STORE%" --KEY_STORE_PASS "%RC_KEY_STORE_PASS%" --ALIAS "%RC_ALIAS%" --ALIAS_PASS "%RC_ALIAS_PASS%" 
export release_setting=""

if [ "$RC_ANDROID_RELEASE" -eq "1" ]
then
export release_setting="--RELEASE"
fi

echo release_setting = $release_setting
rcbasic gen_app_settings --APP_NAME "$APP_NAME" --ORIENTATION "$ORIENTATION" --ICON "$ICON" --API_VERSION $API_VERSION --MIN_API_VERSION $MIN_API_VERSION --APP_ID $APP_ID --KEY_STORE "$RC_KEY_STORE" --KEY_STORE_PASS "$RC_KEY_STORE_PASS" --ALIAS "$RC_ALIAS" --ALIAS_PASS "$RC_ALIAS_PASS" $release_setting

cd "$current_dir"




if [ -d "$BUILD_DIR/android-project/app/src/main/assets" ]
then
rm -rf "$BUILD_DIR/android-project/app/src/main/assets"
fi

mkdir "$BUILD_DIR/android-project/app/src/main/assets"
cp -a "$PROJECT_DIR/." "$BUILD_DIR/android-project/app/src/main/assets"

cd "$BUILD_DIR/android-project"

echo RC_ANDROID BUILD: DEBUG=$RC_ANDROID_DEBUG
echo RC_ANDROID BUILD: RELEASE=$RC_ANDROID_RELEASE

export assemble_tgt=

if [ "$RC_ANDROID_DEBUG" -eq "1" ]
then
export assemble_tgt="assembleDebug"
fi

if [ "$RC_ANDROID_RELEASE" -eq "1" ]
then
export assemble_tgt="$assemble_tgt assembleRelease"
fi

# if "%RC_ANDROID_DEBUG_INSTALL%"=="1" ( .\gradlew uninstallDebug && .\gradlew installDebug )

echo "starting gradle build: $assemble_tgt"

./gradlew $assemble_tgt

# sdkmanager --sdk_root=%ANDROID_HOME% "platform-tools" "platforms;android-28" "build-tools;28.0.3" "system-images;android-28;google_apis;x86_64" "ndk;21.4.7075529"



cd "$PROJECT_DIR"

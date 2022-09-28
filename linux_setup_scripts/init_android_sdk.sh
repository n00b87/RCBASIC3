ANDROID_NDK_HOME=$ANDROID_HOME/ndk/21.4.7075529

PATH=$ANDROID_HOME/cmdline-tools/bin:$ANDROID_NDK_HOME:$JAVA_HOME/bin:$PATH

# making sure the tools for the target API are installed

RC_ANDROID_ARGS1="--sdk_root=$ANDROID_HOME"

DEFAULT_API_VERSION=28

API_VERSION=$1

MIN_API_VERSION=21

BUILD_TOOLS_VERSION=28

if [ -z "$API_VERSION" ]
then
API_VERSION=$DEFAULT_API_VERSION
fi

export API_VERSION=$( echo $API_VERSION | tr -d " ")
echo API_VERSION is set to "$API_VERSION"

current_dir="$PWD"
cd $ANDROID_HOME/cmdline-tools/bin
RC_BUILD_TOOLS_VERSION=$( ./sdkmanager --sdk_root=$ANDROID_HOME --list | grep build-tools | grep $API_VERSION | sort -r )
RC_BUILD_TOOLS_VERSION=$( echo $RC_BUILD_TOOLS_VERSION | cut -d' ' -f1 )
cd "$current_dir"

export RC_BUILD_TOOLS_VERSION=$RC_BUILD_TOOLS_VERSION

export SDK_REQUIREMENT=0

if [ ! -d $ANDROID_HOME/platform-tools ]
then
export RC_ANDROID_ARGS2="platform-tools"
export SDK_REQUIREMENT=1
fi

if [ ! -d $ANDROID_HOME/platforms/android-$API_VERSION ]
then
export RC_ANDROID_ARGS3="platforms;android-$API_VERSION"
export SDK_REQUIREMENT=1
fi

if [ ! -d $ANDROID_HOME/build-tools/$BUILD_TOOLS_VERSION ]
then
export RC_ANDROID_ARGS4="$RC_BUILD_TOOLS_VERSION"
export SDK_REQUIREMENT=1
fi

if [ ! -d $ANDROID_HOME/system-images/android-$API_VERSION/google_apis ]
then
export RC_ANDROID_ARGS5="system-images;android-$API_VERSION;google_apis;x86_64"
export SDK_REQUIREMENT=1
fi

if [ ! -d $ANDROID_NDK_HOME ]
then
export RC_ANDROID_ARGS6="ndk;21.4.7075529"
export SDK_REQUIREMENT=1
fi


# SDK_MANAGER
if [ "$SDK_REQUIREMENT" -eq "1" ]
then
echo "Performing initial setup for RCBasic Android Build Tool"
echo "Configuring SDK"
$ANDROID_HOME/cmdline-tools/bin/sdkmanager $RC_ANDROID_ARGS1 $RC_ANDROID_ARGS2 $RC_ANDROID_ARGS3 $RC_ANDROID_ARGS4 $RC_ANDROID_ARGS5 $RC_ANDROID_ARGS6
$ANDROID_HOME/cmdline-tools/bin/sdkmanager --sdk_root=$ANDROID_HOME --licenses
fi

echo "sdk.dir=$ANDROID_HOME" > $HOME/Programs/rcbasic/tools/dist/rcbasic_android/android-project/local.properties
echo "ndk.dir=$ANDROID_HOME/ndk/21.4.7075529" >> $HOME/Programs/rcbasic/tools/dist/rcbasic_android/android-project/local.properties

if [ $? -eq 0 ]
then
echo "Initial Setup is Complete"
fi

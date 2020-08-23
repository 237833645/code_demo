#!/bin/bash

#set -x
BRANCH_NAME=
#################################################################
BUILD_PROP=$(find out/ -name build.prop | sed -n '1p')
#################################################################

if [ $(find out/ -name build.prop | wc -l) -eq 0 ]; then
    echo "build.prop file not exist int out path, Check !!!!!!!!!!!!!!!!"
    exit 1
else
    if [ $(find out/ -name build.prop | wc -l) -gt 2 ]; then
        echo "Have more target out put, please select !!!!!!!!!!!!!!!!"
	exit 1
    else
    	PROJECT_CONFIG=$(find out/ -name build.prop | sed -n '1p' | awk -F '/' '{print $4}')
    fi
fi
#PROJECT_CONFIG=rlk8735m_6_tst
echo "PROJECT_CONFIG=$PROJECT_CONFIG"

#################################################################

CPU_NAME=$(grep 'ro.board.platform' $BUILD_PROP | awk -F '=' '{print $2}')
#CPU_NAME=8735P
echo "CPU_NAME=$CPU_NAME"

ANDROID_VER=$(grep 'ro.build.version.release' $BUILD_PROP | awk -F '=' '{print $2}')
#ANDROID_VER=8735P
echo "ANDROID_VER=$ANDROID_VER"

BUILD_TYPE=$(grep 'ro.build.type' $BUILD_PROP | awk -F '=' '{print $2}')
#BUILD_TYPE=eng
echo "BUILD_TYPE=$BUILD_TYPE"


BUILD_DATE=$(date -d @$(grep 'ro.build.date.utc' $BUILD_PROP | awk -F '=' '{print $2}') +%Y%m%d%H%M)
#DATE=$(date +%m-%d-%H-%M)
echo "BUILD_DATE=$BUILD_DATE"
#################################################################

if [ ! -f ../.git/HEAD ]; then
    if [ $(repo branch | grep '*' | awk '{print $2}') ]; then
        BRANCH_NAME=$(repo branch | grep '*' | awk '{print $2}')
    else
        echo "no branch"
        exit 1
    fi
else
    BRANCH_NAME=$(cat ../.git/HEAD | awk -F / '{print $3}')
fi
#################################################################
PROJECT_NAME=$BRANCH_NAME-$PROJECT_CONFIG-$ANDROID_VER-$(echo $BUILD_TYPE)
MODEM_PATH=./device/mediatek/$PROJECT_CONFIG/ProjectConfig.mk
MODEM_NAME=$(grep CUSTOM_MODEM $MODEM_PATH | awk -F = '{print $2}' | awk '{print $1}')
BRANCH_NAME=$(git branch | grep "*" | awk -F ' ' '{print $2}')
#################################################################

rm -r ./$PROJECT_NAME-$BUILD_DATE
mkdir ./$PROJECT_NAME-$BUILD_DATE
mkdir ./$PROJECT_NAME-$BUILD_DATE/BIN
mkdir ./$PROJECT_NAME-$BUILD_DATE/DB
mkdir ./$PROJECT_NAME-$BUILD_DATE/OTA

cp $(find ./out/target/product/$PROJECT_CONFIG/ -name '*_Android_scatter.txt') ./$PROJECT_NAME-$BUILD_DATE/BIN
cp $(find ./out/target/product/$PROJECT_CONFIG/ -maxdepth 1 -name '*.bin') ./$PROJECT_NAME-$BUILD_DATE/BIN
cp $(find ./out/target/product/$PROJECT_CONFIG/ -maxdepth 1 -name '*.img') ./$PROJECT_NAME-$BUILD_DATE/BIN

cp $(find ./out/target/product/$PROJECT_CONFIG/ -name APDB_*) ./$PROJECT_NAME-$BUILD_DATE/DB
rm $(find ./$PROJECT_NAME-$BUILD_DATE/DB/ -name APDB_*_ENUM)
cp $(find out/target/product/ -name BPL* | grep system) ./$PROJECT_NAME-$BUILD_DATE/DB

cp ./out/target/product/$PROJECT_CONFIG/obj/PACKAGING/target_files_intermediates/*.zip ./$PROJECT_NAME-$BUILD_DATE/OTA
cp ./out/target/product/$PROJECT_CONFIG/system/build.prop ./$PROJECT_NAME-$BUILD_DATE/OTA

echo $PROJECT_NAME-$BUILD_DATE

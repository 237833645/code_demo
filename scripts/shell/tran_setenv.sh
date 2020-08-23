#!/bin/bash
if [[ $1 = "" && $2 = "" ]]; then
echo "Usage:"
echo "source rlk_setenv.sh [project] <user or eng> "
echo "e.g:source rlk_setenv.sh H971_A user  --It Will configure user compile environment"
echo "e.g:source rlk_setenv.sh h971_A userdebug  --It Will configure userdebug compile environment"
echo "e.g:source rlk_setenv.sh H970_A       --It will configure eng compile environment default"
echo " "
fi

#add shenjiang.he AXQHWQY-628 17.05.12 (start)
if [ mtklog == "${3}" ]
then
    sed -i 's/false/true/g' device/mediatek/common/mtklog/mtklog-config-bsp-*.prop
fi

if [ mobilelog == "${4}" ]
then
    sed -i "s/com.mediatek.log.mobile.enabled = false/com.mediatek.log.mobile.enabled = true/g" device/mediatek/common/mtklog/mtklog-config-bsp-*.prop
    export RLK_TEST_VERSION="test_version"
fi
#add shenjiang.he AXQHWQY-628 17.05.12 (end)

VariName=$1

chmod a+x tran_projects/${VariName%_*}/$1/$1.sh

source ./tran_projects/${VariName%_*}/$1/$1.sh $1 $2
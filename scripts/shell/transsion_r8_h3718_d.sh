#!/bin/bash
echo "execute $1.sh"
projname=k37mv1_bsp
platname=mt6735
kernelver=kernel-3.18
VariName=$1


function rlk_env_check()
{
  local pathname=$1
  local verchk=$2
  local rlklog=$3

  if [ "${verchk}"x = "user"x ]; then
    if [ "${rlklog}"x = "mtklog"x ]; then
      echo "user build: enable mtklog function"
      sed -i "s/MTK_LOG_CUSTOMER_SUPPORT = .*/MTK_LOG_CUSTOMER_SUPPORT = yes/" rlk_projects/${pathname}/ProjectConfig.mk
      sed -i 's/false/true/g' device/mediatek/common/mtklog/mtklog-config-bsp-*.prop
    fi
  fi
}

function rlk_env_config()
{
  local pathname=$1
  local projname=$2
  local lowerplat=$(echo $3 | tr '[A-Z]' '[a-z]')
  local upperplat=$(echo $3 | tr '[a-z]' '[A-Z]')
  local mtkkernel=$4
#  echo bom name: ${pathname}
#  echo proj name: ${projname}
#  echo plat(U) name: ${upperplat}
#  echo plat(L) name: ${lowerplat}

  #customize memory start
  rm -f vendor/mediatek/proprietary/bootable/bootloader/preloader/custom/${projname}/inc/custom_MemoryDevice.h
#  rm -f vendor/mediatek/proprietary/bootable/bootloader/preloader/tools/emigen/${upperplat}/MemoryDeviceList_${upperplat}.xls
  rm -f device/mediatek/build/build/tools/ptgen/${upperplat}/partition_table_${upperplat}.xls
  cp -af tran_projects/${VariName%_*}/${pathname}/memory/custom_MemoryDevice.h vendor/mediatek/proprietary/bootable/bootloader/preloader/custom/${projname}/inc/custom_MemoryDevice.h
  cp -af tran_projects/${VariName%_*}/${pathname}/memory/MemoryDeviceList_MT6737M.xls vendor/mediatek/proprietary/bootable/bootloader/preloader/tools/emigen/${upperplat}/MemoryDeviceList_MT6737M.xls
  cp -af tran_projects/${VariName%_*}/${pathname}/memory/partition_table_MT6737M.xls device/mediatek/build/build/tools/ptgen/MT6737M/partition_table_MT6737M.xls
  #customize memory end

  #customize ProjectConfig start
  rm -f device/mediateksample/${projname}/ProjectConfig.mk
  cp -af tran_projects/${VariName%_*}/${pathname}/ProjectConfig.mk device/mediateksample/${projname}/ProjectConfig.mk
  #customize ProjectConfig end

  #customize pl config start
  rm -f vendor/mediatek/proprietary/bootable/bootloader/preloader/custom/${projname}/${projname}.mk
  rm -f vendor/mediatek/proprietary/bootable/bootloader/preloader/platform/${lowerplat}/default.mak
  cp -af tran_projects/${VariName%_*}/${pathname}/preloader/${projname}.mk vendor/mediatek/proprietary/bootable/bootloader/preloader/custom/${projname}/${projname}.mk
  cp -af tran_projects/${VariName%_*}/${pathname}/preloader/default.mak vendor/mediatek/proprietary/bootable/bootloader/preloader/platform/${lowerplat}/default.mak
  #customize pl config end

  #customize lk config start
  rm -f vendor/mediatek/proprietary/bootable/bootloader/lk/project/${projname}.mk
  cp -af tran_projects/${VariName%_*}/${pathname}/lk/${projname}.mk vendor/mediatek/proprietary/bootable/bootloader/lk/project/${projname}.mk
  #customize lk config end

  #customize kernel config start
  rm -f ${mtkkernel}/arch/arm64/configs/${projname}_debug_defconfig
  rm -f ${mtkkernel}/arch/arm64/configs/${projname}_defconfig
  cp -af tran_projects/${VariName%_*}/${pathname}/kernel/${projname}_debug_defconfig ${mtkkernel}/arch/arm/configs/${projname}_debug_defconfig
  cp -af tran_projects/${VariName%_*}/${pathname}/kernel/${projname}_defconfig ${mtkkernel}/arch/arm/configs/${projname}_defconfig
  #customize kernel config end

  #customize kernel dts start
  rm -f ${mtkkernel}/arch/arm/boot/dts/${projname}.dts
  #rm -f ${mtkkernel}/arch/arm/boot/dts/${lowerplat}.dtsi
  cp -af tran_projects/${VariName%_*}/${pathname}/dts/${projname}.dts ${mtkkernel}/arch/arm/boot/dts/${projname}.dts
  #cp -af tran_projects/${pathname}/dts/${lowerplat}.dtsi ${mtkkernel}/arch/arm/boot/dts/${lowerplat}.dtsi
  #customize kernel dts end

  #customize DWS start
  rm -f vendor/mediatek/proprietary/bootable/bootloader/preloader/custom/${projname}/dct/dct/codegen.dws
  rm -f vendor/mediatek/proprietary/bootable/bootloader/lk/target/${projname}/dct/dct/codegen.dws
  rm -f ${mtkkernel}/drivers/misc/mediatek/dws/${lowerplat}/${projname}.dws
  cp -af tran_projects/${VariName%_*}/${pathname}/dws/pl_lk/codegen.dws vendor/mediatek/proprietary/bootable/bootloader/preloader/custom/${projname}/dct/dct/codegen.dws
  cp -af tran_projects/${VariName%_*}/${pathname}/dws/pl_lk/codegen.dws vendor/mediatek/proprietary/bootable/bootloader/lk/target/${projname}/dct/dct/codegen.dws
  # cp -af rlk_projects/${pathname}/dws/${projname}.dws ${mtkkernel}/drivers/misc/mediatek/dws/${lowerplat}/${projname}.dws
  # cp -af rlk_projects/${pathname}/dws/kernel/codegen.dws ${mtkkernel}/drivers/misc/mediatek/dws/${lowerplat}/${projname}.dws
  cp -af tran_projects/${VariName%_*}/${pathname}/dws/kernel/codegen.dws ${mtkkernel}/drivers/misc/mediatek/dws/mt6735/k37mv1_bsp.dws
  #customize DWS end

  #customize audio start
#  cp -f rlk_projects/${VariName%_*}/${pathname}/audio/tfa98xx.cnt   device/mediatek/common/smartpa_params/tfa98xx.cnt
#  cp -f rlk_projects/${VariName%_*}/${pathname}/audio/audio_param_smartpa/*   device/mediatek/common/audio_param_smartpa/
#  cp -f rlk_projects/${pathname}/audio/param/default.audio_param   device/reallytek/rlk6797_5m_n/
#  cp -f rlk_projects/${pathname}/audio/Audio_Customization_Common.h   vendor/mediatek/proprietary/custom/rlk6797_5m_n/hal/audioflinger/audio/
#  cp -f rlk_projects/${pathname}/audio/audio_policy_configuration.xml device/mediatek/mt6797/audio_policy_config/
  #customize audio end
  
  ##android go config
  rm -f device/mediateksample/${projname}/device.mk
  cp -af tran_projects/${VariName%_*}/${pathname}/device.mk device/mediateksample/${projname}/device.mk 
  rm -f device/mediateksample/${projname}/BoardConfig.mk
  cp -af tran_projects/${VariName%_*}/${pathname}/BoardConfig.mk device/mediateksample/${projname}/BoardConfig.mk   
  rm -f device/mediateksample/${projname}/full_k37mv1_bsp.mk
  cp -af tran_projects/${VariName%_*}/${pathname}/full_k37mv1_bsp.mk device/mediateksample/${projname}/full_k37mv1_bsp.mk     
  
}

function rlk_custap_config()
{
  #add shenjiang.he AXQHWQY-601 17.05.12 (start)
  cp -rf tran_projects/$1/$2 device/mediateksample/
  cp tran_projects/$1/buildinfo.sh build/tools/buildinfo.sh
  cp tran_projects/$1/custom.conf device/mediatek/common/custom.conf
  #add shenjiang.he AXQHWQY-601 17.05.12 (end)

  #add AXQHWQY-75 by wenlin.xiao for APN start
  rm device/mediatek/common/apns-conf.xml
  rm device/mediatek/common/spn-conf.xml
  rm frameworks/opt/telephony/src/java/com/android/internal/telephony/gsm/UtilAPN.java
  rm vendor/mediatek/proprietary/frameworks/base/telephony/etc/virtual-spn-conf-by-efspn.xml
  cp packages/apps/TecnoApn/apns-conf.xml device/mediatek/common/apns-conf.xml
  cp packages/apps/TecnoApn/spn-conf.xml device/mediatek/common/spn-conf.xml
  cp packages/apps/TecnoApn/UtilAPN.java frameworks/opt/telephony/src/java/com/android/internal/telephony/gsm/UtilAPN.java
  cp packages/apps/TecnoApn/virtual-spn-conf-by-efspn.xml vendor/mediatek/proprietary/frameworks/base/telephony/etc/virtual-spn-conf-by-efspn.xml
  #add AXQHWQY-75 by wenlin.xiao for APN end

  #add by pengpeng.liang 20170412 start
  cp -rf vendor/Tecnon_BuildIn/sounds/tecno/AllAudio.mk frameworks/base/data/sounds
  #add by pengpeng.liang 20170412 end
}

rlk_env_config $1 ${projname} ${platname} ${kernelver}
# rlk_custap_config $1 ${projname}


# setting build env;
echo $1
echo $2
if [[ $2 = "user" ]] ; then
  echo "user version setting start ---"
  echo "build/envsetup.sh"
  source build/envsetup.sh
  echo "source mbldenv.sh"
  source mbldenv.sh
  echo "lunch full_${projname}-user"
  lunch full_${projname}-user
elif [[ $2 = "userdebug" ]] ; then
  echo "userdebug version setting start ---"
  echo "build/envsetup.sh"
  source build/envsetup.sh
  echo "source mbldenv.sh"
  source mbldenv.sh
  echo "lunch full_${projname}-userdebug"
  lunch full_${projname}-userdebug
else
  echo "eng version setting start ---"
  echo "build/envsetup.sh"
  source build/envsetup.sh
  echo "source mbldenv.sh"
  source mbldenv.sh
  echo "lunch full_${projname}-eng"
  lunch full_${projname}-eng
fi

echo
echo
echo "========================================================================"
echo "The compile environment is setup,"
echo "Please Input the follow command to compile whole Android"
echo "make -j24 2>&1 | tee build.log"
echo "========================================================================"
echo
echo


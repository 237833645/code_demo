#/bin/sh

###############################################################
# how to user:
# ./copy_target_bin.sh temp_dir
# You will found it in "RLK_TATGET_DIR"
#
###############################################################

# fixme: how to get TARGET_PROJECT name
# echo "Target product = $TARGET_PRODUCT"

RLK_TARGET_PRODUCT=${TARGET_PRODUCT#*_}
OUT_PATH=out/target/product
M_DATE=`date +%Y%m%d_%H_%M`
# RLK_TARGET_DIR=~/share/$1
RLK_TARGET_DIR=$OUT_PATH/${RLK_TARGET_PRODUCT}_${M_DATE}

# mkdir target dir
if [ ! -d $RLK_TARGET_DIR ];then
    mkdir $RLK_TARGET_DIR
else
    rm $RLK_TARGET_DIR/ -rf
fi

# fixme: get two database files for SN_tool
function get_datebase()
{
    mkdir ~/Desktop -p
    cd out/target/product/$RLK_TARGET_PRODUCT/obj/ETC/BPLGUInfoCustomAppSrcP* 
    cp BPLGUInfoCustomAppSrcP* ~/Desktop/
    cd - > /dev/null
    mv ~/Desktop/BPLGUInfoCustomAppSrcP* $RLK_TARGET_DIR/

    cd out/target/product/$RLK_TARGET_PRODUCT/obj/CGEN/ 
    ls APDB* > temp.txt
    cp `sed -n '1,1p' temp.txt` ~/Desktop/
    rm temp.txt
    cd - > /dev/null
    mv ~/Desktop/APDB*  $RLK_TARGET_DIR/
}

function get_version()
{
    cp $OUT_PATH/$RLK_TARGET_PRODUCT/*.img $RLK_TARGET_DIR/ -arv
    cp $OUT_PATH/$RLK_TARGET_PRODUCT/appsboot.mbn $RLK_TARGET_DIR/ -arv
    cp $OUT_PATH/$RLK_TARGET_PRODUCT/appsboot.raw $RLK_TARGET_DIR/ -arv
    cp $OUT_PATH/$RLK_TARGET_PRODUCT/lk.bin $RLK_TARGET_DIR/ -arv
    cp $OUT_PATH/$RLK_TARGET_PRODUCT/logo.bin $RLK_TARGET_DIR/ -arv
    cp $OUT_PATH/$RLK_TARGET_PRODUCT/MT*_Android_scatter.txt  $RLK_TARGET_DIR/ -arv
    cp $OUT_PATH/$RLK_TARGET_PRODUCT/preloader_$RLK_TARGET_PRODUCT.bin $RLK_TARGET_DIR/ -arv
    cp $OUT_PATH/$RLK_TARGET_PRODUCT/trustzone.bin $RLK_TARGET_DIR/ -arv
}

function main()
{
    get_version
    get_datebase
}

#run main
# ================================
main
# ================================

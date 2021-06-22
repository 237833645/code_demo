# Android c/c++动态库使用

## 使用动态库的目的（略）

### 编译出一个动态库文件 .so

- 新建一个命名库目录dynamic_lib，内部新建好.c .h Android.mk文件
- 编写相关函数逻辑实现
- 将dynamic_lib目录拷贝到extern下，使用mmm编译出动态库
- 编译生成的so库如下
  >out/target/product/h900_1g/system/lib/dynamic_lib.so

### 在其他程序代码中导入动态库内部函数

- 新建call_dynamic_lib，内部新建好call_dynamic.c Android.mk文件
- 拷贝编译出的动态库文件 dynamic_lib.so 放到需要调用程序的call_dynamic_lib目录下
- call_dynamic_lib/Android.mk编写加入动态库的功能
- call_dynamic_lib/call_dynamic.c文件调用库函数功能
- 将call_dynamic_lib目录拷贝到extern下，使用mmm编译出可执行文件
  >[100% 6/6] Install: out/target/product/h900_1g/system/bin/call_dynamic

### 执行

- CANNOT LINK EXECUTABLE "./call_dynamic_demo": library "dynamic_lib.so" not found
  >需要拷贝编译生成的system/bin/call_dynamic 和 system/lib/dynamic_lib.so到对应设备

安装上面的验证得出结论：
> LOCAL_LDFLAGS := $(LOCAL_PATH)/lib/dynamic_lib.so
> 和  LOCAL_SHARED_LIBRARIES := dynamic_lib.so 执行的结果是一致的
> 都依赖/system/lib/dynamic_lib.so 这个文件

### 删除库源文件dynamic_lib.c

### *使用动态库so文件放在自定义文件夹下是没有意义的*

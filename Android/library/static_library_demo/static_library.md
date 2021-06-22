# Android c/c++静态库使用

## 使用静态库的目的（略）

### 编译出一个静态库文件.a

- 新建一个命名库目录static_lib，内部新建好.c .h Android.mk文件
- 编写相关函数逻辑实现
- 将static_lib目录拷贝到extern下，使用mmm编译出静态库

### 在其他程序代码中导入静态库内部函数

- 新建call_static_lib，内部新建好call_static.c Android.mk文件
- 拷贝编译出的静态库文件 static_lib.a 放到需要调用程序的call_static_lib目录下
- call_static_lib/Android.mk编写加入静态库的功能
- call_static_lib/call_static.c文件调用库函数功能
- 将call_static_lib目录拷贝到extern下，使用mmm编译出可执行文件
  >[100% 6/6] Install: out/target/product/h900_1g/system/bin/call_static

### 删除库源文件static_lib.c

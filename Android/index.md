# Android代码Demo

## [Android makefile介绍](./makefile.md)

## Android源码工程库编译及库函数使用

    call_dynamic.c和call_static.c分别是调用动\静态库里面函数的主程序  
    static_lib和dynamic_lib两个目录就是分别需要编译出来的库

- [Android c/c++ 静态库使用介绍](library/static_library_demo/static_library.md)
- [Android c/c++ 动态库使用介绍](library/dynamic_library_demo/dynamic_library.md)

## Linux内核导入目标文件.o_shipped

有些外部模块编译需要二级制文件，kbuild编译系统支持这种需求，但是二进制文件命名为特定模式：_shipped。当编译时，编译系统会把_shipped去掉。
obj-y   :=  gpio_ctrl.o  (目录下面是gpio_ctrl.o_shipped)

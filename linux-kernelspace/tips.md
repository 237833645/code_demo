# 内核子系统学习

- insmod内核模块报错“module verification failed: signature and/or required key missing - tainting kernel”

  有两种方式解决：

  > 在当前linux 系统的kernel源码下修改config文件，CONFIG_MODULE_SIG=n  
  > 在驱动的Makefile文件里面添加这行CONFIG_MODULE_SIG=n

- 
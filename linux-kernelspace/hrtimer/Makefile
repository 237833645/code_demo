obj-m := hrtimer.o
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	@make clean
clean:
	rm -rf .*.ko.cmd *.mod *.mod.c .*.mod.cmd *.mod.o .*.mod.o.cmd *.o .*.o.cmd modules.order Module.symvers
.PYONY: modules clean
 

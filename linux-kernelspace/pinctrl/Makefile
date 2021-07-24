obj-m := gpio_request_one.o gpio_request_array.o gpiochip_find.o
KERNELDIR ?= /lib/modules/$(shell uname -r)/build
PWD := $(shell pwd)
modules:
	$(MAKE) -C $(KERNELDIR) M=$(PWD) modules
	@make clean
clean:
	rm -rf .*.ko.cmd *.mod *.mod.c .*.mod.cmd *.mod.o .*.mod.o.cmd *.o .*.o.cmd modules.order Module.symvers .tmp_versions .cache.mk
.PYONY: modules clean
 

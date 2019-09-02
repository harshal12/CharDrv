obj-m:=chdrv_interface.o


KDIR=/lib/modules/$(shell uname -r)/build

all : 
	$(MAKE) -C $(KDIR) M=$(PWD) modules 

clean:
	sudo rm *.ko *.order *.o *.mod.c *.symvers




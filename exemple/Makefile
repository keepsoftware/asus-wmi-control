obj-m += ite5570.o

all:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean


obj-m += ite5570.o
KDIR := /lib/modules/`uname -r`/build
PWD := $(shell pwd)
CC = gcc

all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C /lib/modules/$(shell uname -r)/build M=$(PWD) clean
    #rm -rf *.o *~ core .depend .*.cmd *.mod.* *.ko *.symvers

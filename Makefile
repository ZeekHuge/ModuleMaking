#
# Makefile for ModuleMaking
#

obj-m += Hello.o
obj-m += getGPIO.o
obj-m += exposeCharDev.o
	

KDIR ?= /lib/modules/$(shell uname -r)/build


all:
	make -C $(KDIR) M=$(PWD) modules

clean:
	make -C $(KDIR) M=$(PWD) clean
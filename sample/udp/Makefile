# 
# ksocket project
# BSD-style socket APIs for kernel 2.6 developers
# 
# @2007-2008, China
# @song.xian-guang@hotmail.com (MSN Accounts)
# 
# This code is licenced under the GPL
# Feel free to contact me if any questions
# @2017
# Hardik Bagdi (hbagdi1@binghamton.edu)
# Changes for Compatibility with Linux 4.9 to use iov_iter
# 

.PHONY: default clean

obj-m := ksocket_udp_srv_demo.o ksocket_udp_cli_demo.o
#ksocket_tcp_srv-objs := ../ksocket.o
KDIR  := /lib/modules/$(shell uname -r)/build
PWD   := $(shell pwd)

EXTRA_LDFLAGS := -I../../src

ifeq ($(ADDRSAFE),true)
	EXTRA_CFLAGS += -DKSOCKET_ADDR_SAFE
endif

default:
	$(MAKE) -C $(KDIR) M=$(PWD) modules

clean:
	rm -rf *.ko *.o *.mod.* .H* .tm* .*cmd Module.symvers modules.order


# ksocket API  

BSD-style socket API in kernel space for TCP/IP networking.
Original ksocket for v2.6 was published at [http://ksocket.sourceforge.net/](http://ksocket.sourceforge.net/).
This repository contains changes to make it compatible with new kernel versions.
The ksocket API has been updated to incorporate the changes related to the [iov_iter](https://lwn.net/Articles/625077/) interface introduced in kernel v3.19+.

### Getting started
```
$ git clone https://github.com/hbagdi/ksocket.git
$ cd ksocket/src
$ make # make sure you have the kernel headers/tree installed
$ sudo insmod ksocket.ko
#now you can use the exported symbols from this kernel module
```

### Sample
Look at `sample` sub-directory for code-samples.
```
$ cd ksocket/sample/tcp/
$ make
# two kernel modules are ksocket_tcp_cli_demo.ko(TCP client) and ksocket_tcp_srv_demo.ko(TCP server)
$ sudo ksocket_tcp_srv_demo.ko
$ sudo ksocket_tcp_cli_demo.ko
$ dmesg
```

### Support across kernel versions
The original ksocket work was to support Linux 2.6, however support for v5.4.0 has been
included.

v5.4.0 support is a work on Linux ubuntu 5.4.0-66 x86-64, therefore there is no guarantee it works
well on versions > 2.6 && < 5.3.x

In order to keep the 2.6 version stable it was left without the 5.4.0 work,
instead we now have two branches: v2.6 (master) and v5.4.0

#### v2.6 original development
https://github.com/hbagdi/ksocket

#### v5.4.0
https://github.com/hbagdi/ksocket/tree/linux-5.4.0

### Contributing/Reporting Bugs
- Feel free to open Pull-Requests here for any enhancements/fixes.
- Open an issue in the repository for any help or bugs. Make sure to mention Kernel version.

### Contact
Email at hardikbagdi@gmail.com for any further help.

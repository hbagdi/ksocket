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

### Contributing/Reporting Bugs
- Feel free to open Pull-Requests here for any enhancements/fixes.
- Open an issue in the repository for any help or bugs. Make sure to mention Kernel version.

### Contact
Email at hardikbagdi@gmail.com for any further help.

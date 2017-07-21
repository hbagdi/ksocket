/* 
 * ksocket project test sample - udp server
 * BSD-style socket APIs for kernel 2.6 developers
 * 
 * @2007-2008, China
 * @song.xian-guang@hotmail.com (MSN Accounts)
 * 
 * This code is licenced under the GPL
 * Feel free to contact me if any questions
 * 
 * @2017
 * Hardik Bagdi (hbagdi1@binghamton.edu)
 * Changes for Compatibility with Linux 4.9 to use iov_iter
 */
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/string.h>
#include <linux/kthread.h>
#include <linux/socket.h>
#include <linux/net.h>
#include <net/sock.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <linux/in.h>

#include "ksocket.h"

#define BUF_SIZE 100

static int port = 4444;
module_param(port, int, 0444);

int udp_srv(void *arg)
{
	ksocket_t sockfd_srv, sockfd_cli;
	struct sockaddr_in addr_srv;
	struct sockaddr_in addr_cli;
	char buf[BUF_SIZE];
	int addr_len, len;

#ifdef KSOCKET_ADDR_SAFE
		mm_segment_t old_fs;
		old_fs = get_fs();
		set_fs(KERNEL_DS);
#endif
	
	sockfd_srv = sockfd_cli = NULL;
	memset(&addr_cli, 0, sizeof(addr_cli));
	memset(&addr_srv, 0, sizeof(addr_srv));
	addr_srv.sin_family = AF_INET;
	addr_srv.sin_port = htons(port);
	addr_srv.sin_addr.s_addr = INADDR_ANY;
	addr_len = sizeof(struct sockaddr_in);
	
	sockfd_srv = ksocket(AF_INET, SOCK_DGRAM, 0);
	printk("sockfd_srv = 0x%p\n", sockfd_srv);
	if (sockfd_srv == NULL)
	{
		printk("socket failed\n");
		return -1;
	}
	if (kbind(sockfd_srv, (struct sockaddr *)&addr_srv, addr_len) < 0)
	{
		printk("bind failed\n");
		return -1;
	}
	
	while (1)
	{
		memset(buf, 0, sizeof(buf));
		len = krecvfrom(sockfd_srv, buf, sizeof(buf), 0,(struct sockaddr*)&addr_cli,&addr_len);
		if (len > 0)
		{
			printk("got message : %s\n", buf);
			ksendto(sockfd_srv, buf, len, 0,(struct sockaddr*)&addr_cli,addr_len);
			if (memcmp(buf, "quit", 4) == 0)
				break;
		}
	}

	kclose(sockfd_srv);
#ifdef KSOCKET_ADDR_SAFE
		set_fs(old_fs);
#endif
	
	return 0;
}

static int ksocket_udp_srv_init(void)
{
	kthread_run(udp_srv, NULL, "tcp_srv_kthread");
	
	printk("ksocket udp srv init ok\n");
	return 0;
}

static void ksocket_udp_srv_exit(void)
{
	printk("ksocket udp srv exit\n");
}

module_init(ksocket_udp_srv_init);
module_exit(ksocket_udp_srv_exit);

MODULE_LICENSE("Dual BSD/GPL");

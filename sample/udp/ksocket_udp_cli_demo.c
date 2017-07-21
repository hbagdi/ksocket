/* 
 * ksocket project test sample - udp client
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
#include <linux/socket.h>
#include <linux/kthread.h>
#include <linux/net.h>
#include <net/sock.h>
#include <asm/processor.h>
#include <asm/uaccess.h>
#include <linux/in.h>

#include "ksocket.h"

#define BUF_SIZE 100

int udp_cli(void *arg)
{
	ksocket_t sockfd_cli;
	struct sockaddr_in addr_srv;
	char buf[BUF_SIZE], *tmp;
	int addr_len;

#ifdef KSOCKET_ADDR_SAFE
	mm_segment_t old_fs;
	old_fs = get_fs();
	set_fs(KERNEL_DS);
#endif

	memset(&addr_srv, 0, sizeof(addr_srv));
	addr_srv.sin_family = AF_INET;
	addr_srv.sin_port = htons(4444);
	addr_srv.sin_addr.s_addr = inet_addr("127.0.0.1");;
	addr_len = sizeof(struct sockaddr_in);
	
	sockfd_cli = ksocket(AF_INET, SOCK_DGRAM, 0);
	printk("sockfd_cli = 0x%p\n", sockfd_cli);
	if (sockfd_cli == NULL)
	{
		printk("socket failed\n");
		return -1;
	}
	tmp = "quit";
	ksendto(sockfd_cli, tmp, 4, 0,(struct sockaddr*)&addr_srv, sizeof(addr_srv));
	krecvfrom(sockfd_cli, buf, 1024, 0,(struct sockaddr*)&addr_srv, &addr_len);
	printk("got message : %s\n", buf);
	kclose(sockfd_cli);
#ifdef KSOCKET_ADDR_SAFE
		set_fs(old_fs);
#endif
	
	return 0;
}

static int ksocket_udp_cli_init(void)
{
	kthread_run(udp_cli,NULL,"tcp_cli_kthread");
	printk("ksocket udp cli init ok\n");
	return 0;
}

static void ksocket_udp_cli_exit(void)
{
	printk("ksocket udp cli exit\n");
}

module_init(ksocket_udp_cli_init);
module_exit(ksocket_udp_cli_exit);

MODULE_LICENSE("Dual BSD/GPL");

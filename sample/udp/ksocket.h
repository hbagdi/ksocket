/* 
 * ksocket project
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
 * 
 */

#ifndef _ksocket_h_
#define _ksocket_h_

struct socket;
struct sockaddr;
struct in_addr;
typedef struct socket * ksocket_t;

/* BSD socket APIs prototype declaration */
extern ksocket_t ksocket(int domain, int type, int protocol);
extern int kshutdown(ksocket_t socket, int how);
extern int kclose(ksocket_t socket);

extern int kbind(ksocket_t socket, struct sockaddr *address, int address_len);
extern int klisten(ksocket_t socket, int backlog);
extern int kconnect(ksocket_t socket, struct sockaddr *address, int address_len);
extern ksocket_t kaccept(ksocket_t socket, struct sockaddr *address, int *address_len);

extern ssize_t krecv(ksocket_t socket, void *buffer, size_t length, int flags);
extern ssize_t ksend(ksocket_t socket, const void *buffer, size_t length, int flags);
extern ssize_t krecvfrom(ksocket_t socket, void * buffer, size_t length, int flags, struct sockaddr * address, int * address_len);
extern ssize_t ksendto(ksocket_t socket, void *message, size_t length, int flags, const struct sockaddr *dest_addr, int dest_len);

extern int kgetsockname(ksocket_t socket, struct sockaddr *address, int *address_len);
extern int kgetpeername(ksocket_t socket, struct sockaddr *address, int *address_len);
extern int ksetsockopt(ksocket_t socket, int level, int optname, void *optval, int optlen);
extern int kgetsockopt(ksocket_t socket, int level, int optname, void *optval, int *optlen);

extern unsigned int inet_addr(char* ip);
extern char *inet_ntoa(struct in_addr *in); /* DO NOT forget to kfree the return pointer */

#endif /* !_ksocket_h_ */

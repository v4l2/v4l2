#ifndef MYV4L2_H
#define MYV4L2_H

#include <sys/types.h>
#include <sys/socket.h>
#include <sys/ipc.h>
#include <sys/sem.h>

#define PORT      9999

union semun
{
	int val;
	struct semid_ds *buf;
	unsigned short *array;
};

static int set_semvalue(void);
static void del_semvalue(void);
int semaphore_p(void);
int semaphore_v(void);




//get ip v4_addr
struct ifconfig_addr
{
	char *v4_addr;
};

struct shared_sock
{
	int fd;
	struct sockaddr s_addr;
};

void create_save_socket();
int get_socket_fds(int *sockets, int *nums);

#endif

#ifndef MYV4L2_H
#define MYV4L2_H

#define PORT      9999

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

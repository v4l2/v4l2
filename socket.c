#include <sys/types.h>
#include <sys/socket.h>
#include <fcntl.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <netdb.h>
#include <sys/time.h>
#include <string.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>
#include "myv4l2.h"

#define ADDRSIZE    20
#define MAX_FDS     6
int v_socket(const char *host, int clientPort)
{
	int sock;
	unsigned long inaddr;
	struct sockaddr_in ad;
	struct hostent *hp;

	memset(&ad, 0, sizeof(ad));
	inaddr = inet_addr(host);

	ad.sin_family = AF_INET;
	ad.sin_port = htons(clientPort);
	if (inaddr != INADDR_NONE)
		memcpy(&ad.sin_addr, &inaddr, sizeof(inaddr));
	else
	{
		hp = gethostbyname(host);
		if (hp == NULL)
			return -1;
		memcpy(&ad.sin_addr, hp->h_addr, hp->h_length);
	}

	sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
		return -1;
	return sock;
}

int read(const char *path, struct ifconfig_addr *addr)
{
	int fd;
	char buf;
	fd = open(path, O_RDONLY);
	if (fd == -1)
	{
		return fd;
	}	
	addr->v4_addr =(char *) malloc(ADDRSIZE);
	bzero(addr->v4_addr, ADDRSIZE);
	while (1)
	{
		read(fd, &buf, 1);
		if (buf == '\n')
		{
			while (1)
			{
				read(fd, &buf, 1);
				if (buf == 'i')
					break;
			}
			break;
		}
	}
	while (1)
	{
		read(fd, &buf, 1);
		if (buf == ':')
		{
			while (1)
			{
				read(fd, &buf, 1);
				if (buf == ' ')
					break;
				strcat(addr->v4_addr, &buf);
			}
			break;
		}
	}

	close(fd);
	return 0;
}

void get_host_addr(char *host)
{
	struct ifconfig_addr *addr;
	int status;
	
	status = mkdir("0");
	if(status == 0)
		rmdir("./0");
	else 
	{
		perror("error:");
		free(host);
		exit(-1);
	}
	system("ifconfig > ifconfig.txt");
	addr = (ifconfig_addr)malloc(sizeof(struct ifconfig_addr));
	if(read_file("./ifconfig.txt", addr) != 0)
	{
		perror("error:");
		free(addr->v4_addr);
		free(addr);
		exit(-1);
	}
	
	host = addr->v4_addr;
	system("rm -rf ifconfig.txt");
	free(addr->v4_addr);
	free(addr);
}

void create_save_socket(void)
{
	fd_set fds; 
	
	struct shared_sock share_mem[MAX_FDS];
	int num;
	int sock;
	int maxfd;
	int fd;
	int i;
	//struct timeval tv;
	/* Timeout. */ 
	//struct timeval tv; 
	//tv.tv_sec = 2; 
	//tv.tv_usec = 0;

	char *host;

	shmid = shmget((key_t)1234, 6*sizeof(struct shared_sock), 0666);
	if(shmid == -1)
	{
		perror("shmet failed");
	}
	shm = shmat(shmid, 0, 0);
	if(shm == (void *)-1)
	{
		perror("shmat failed");	
	}
	printf("\nMemory attached at %x\n", (int)shm);
	shared = (struct shared_sock *)shm;
	
	//init share_mem;
	for(i = 0; i < MAX_FDS; i++)
		{
			share_mem[i].fd = -1;
			memset(&share_mem[i].s_addr, 0, sizeof(shared[i].s_addr));
		}

	host =(char *)malloc(ADDRSIZE);
	get_host_addr(host);	
	sock = v_socket(host, PORT);
	if (-1 == sock)
	{
		perror("error:");
		exit(-1);
	}
	maxfd = sock;
	memset(socks, -1, MAX_FDS);
	while (1)
	{
		//reflash sock_fd, and save it to share_mem_sock[]
 		//init shared mem
		semaphore_p();
		for(i = 0; i < MAX_FDS; i++)
		{
			shared[i].fd = share_mem[i].fd;
			memcpy(&shared[i].s_addr, &share_mem.s_addr);
		}
		semaphore_v();
		
		FD_ZERO (&fds);
		FD_SET(sock, &fds);
		for (i = 0; i < MAX_FDS; i++)
		{
			if (share_mem[i].fd != -1)
			{
				FD_SET(socks[i], &fds);
				maxfd = maxfd > share_mem[i].fd?maxfd:share_mem[i].fd;
			}
		}
		//wait
		r = select (maxfd + 1, &fds, NULL, NULL, NULL); 
		if (-1 == r) 
		{
			if (EINTR == errno) 
				continue; 
			//to do something
			exit (-1); 
		}
		if (FD_ISSET(sock, &fds))
		{
			fd = connect(sock, (struct sockaddr *)&ad, sizeof(ad));
			for(i = 0; i < MAX_FDS; i++)
			{
				if (share_mem[i].fd == -1)
				{
					share_mem[i].fd = fd;
					memcpy(&share_mem.s_addr, &ad);
				}
			}
	 	}
		//subtract fd
		for(i = 0; i < MAX_FDS;i++)
		{
			if ((share_mem[i].fd != -1) && (FD_ISSET(share_mem[i].fd, &fds)) && (recvfrom(share_mem[i].fd, buffer, 1024, 0, (struct sockaddr *)&ad, (socket_t *)&sock_len) == 0) )
			{
				share_mem[i].fd == -1;
				memset(&share_mem[i].s_addr, 0, sizeof(share_mem[i].s_addr));
			}
		}
	}
}

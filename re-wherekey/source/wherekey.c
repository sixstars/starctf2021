/*
 * test.c
 * Copyright (C) 2020 ctf <hailongeric@gmail.com>
 * flag{are_you_sure_friend}
 * A = [102, 108, 97, 103, 123, 97, 114, 101, 95, 121, 111, 117, 95, 115, 117, 114, 101, 95, 102, 114, 105, 101, 110, 100, 125]
 *A-1  =  [[ 70  15 190 134 147]
[157 121 210 213  51]
[124 136 223 180 128]
[ 48 173  34 141 143]
[224 162 208 100 112]]
 * *CTF{Ha23_f0n_9nd_G0od-1uck-OH}
 * [[72, 97, 50, 51, 95],[ 102, 48, 110, 95, 57], [110, 100, 95, 71, 48], [111, 100, 45, 49, 117], [99, 107, 45, 79, 72]]
 * [ 72  97  50  51  95]
[102  48 110  95  57]
[110 100  95  71  48]
[111 100  45  49 117]
[ 99 107  45  79  72]
 * flag*A=[ 56 109  75  75 185]
[138 249 138 187  92]
[138 154 186 107 210]
[198 187   5 144  86]
[147 230  18 189  79]
 * Distributed under terms of the MIT license.
 */

#include <sys/select.h>
#include <sys/epoll.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <fcntl.h>
#include <errno.h>
#include <signal.h>

#define JUNKCODE          \
	__asm__ __volatile__( \
		"jmp junk1\n\t"   \
		".byte 0x12\n\t" \
		" junk2 : \n\t"   \
		"ret \n\t"        \
		".byte 0x34\n\t" \
		"junk1 : \n\t"    \
		"call junk2\n\t");

#define JUNKCODE2 __asm__ __volatile__( \
	".byte 0x75\n\t"                    \
	".byte 0x2\n\t"                     \
	".byte 0xE9\n\t"                    \
	".byte 0xED\n\t");

#define JUNKCODE3          \
	__asm__ __volatile__( \
		"jmp junk3\n\t"   \
		".byte 0x22\n\t" \
		" junk4 : \n\t"   \
		"ret \n\t"        \
		".byte 0x44\n\t" \
		"junk3 : \n\t"    \
		"call junk4\n\t");

#define JUNKCODE4          \
	__asm__ __volatile__( \
		"jmp junk5\n\t"   \
		".byte 0x12\n\t" \
		" junk6 : \n\t"   \
		"ret \n\t"        \
		".byte 0x67\n\t" \
		"junk5 : \n\t"    \
		"call junk6\n\t");

#define IN 0
#define OUT 1
#define UDP_RECV_PORT 8888
#define UDP_SEND_PORT 8888
char UDP_SERVER_IP[] = {50, 49, 52, 45, 51, 45, 51, 45, 50, 3};

struct sockaddr_in server;
struct sockaddr_in local;
int input_size = 0;
int input_num = 0;
int finished = 666;
char buf[100];
char *TEMP_BUF = NULL;
char A[] = {102, 108, 97, 103, 123, 97, 114, 101, 95, 121, 111, 117, 95, 115, 117, 114, 101, 95, 102, 114, 105, 101, 110, 100, 125};

char B[25];
int q_num = 0;
int chanll = 1;
char raw[] = {5, 72, 67, 68, 5, 89, 94, 94, 83, 10, 88, 75, 93, 42}; //"/bin/stty raw"

int sock_fd_send;
int sock_fd_recv;
char cook[] = {5, 72, 67, 68, 5, 89, 94, 94, 83, 10, 73, 69, 69, 65, 79, 78, 42}; //"/bin/stty cooked"
int in_fd;
char AIM[] = {56, 109, 75, 75, 185, 138, 249, 138, 187, 92, 138, 154, 186, 107, 210, 198, 187, 5, 144, 86, 147, 230, 18, 189, 79};

char *encode(char *m);
void encode2(char *m);

char *encode(char *str)
{
	int l = strlen(str);
	char *ret = malloc(l);
	int i = 0;
	for (; i < l; i++)
	{
		ret[i] = str[i] ^ 42;
	}
	return ret;
}

char *hide(char *str)
{
	int l = strlen(str);
	char *ret = malloc(l);
	int i = 0;
	for (; i < l; i++)
	{
		ret[i] = str[i] ^ ((l / 3) & 0xff);
	}
	return ret;
}

int mul(char *dest, char *src, int len)
{
	int ret = 0;
	JUNKCODE2
	for (int i = 0; i < len; i++)
	{
		ret += dest[i] * src[i];
	}
	return ret;
}

char *hide2(char *str)
{
	int l = strlen(str);
	int i = 0;
	for (; i < l; i++)
	{
		JUNKCODE
		str[i] ^= (((l * 10) / 3) & 0xff);
	}
	return str;
}

void get_table(char *a, int n)
{
	int i = n;
	int j = 0;
	for (; i < 25; i += 5)
	{
		a[j++] = A[i];
	}
	JUNKCODE4
	return;
}

void quit()
{
	if (finished == 666 && chanll)
	{
		//char s[] = "Congratulations, please wrap your input with *CTF{} and submit it\n";
		char s[] = {159, 179, 178, 187, 174, 189, 168, 169, 176, 189, 168, 181, 179, 178, 175, 240, 252, 172, 176, 185, 189, 175, 185, 252, 171, 174, 189, 172, 252, 165, 179, 169, 174, 252, 181, 178, 172, 169, 168, 252, 171, 181, 168, 180, 252, 246, 159, 136, 154, 167, 161, 252, 189, 178, 184, 252, 175, 169, 190, 177, 181, 168, 252, 181, 168, 214, 0};
		write(STDOUT_FILENO, hide2(s), strlen(s));
	}
	exit(0);
}

void INPUT()
{
	int i = 0;
	char c;

	do
	{
		i = read(in_fd, &c, 1);
		if (c == '\n')
		{
			i = 0;
		}
		if (i < 0 && errno != EAGAIN)
		{
			exit(1);
		}
		if (i > 0)
		{
			buf[input_size] = c;
			input_size += i;
		}
		if (input_num > 4 && i > 0)
		{
			system(encode(cook));
			puts("why???");
			chanll = 0;
			return;
		}
		if (input_size >= 5 && input_num < 5)
		{
			input_num++;
			sendto(sock_fd_send, buf, 5, 0, (struct sockaddr *)&server, sizeof(server));
			int k = input_size;
			while (k > 5)
				buf[k - 6] = buf[--k];
			memset(buf + input_size - k, 0, input_size);
			input_size -= k;
		}

	} while (i);
	return;
}

void receive()
{
	int num = 0;
	char *str;
	int sin_size = sizeof(struct sockaddr_in);
	char *recv = malloc(10);
	memset(recv, 0, 10);
	num = recvfrom(sock_fd_recv, recv, 5, 0, (struct sockaddr *)&local, &sin_size);
	if (num > 0)
	{
		encode2(recv);
	}
}

void encode2(char *m)
{
	//JUNKCODE2
	if (TEMP_BUF == NULL)
	{
		TEMP_BUF = malloc(30);
	}
	strcat(TEMP_BUF, m);
	int l = strlen(TEMP_BUF);
	char a[5];
	if (l >= 5 * q_num)
	{
		for (int j = 0; j < 5; j++)
		{
			JUNKCODE3
			get_table(a, j);
			B[q_num * 5 + j] = (mul(TEMP_BUF + q_num * 5, a, 5) % 257) & 0xff;
		}
		q_num++;
	}

	if (q_num >= 5)
	{
		JUNKCODE2
		if (!memcmp(AIM, B, 25))
		{
			raise(SIGQUIT);
		}
	}
	return;
}

int init_send_fd()
{
	int sockfd = 0;
	int server_len = sizeof(struct sockaddr_in);
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		exit(0);
	}
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port = htons(UDP_SEND_PORT);
	server.sin_addr.s_addr = inet_addr(hide(UDP_SERVER_IP));
	return sockfd;
}

int inti_recv_fd()
{
	int sock = socket(AF_INET, SOCK_DGRAM, 0);
	if (sock < 0)
	{
		exit(1);
	}
	local.sin_family = AF_INET;
	local.sin_port = htons(UDP_RECV_PORT);
	local.sin_addr.s_addr = inet_addr(hide(UDP_SERVER_IP));
	if (bind(sock, (struct sockaddr *)&local, sizeof(local)) < 0)
	{
		exit(2);
	}
	return sock;
}

int init_in_fd()
{

	int fd = open("/dev/tty", O_RDONLY | O_NONBLOCK);
	if (fd < 0)
	{
		exit(1);
	}
	signal(SIGQUIT, quit);
	return fd;
}

int main()
{

	sock_fd_send = init_send_fd();
	sock_fd_recv = inti_recv_fd();
	in_fd = init_in_fd();

	puts("Please enter the key:");
	//JUNKCODE2
	while (1)
	{
		fd_set FDSet;
		FD_ZERO(&FDSet);
		FD_SET(in_fd, &FDSet);
		FD_SET(sock_fd_recv, &FDSet);
		select(FD_SETSIZE, &FDSet, NULL, NULL, NULL);
		JUNKCODE2
		if (FD_ISSET(sock_fd_recv, &FDSet))
			receive();
		if (FD_ISSET(in_fd, &FDSet))
		{
			//JUNKCODE2
			system(encode(raw));
			INPUT();
			system(encode(cook));
		}
	}
	return 0;
}
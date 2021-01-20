#### wherekey writeup 

```
A = [102, 108, 97, 103, 123, 97, 114, 101, 95, 121, 111, 117, 95, 115, 117, 114, 101, 95, 102, 114, 105, 101, 110, 100, 125] 5D
inverse(A)=  [[ 70  15 190 134 147]
              [157 121 210 213  51]
              [124 136 223 180 128]
              [ 48 173  34 141 143]
              [224 162 208 100 112]]

 flag*A=[ 56 109  75  75 185]
        [138 249 138 187  92]
        [138 154 186 107 210]
        [198 187   5 144  86]
        [147 230  18 189  79]

flag = flag*A*inverse(A)
```



source code:

```c
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

int main()
{

	sock_fd_send = init_send_fd();
	sock_fd_recv = inti_recv_fd();
	in_fd = init_in_fd();

	puts("Please enter the key:");
	while (1)
	{
		fd_set FDSet;
		FD_ZERO(&FDSet);
		FD_SET(in_fd, &FDSet);
		FD_SET(sock_fd_recv, &FDSet);
		select(FD_SETSIZE, &FDSet, NULL, NULL, NULL);
		if (FD_ISSET(sock_fd_recv, &FDSet))
			receive();
		if (FD_ISSET(in_fd, &FDSet))
		{
			system(encode(raw));
			INPUT();
			system(encode(cook));
		}
	}
	return 0;
}
```


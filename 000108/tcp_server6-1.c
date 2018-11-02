//client.c
#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<stdlib.h>
#include<netinet/in.h>
#include<arpa/inet.h>
int main(int argc, const char* argv[])
{
	if (argc != 5)
	{
		printf("Usgae:%s [ip] [port] [read byte] [write byte]\n", argv[0]);
		return 0;
	}

	//创建一个用来通讯的socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);
	if (sock < 0)
	{
		perror("socket");
		return 1;
	}

	//设置发送缓冲区大小
	/*int optVal=1024*3;
	setsockopt(sock,SOL_SOCKET,SO_SNDBUF,(const char*)&optVal,sizeof(int));*/

	//需要connect的是对端地址，因此这里定义服务器端的地址结构体
	struct sockaddr_in server;
	server.sin_family = AF_INET;
	server.sin_port = htons(atoi(argv[2]));
	server.sin_addr.s_addr = inet_addr(argv[1]);
	socklen_t len = sizeof(struct sockaddr_in);

	if (connect(sock, (struct sockaddr*)&server, len) < 0)
	{
		perror("connect");
		return 2;
	}
	//连接成功进行收数据
	char buf[1024];
	int count=0; //统计字节
	while (1)
	{
		/*printf("send###");
		fflush(stdout);*/

		//read
		ssize_t _s = read(sock, buf, atoi(argv[3]));
		if (_s > 0)
		{
			buf[_s] = 0;
			printf("server:%s", buf);
			count += _s;
			printf("total byte : %d", count);
		}
		else
		{
			printf("server is quit!\n");
			break;
		}
		//write
		int i=0;
		while(i < atoi(argv[4])){
			i+=10;
			write(sock,"aaaaaaaaaa", 10);
		}
	}
	close(sock);
	return 0;
}

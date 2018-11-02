//server.c
#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<unistd.h>
#include<netinet/in.h>
#include<arpa/inet.h>


//_port:端口  _ip:可使用的主机ip地址
int startup(int _port, const char *_ip)
{
	//创建socket
	int sock = socket(AF_INET, SOCK_STREAM, 0);

	//错误返回
	if (sock < 0)
	{
		perror("socket");
		exit(1);
	}

	int opt = 1;
	setsockopt(sock, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt));

	//以socket_in结构体填充socket信息
	struct sockaddr_in server_sockaddr;
	server_sockaddr.sin_family = AF_INET; //IPV4
	server_sockaddr.sin_port = htons(_port);
	server_sockaddr.sin_addr.s_addr = inet_addr(_ip);
	socklen_t len = sizeof(server_sockaddr);

	//bind绑定
	if (bind(sock,(struct sockaddr*)&server_sockaddr,len) < 0)
	{
		perror("bind");
		exit(2);
	}

	if (listen(sock, 5) < 0) //允许连接的最大数量为5
	{
		perror("listen");
		exit(3);
	}

	return sock;
}

int main(int argc, const char *argv[])
{
	if (argc != 2)
	{
		printf("Usage:%s [local_port]\n", argv[0]);
		return 1;
	}

	//初始化
	int listen_sock = startup(atoi(argv[1]), "192.168.80.230");

	//用来接收客户端的socket地址结构体
	struct sockaddr_in remote;
	socklen_t len = sizeof(struct sockaddr_in);

	while (1)
	{
		int sock = accept(listen_sock,(struct sockaddr*)&remote, &len);
		if (sock < 0)
		{
			perror("accept");
			continue;
		}

		//每次建立一个连接后fork出一个子进程进行收发数据
		pid_t pid = fork();
		if (pid > 0)
		{
			close(sock);
			while (waitpid(-1, NULL, WNOHANG) > 0);
		}
		else if (pid == 0)
		{
                        printf("get a client,ip:%s,port:%d\n",inet_ntoa(remote.sin_addr),ntohs(remote.sin_port));
			if (fork() > 0)
				exit(0);
			close(listen_sock);
			char buf[1024];
			while (1)
			{
				ssize_t _s = read(sock, buf, sizeof(buf) - 1);
				if (_s > 0)
				{
					buf[_s] = 0;
					printf("client:%s", buf);
				}
				else
				{
					printf("client is quit!\n");
					break;
				}
			}
		}
		else
		{
			perror("fork");
			return 2;
		}
	}
	return 0;
}

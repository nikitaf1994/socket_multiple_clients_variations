#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define SERVER_PATH   "./socket"

char message[] = "Hello from client!\n";
char buf[sizeof(message)];
//char buf[1024];
char mes[1024];

int main()
{
    	int sock;
	char mes[1024];
    	struct sockaddr_un server;

    	sock = socket(AF_UNIX, SOCK_STREAM, 0);

    	if(sock < 0)
    	{
        	perror("socket");
        	exit(1);
    	}

    	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, SERVER_PATH);

    	if(connect(sock, (struct sockaddr *)&server, sizeof(struct sockaddr_un)) < 0)
    	{
        	perror("connect");
        	exit(2);
    	}

	//while(ch!=KEY_F(3))
	while(1)
	{
		scanf("%s", &mes[0]);
    		send(sock, mes, sizeof(mes), 0);
		if(strcmp(mes, ":exit") == 0){
			close(sock);
			printf("Disconnected from server.\n");
			exit(1);
		}
		recv(sock, buf, 1024, 0);
		printf("%s",buf);
	}

    	return 0;
}

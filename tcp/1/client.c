#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

char message[] = "Hello from client!\n";
char buf[sizeof(message)];
//char buf[1024];
char mes[1024];

int main()
{
    	int sock;
	char mes[1024];
    	struct sockaddr_in addr;

    	sock = socket(AF_INET, SOCK_STREAM, 0);

    	if(sock < 0)
    	{
        	perror("socket");
        	exit(1);
    	}

    	addr.sin_family = AF_INET;
    	addr.sin_port = htons(3455);
    	addr.sin_addr.s_addr = htonl(INADDR_LOOPBACK);

    	if(connect(sock, (struct sockaddr *)&addr, sizeof(addr)) < 0)
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

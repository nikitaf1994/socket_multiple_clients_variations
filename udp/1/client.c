#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	char *msg = "Hello from client!\n";
	char mes[1024];
	int sock;
    	struct sockaddr_in addr;
	char buf[1024];
    	int bytes_read;
	int len;

    	sock = socket(AF_INET, SOCK_DGRAM, 0);

    	if(sock < 0)
    	{
        	perror("socket");
        	exit(1);
	}

    	addr.sin_family = AF_INET;
    	addr.sin_port = htons(3445);
    	addr.sin_addr.s_addr = INADDR_ANY;

	while(1)
	{
		scanf("%s", &mes[0]);
    		sendto(sock, (const char *)mes, strlen(mes), MSG_CONFIRM,(const struct sockaddr *) &addr, sizeof(addr));
		if(strcmp(mes, ":exit") == 0){
			close(sock);
			printf("Disconnected from server.\n");
			exit(1);
		}
		bytes_read=recvfrom(sock, (char *)buf, 1024, MSG_WAITALL,(struct sockaddr *) &addr, &len);
		buf[bytes_read] = '\0';
		printf("%s",buf);
	}
	close(sock);

    	return 0;
}

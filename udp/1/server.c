#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

int main()
{
	char *msg = "Server got the message!\n";
    	int sock;
    	struct sockaddr_in addr, cliaddr; 
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

    	if(bind(sock, (const struct sockaddr *) &addr, sizeof(addr)) < 0 )
    	{
        	perror("bind");
        	exit(2);
    	}
	while(1)
	{
	bytes_read=recvfrom(sock, (char *)buf, 1024, MSG_WAITALL, (struct sockaddr *) &cliaddr, &len);
	buf[bytes_read] = '\0';
	printf("%s\n",buf);
	sendto(sock, (const char *)msg, strlen(msg), MSG_CONFIRM, (const struct sockaddr *) &cliaddr, len);
	}
    	return 0;
}

#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

int main()
{
	int sock, listener;
    	struct sockaddr_in addr;
    	char buf[1024];
	char message[]="Server got message\n";
    	int bytes_read;
	pid_t childpid;

    	listener = socket(AF_INET, SOCK_STREAM, 0);

    	if(listener < 0)
    	{
        	perror("socket");
        	exit(1);
    	}

    	addr.sin_family = AF_INET;
    	addr.sin_port = htons(3455);
    	addr.sin_addr.s_addr = htonl(INADDR_ANY);
    	if(bind(listener, (struct sockaddr *)&addr, sizeof(addr)) < 0)
    	{
        	perror("bind");
        	exit(2);
    	}

    	listen(listener, 1);

    	while(1)
    	{
        	sock = accept(listener, NULL, NULL);

		if(sock < 0)
        	{
            		perror("accept");
            		exit(3);
        	}

		if((childpid = fork()) == 0)
		{
			while(1)
        		{
            			bytes_read = recv(sock, buf, 1024, 0);
            			if(bytes_read <= 0) exit(4);
				printf("%s\n", buf);
                		send(sock, message, sizeof(message), 0);
	       		}

        		close(sock);

		}
	}

	return 0;
}

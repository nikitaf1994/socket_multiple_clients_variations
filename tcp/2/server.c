#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#define ERROR_CREATE_THREAD -11
#define SERVER_PATH     "./socket"

int sock;
char buf[1024];
char message[]="Server got message\n";
int bytes_read;
int i=0;
pthread_mutex_t lock;


void *buying()
{
	printf("Created thread number %d\n", i);
	while(1)
        {
	//	pthread_mutex_lock(&lock);
        	bytes_read = recv(sock, buf, 1024, 0);
                if(bytes_read <= 0) exit(4);
                printf("%s\n", buf);
                send(sock, message, sizeof(message), 0);
	//	pthread_mutex_unlock(&lock);
        }
	
        close(sock);
	unlink(SERVER_PATH);
}

int main()
{
	int listener;
	//int i;
	pthread_t threads[2];
	int status;
    	struct sockaddr_un server;
    	listener = socket(AF_UNIX, SOCK_STREAM, 0);

    	if(listener < 0)
    	{
        	perror("socket");
        	exit(1);
    	}

	memset(&server, 0, sizeof(server));
	server.sun_family = AF_UNIX;
	strcpy(server.sun_path, SERVER_PATH);

	unlink(SERVER_PATH);
    	if(bind(listener, (struct sockaddr *)&server, SUN_LEN(&server)) <0)
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

//		for (; i < 3; i++)
		if(i<3)
                {
			i++;
                        status = pthread_create(&threads[i], NULL, buying, NULL);
		//	printf("Created thread number %d\n", i);
                        if (status != 0)
                        {
                                printf("main error: can't create thread, status = %d\n", status);
                                exit(ERROR_CREATE_THREAD);
                        }
                }else
		printf("no more threads");
        		//close(sock);


	}

	return 0;
}

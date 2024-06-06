#include <stdio.h>
#include <errno.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>
#include <unistd.h>
#include <ctype.h>
#include <stdlib.h>

#define PORT 8000
#define BUFFER_SIZE 1024

char* toLowerCase(char *str){
	int i=0;
	while(str[i]){
		str[i] = tolower(str[i]);
	}
}

int main(){
	//Size of the buffer that socket can read and store
	char buffer[BUFFER_SIZE];
	//Socket to establish connection
	//AF_INET - Used to specify address family(IPv4)
	//SOCK_STREAM - Connection type: TCP
	//0 - Defines default prototcol for SOCK_STREAM(TCP)
	int socketfd = socket(AF_INET,SOCK_STREAM,0);
	//socketfd - File descriptor containing status of socket
	if(socketfd==-1){
		perror("Websocket(socket)");
		return 1;
	}
	printf("Welcome to Bare Metal Chat\n");
	//Sockadd_in - Struct which contains address of host
	struct sockaddr_in host_addr;
	int host_addrlen = sizeof(host_addr);

	//3 components of sockaddr_in
	host_addr.sin_family = AF_INET;
	host_addr.sin_port = htons(PORT);
	//htons - Converts address from host byte order to network byte order
	//INADDR_ANY - Accept connection through all network interfaces
	host_addr.sin_addr.s_addr = htons(INADDR_ANY);

	//Binds socket with port
	//host_addrlen contains size of the buffer, to allocate right amount of memory for the address structure
	//16 in the case of our IPv4 connection
	if(bind(socketfd, (struct sockaddr *)&host_addr, host_addrlen)!=0){
		perror("Webserver(bind)");
		return 1;
	}

	//Listen to any incoming connections
	//SOMAXCONN - Mentions the maximum no of connections that can be stored in queue
	if(listen(socketfd,SOMAXCONN)!=0){
		perror("Webserver(listen)");
		return 1;
	}

	int acceptsocket = accept(socketfd,(struct sockaddr *)&host_addr,(socklen_t *)&host_addrlen);
		if(acceptsocket<0){
			perror("Webserver (accept)");
		}


	//Infinite loop for accepting new connections
	for(;;){
		//Specifies size of buffer that contains address structure of connecting client
		//Reads data
		int valread = read(acceptsocket,buffer,BUFFER_SIZE);
		buffer[valread]='\0';
		printf("\tClient message:%s\n",buffer);
		if(valread<0){
			perror("Webserver(read)");
			continue;
		}

		printf("Enter message\n");
		char* a = (char *)malloc(50*sizeof(char));
		fgets(a,50,stdin);
		a[strcspn(a,"\n")]=0;
		//Writes data on successful read - Response
		int valwrite = write(acceptsocket,a,strlen(a));
		if(valwrite<0){
			perror("Webserver(write)");
			free(a);
			continue;}
		free(a);
	}
	return 0;
}

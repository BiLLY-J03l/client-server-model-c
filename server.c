#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


int main(int argc, char **argv){
	
	
	if(argc == 1){
		printf("[x] please enter port number\ne.g. %s <port no.>\n",argv[0]);
		return 1;

	};

	//server hello msg
	char server_message[500]="[+] YOU ARE CONNECTED TO THE SERVER\n";
	
	//argv[1] ==> port
	
	int port_no=atoi(argv[1]);
	char server_ip[]="0.0.0.0";

	//create a socket
	//AF_INET ==> comms with ipv4
	//SOCK_STREAM ==> TCP
	//0 ==> 
	int server_socket=socket(AF_INET,SOCK_STREAM,0);

	//declare a pointer to sockaddr_in struct and allocate memory for it
	struct sockaddr_in *server_address = malloc(sizeof(struct sockaddr_in));

	server_address->sin_family=AF_INET;
	server_address->sin_port=htons(port_no); //htons ==> convert port no. to network byte order
	
	//inet_pton ==> convert ip addr from string to binary, st0oring it in sin_addr
	if(inet_pton(AF_INET,server_ip,&(server_address->sin_addr)) <= 0){
		printf("[x] unable to listen on 0.0.0.0\n[x]exiting...\n");
		return 1;
	}
	
	//binding process
	bind(server_socket,(struct sockaddr *)server_address,sizeof(*server_address));

	//listening for connections
	printf("[+] listening on port %d...\n",port_no);
	listen(server_socket, 10);
	

	//accepting connections
	int client_socket=accept(server_socket, NULL, NULL);
	printf("[+] connection received...\n");
		
	//sending msg
	printf("[+] sending hello message to client...\n");
	send(client_socket, server_message, sizeof(server_message),0);
	printf("[+] message sent...\n");
	
	//close connectiion
	printf("[+] closing connection...\n");
	close(server_socket);
	printf("[+] connection closed...\n");

	//free memory
	free(server_address);

	return 0;






}




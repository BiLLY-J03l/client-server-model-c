#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>



int main(void){

	//create a socket
	//AF_INET ==> comms with ipv4
	//SOCK_STREAM ==> TCP
	//0 ==> IP protocol
	int network_socket=socket(AF_INET,SOCK_STREAM,0);
	
	char server_address_input[100];
	int server_port;
	int *server_port_pointer=&server_port;
	
	printf("[+] enter server address: ");
	scanf("%s",server_address_input);
	
	printf("[+] enter server port: ");
	if ( (scanf("%d",server_port_pointer) < 1) || (*server_port_pointer < 1 || *server_port_pointer > 65535) ){
		printf("[x] invalid port number\n[x]exiting...\n");
		return 1;	
	
	};
	
	

	//declare a pointer to sockaddr_in struct and allocate memory for it
	struct sockaddr_in *server_address = malloc(sizeof(struct sockaddr_in));
	
	server_address->sin_family=AF_INET;
	server_address->sin_port=htons(*server_port_pointer); //htons ==> convert port no. to network byte order
	
	//inet_pton ==> convert ip addr from string to binary, storing it in sin_addr
	if(inet_pton(AF_INET,server_address_input,&(server_address->sin_addr)) <= 0){
		printf("[x] invalid address\n");
		return 1;	
	}; 
		
	//connect to server
	
	int CONN_STAT=connect(network_socket, (struct sockaddr *)server_address, sizeof(*server_address));
	
	//check for conn err
	
	if (CONN_STAT != 0){
		printf("[x] error connecting to server...\n");
		return 1;
	}
	
	
	//buffer to hold recieved data
	char server_response[500];
	//recieve data from server
	recv(network_socket,&server_response,sizeof(server_response),0);

	//show server's response
	
	printf("[+] server sent data\n%s",server_response);

	//close connection
	printf("[+] closing connection...\n");
	close(network_socket);
	printf("[+] connection closed...\n");

	//free memory
	free(server_address);
	return 0;
}


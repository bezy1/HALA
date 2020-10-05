#include "Headers/Reciever.h"
#include <stdio.h> #include <stdlib.h>
#include <string.h>
#ifdef _WIN32
#include <winsock.h>
FILE * Start
int Setup(int * sockfd){ WSAData wsaData; /* This Part is window stuiped things */
	if((WSAStartup(MAKEWORD(1,1), &wsaData)) != 0 ){
		fprintf(stderr,"WSAStartup Failed.:(\n");
		exit(1);
	}
	int sockfd2,status; /* Here i created a file descriptor and status for gai_strerrorinfo(status)); */
	struct addrinfo hints, * res;  
	struct sockaddr_storage address;
	memset(&(hints),0,sizeof hints); /* make sure that Hints is empty */
	hints.ai_family = AF_UNSPEC;    /* This is used to specify if it's a IPV4 or IPV6 but here we didn't specify*/
	hints.ai_socktype = SOCK_STREAM; /* This is used to Specify the socket type wether tcp or udp  SOCK_STREAM mean tcp */
	hints.ai_flags = AI_PASSIVE; /* Here the flags specify that we don't want to set an ip address */
	if(status = (getaddrinfo(NULL,"6776",&hints,&res)) != 0){ /* Getting the Info Needed to make our socket and connection */
		fprintf(stderr,"GetaddrFailed",gai_strerror(status)); /* In case getaddrinfo Failed We Print the error */
		exit(1);
	}
	if((*sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol)) < 0){ /* Creating a new socket using our information from the res struct. */
		perror("Failed To Create A Socket"); // Print what inside errorno 
		exit(1);
	}
	if((bind(*(sockfd),res->ai_addr,res->ai_addrlen)) < 0){ /* This Function will ensure that port is associated */
		perror("Failed To Bind"); // Print What inside errorno
		exit(1);
	}
	if((listen(sockfd,10)) < 0){
		perror("Failed To Listen for Incoming Connection"); // Print What inside errorno 
		exit(1);
	}
	if((sockfd2 = accept(sockfd,(struct sockaddr *)&address,&(sizeof(address)))) < 0){  /* Here Were We get the Remote Socket */
		perror("Sorry But We wouldn't Accept this"); // Print What inside errorno
		exit(1);
	}
	return sockfd2;
}
char * Recieve(int sockfd , int sockfd2){
	char * Buffer = malloc(1024 * sizeof(char)); /* This is the Buffer Where We are going to receive our Message */
	short int len; /* This where we will get the length of the message that we have recived */
	char * fMessage = "We Couldn't Receive Anything"; 
	len = recv(&(sockfd2) , Buffer , sizeof(Buffer), 0);  /* This Function Will Recvieve Messages From the Remote  */
	swtich(len){ /* This one Will check if the Message Was Recieved or not */
		case -1 : perror("Failed To Reiceve the message");
				  break;
		case 0 :  send(sockfd,fMessage,sizeof fMessage ,0);
				  break;
	}	
	return Buffer[1024];
}
#else
// This is linux Code 
#include <sys/socket.h> // for socket() and the other guys
#include <sys/types.h> // This is pid_t
#include <netdb.h> // addrinfo , get addrinfo , gai_strerrorinfo

int Setup(int * sockfd){
	int sockfd2,status; /* Here i created a file descriptor and status for gai_strerrorinfo(status)); */
	struct addrinfo hints, * res;  
	struct sockaddr_storage address;
	memset(&(hints),0,sizeof hints); /* make sure that Hints is empty */
	hints.ai_family = AF_UNSPEC;    /* This is used to specify if it's a IPV4 or IPV6 but here we didn't specify*/
	hints.ai_socktype = SOCK_STREAM; /* This is used to Specify the socket type wether tcp or udp  SOCK_STREAM mean tcp */ hints.ai_flags = AI_PASSIVE; /* Here the flags specify that we don't want to set an ip address */
	if(status = (getaddrinfo(NULL,"6776",&hints,&res)) != 0){ /* Getting the Info Needed to make our socket and connection */
		fprintf(stderr,"GetaddrFailed",gai_strerror(status)); /* In case getaddrinfo Failed We Print the error */
		exit(1);
	}
	if((*sockfd = socket(res->ai_family,res->ai_socktype,res->ai_protocol)) < 0){ /* Creating a new socket using our information from the res struct. */
		perror("Failed To Create A Socket"); // Print what inside errorno 
		exit(1);
	}
	if((bind(*(sockfd),res->ai_addr,res->ai_addrlen)) < 0){ /* This Function will ensure that port is associated */
		perror("Failed To Bind"); // Print What inside errorno
		exit(1);
	}
	if((listen(sockfd,10)) < 0){
		perror("Failed To Listen for Incoming Connection"); // Print What inside errorno 
	}
	if((sockfd2 = accept(sockfd,(struct sockaddr *)&address,&(sizeof(address)))) < 0){  /* Here Were We get the Remote Socket */
		perror("Sorry But We wouldn't Accept this"); // Print What inside errorno
		exit(1)
	}
	return sockfd2; /* Returning the Socket of the Remote */
}

char * Recieve(int sockfd , int sockfd2){
	char * Buffer = malloc(1024 * sizeof(char)); /* This is the Buffer Where We are going to receive our Message */
	short int len; /* This where we will get the length of the message that we have recived */
	char * fMessage = "We Couldn't Receive Anything"; 
	len = recv(&(sockfd2) , Buffer , sizeof(Buffer), 0);  /* This Function Will Recvieve Messages From the Remote  */
	swtich(len){ /* This one Will check if the Message Was Recieved or not */
		case -1 : perror("Failed To Reiceve the message");
				  break;
		case 0 :  send(sockfd,fMessage,sizeof fMessage ,0);
				  break;
	}	
	return Buffer;
}
int Kill(){
	char * path = getenv("PWD"); 
}
#endif

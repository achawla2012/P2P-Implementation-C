/* server setup */

#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include <arpa/inet.h>
#include<stdlib.h>
#include<netdb.h>
#include<string.h>
#include"cserver.h"
struct SPeer
{
        char PID[2];
        char PADDRESS[20];
        char PNUM[7];
}peers[10];

static int peerCount = 0;

int main(int argc, char *argv[])
{
        for(LoopI=0;LoopI<10;LoopI++)
              memset(peers[LoopI].PID,'\0',2);
        if ((serverFD = socket(AF_INET, SOCK_STREAM, 0))< 0)
            perror("Fail to open socket");

        bzero((char *) &serverAddr, sizeof(serverAddr));
        portNum = 9999;
        serverAddr.sin_family = AF_INET;
        serverAddr.sin_addr.s_addr = INADDR_ANY;
        serverAddr.sin_port = htons(portNum);
        if (bind(serverFD, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0)
            perror("Fail to bind");
  listen(serverFD,10);
	Length = sizeof(clientAddr);
	puts("Trying to connect with peers ....");
	while(1)
	{
	    FD_ZERO(&readfds);
	    FD_SET(serverFD, &readfds);
	    IsActive = select( 10 , &readfds , NULL , NULL , NULL);
	    if(IsActive < 0)
		printf("Error in Activity");

	    if (FD_ISSET(serverFD, &readfds)) 
	    {
        	if ((sockFD = accept(serverFD, (struct sockaddr *) &clientAddr, &Length)) < 0)
	           	    perror("Fail to accept");
		bzero(Message,500);
 	        read(sockFD, Message, 500);
		strtok_r(Message, ";", &breakage);   // breakage has remaining Message values in it i.e Message's right
		puts("Requested Peer Added to Network");
		strcpy(peers[peerCount].PID,breakage);
		strcpy(peers[peerCount].PNUM,Message);
		copy = (char *)inet_ntoa(clientAddr.sin_addr);		
		strcpy(peers[peerCount].PADDRESS, copy);
		if(peerCount == 0)
		{
		    bzero(Message,500);
		    strcpy(Message,"Connected to N/w");			
		    write(sockFD, Message, 30);
		}
		else
		{
		    bzero(Message, 500);
		    Rand_var = random()%10;
			// Select clients from server in random way.
		    while (peers[Rand_var].PID[0] == '\0' || Rand_var == peerCount) Rand_var = random()%10;
		    strcpy(Message, "0");strcat(Message, ",");strcat(Message, peers[Rand_var].PID);
		    strcat(Message, ",");strcat(Message, peers[Rand_var].PNUM);
		    strcat(Message, ",");strcat(Message, peers[Rand_var].PADDRESS);
		    write(sockFD, Message, 500);
		}
		peerCount++;
	    }           
	}
}

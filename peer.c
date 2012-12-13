#include<stdio.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<stdlib.h>
#include<netdb.h>
#include<string.h>
#include<unistd.h>
#include<dirent.h>
#include<errno.h>
#include<net/if.h>
#include<sys/ioctl.h>
#include<fcntl.h>
#include"peer.h"
void NextPeer();
int main(int argc, char *argv[]) {
  IsCheckFlag = 0;int op;
	LoopI = 0; while (LoopI < 3) {
		memset(peer[LoopI].PEERID, '\0', 2);LoopI++;
	}
	if (argc < 3) {
		perror("Wrong number of arguments given to peer\n");
		exit(1);
	}
	peerPort = atoi(argv[2]);
	copyArg[3] = NULL;
	PID = atoi(argv[3]);
	peerServerSock = socket(AF_INET, SOCK_STREAM, 0);
	if (peerServerSock < 0) {
		perror("Fail to open socket");
	}
	bzero((char *) &seraddr, sizeof(seraddr));
	PortNum = atoi(argv[1]);
	copyArg[1] = argv[1];
	seraddr.sin_family = AF_INET;
	seraddr.sin_addr.s_addr = INADDR_ANY;
	seraddr.sin_port = htons(peerPort);
	if (bind(peerServerSock, (struct sockaddr *) &seraddr, sizeof(seraddr)) < 0) {
		perror("fail to bind");
	}
	listen(peerServerSock, 10);
	LengthAddr = sizeof(clientaddr);
	FD_ZERO(&RDF);
	FD_SET(0, &RDF);
	FD_SET(peerServerSock, &RDF);
	PortNum = 9999;
	copyaddr.sin_addr.s_addr = INADDR_ANY;
	Ser_sock = socket(AF_INET, SOCK_STREAM, 0);
	if (Ser_sock < 0) {
		perror("fail to open socket");
	}
	server = gethostbyname(argv[1]);
	if (server == NULL) {
		perror("Fail to connect to a central server");
		exit(0);
	}
	bzero((char *) &seraddr, sizeof(seraddr));
	seraddr.sin_family = AF_INET;
	copyArg[2] = argv[2];
	bcopy((char *) server->h_addr, (char *) &seraddr.sin_addr.s_addr,
			server->h_length);
	seraddr.sin_port = htons(PortNum);

	if (connect(Ser_sock, (struct sockaddr *) &seraddr, sizeof(seraddr))
			< 0) {
		perror("Fail to connect");
	}
	bzero(Message, 500);strcpy(Message, argv[2]);
	copyArg[3] = argv[3];
	strcat(Message, ";");login = getlogin();strcat(Message, argv[3]);
	write(Ser_sock, Message, strlen(Message));strcpy(DirectoryPath,"//home//");
	strcat(DirectoryPath,login);bzero(Message, 500);
	read(Ser_sock, Message, 500);
	duplicateIP = strtok(Message, ",");
	peerUnique = strtok(NULL, ",");
	port = strtok(NULL, ",");
	InternetAdd = strtok(NULL, ",");
	if (duplicateIP[0] == '0') { 
		NextPeer(); // To call next nodes.
	}
	strcpy(DirectoryPath,argv[4]); //puts(DirectoryPath);puts("hello");
// *****************************************SHARED DIRECTORY PATH******************************************
	//strcpy(DirectoryPath,"//home//amar//Desktop//shared");puts("fullpath");puts(DirectoryPath);
//*********************************************************************************************************

	while (1) {
		bzero(Sec_msg,500);
		bzero(Message,500);
		memcpy(&TFS, &RDF, sizeof(fd_set));
		if(IsCheckFlag == 0)
		{
			puts("\n		        Select below choices \n ");
			puts("1. Quit peer Network             : Enter Quit/quit");
			puts("2. List Files on peer            : Enter List/list");
			puts("3. Find The File On The Network  : Enter get/Get <File>");
		}
		IsCheckFlag = 0;
		fflush(stdout);
		IsActive = select(10, &TFS, NULL, NULL, NULL);
		if (IsActive < 0) {
			printf("Error");
		}
		if (FD_ISSET(peerServerSock, &TFS)) {
			if ((ClientSockFD = accept(peerServerSock, (struct sockaddr *) &clientaddr, &LengthAddr)) < 0) {
				perror("fail to accept");
			}

			bzero(Message, 500);
			read(ClientSockFD, Message, 500);
			if(Message[0] == '$')
			{
				FileTransfer = strtok(TransferFile,";");IsPath = opendir (DirectoryPath);
				if (IsPath != NULL)
					{ present=0;
			  		while ((dirpoint = readdir (IsPath)) != NULL) {
						dirpoint->d_name[strlen(dirpoint->d_name)] = '\0';
						if(strcmp(dirpoint->d_name,FileTransfer)== 0) {present=1;break;}}
						closedir(IsPath);
						if(!present){
							puts("Copy file at:-");LoopA=1;strcpy(TargetPath,DirectoryPath);
							strcat(TargetPath,"//");strcat(TargetPath,FileTransfer); puts(TargetPath);
							FDESC= fopen(TargetPath,"w");
							if (FDESC) {
				    				while (Message[LoopA] != '\0') putc(Message[LoopA++],FDESC);
							    fclose(FDESC);
							}
						}
				}
			bzero(Message,500);
			}

			else{

			if (peerCount < 3) {
				FD_SET(ClientSockFD, &RDF);
				peer_accept[PeerAddedLoop] = ClientSockFD;PeerAddedLoop++;
				strtok_r(Message, ";", &breakage);
				strcpy(peer[peerCount].PEERID, breakage);
				strcpy(peer[peerCount].PeerPortNum, Message);
				duplicate = (char *) inet_ntoa(clientaddr.sin_addr);
				strcpy(peer[peerCount].PeerAddressIP, duplicate);
				peer[peerCount].actualPort = ntohs(clientaddr.sin_port);
				peerCount++;bzero(Message, 500);strcpy(Message, "Greeting");
				IsCheckFlag = 1;write(ClientSockFD, Message, 500);
			} else {
				bzero(Message, 500);Rand_Var = random() % 3;
				while (peer[Rand_Var].PEERID[0] == '\0') Rand_Var = random() % 3;
				strcpy(Message, "6"); strcat(Message, ",");
				strcat(Message, peer[Rand_Var].PEERID);strcat(Message, ",");
				strcat(Message, peer[Rand_Var].PeerPortNum);strcat(Message, ",");
				strcat(Message, peer[Rand_Var].PeerAddressIP);write(ClientSockFD, Message, 500);
			}
			bzero(Message, 500);puts("A Peer has joined");
			}
		}
		for (LoopI = 0; LoopI < PeerAddedLoop; LoopI++) {
			acceptSock = peer_accept[LoopI];
			bzero(Message,500);
			if (FD_ISSET( acceptSock , &TFS)) {
				bzero(Message,500);
				read(acceptSock, Message, 500);
				if (strlen(Message) == 0)
				{
					getpeername(acceptSock, (struct sockaddr*) &clientaddr, &LengthAddr);
					LoopI =0; while( LoopI< peerCount)
					{       // Disconnect peer
						if(peer[LoopI].actualPort == ntohs(clientaddr.sin_port))
						printf("Disconnect peer: InternetAdd %s \n",
							inet_ntoa(clientaddr.sin_addr));
						LoopI++;							
					}
					close(acceptSock);peerCount--;
					peer_accept[LoopI]--;FD_CLR(acceptSock, &RDF);
					IsCheckFlag = 1;
					LoopY =0; while(LoopY<3) 
					{		// refresh the position of Quited peer with NULL
						if(strcmp(inet_ntoa(clientaddr.sin_addr), peer[LoopY].PeerAddressIP)==0)
						{ 	memset(peer[LoopI].PEERID, '\0', 2);
							memset(peer[LoopI].PeerPortNum, '\0', 10);
							memset(peer[LoopI].PeerAddressIP, '\0', 30);
							break;
						}
						LoopY++;					
					}
				}
				else
				{
					strcpy(Sec_msg,Message);
					TransferFile2 = strtok(Sec_msg,";");AddressIP = strtok(NULL,";");PeerNumber=strtok(NULL,";");
					SharedPath = opendir (DirectoryPath);
					if (SharedPath != NULL)
					{
				  		while ((dirpoint = readdir (SharedPath)) != NULL) {
							dirpoint->d_name[strlen(dirpoint->d_name)] = '\0';
							if(strcmp(dirpoint->d_name,TransferFile2) == 0)
							{
								strcpy(Destination,"$");LoopD=strlen(Destination);
								printf("\nThe File -%s- on current peer\n", TransferFile2);
								IsPresent = 1;
								FDESC = fopen(TransferFile2, "r");
								if (FDESC) {
								    while ((acceptChar = getc(FDESC)) != EOF)
										Destination[LoopD++]=acceptChar;
								    Destination[LoopD]='\0';
								    fclose(FDESC);
								}
								break;
							}
						}
						if(IsPresent ==1){
						PeerSocket = socket(AF_INET, SOCK_STREAM, 0);
						Peer_hostent = gethostbyname(AddressIP);
						bzero((char *) &PeerAddr, sizeof(PeerAddr));
						PeerAddr.sin_family = AF_INET;
						bcopy((char *) Peer_hostent->h_addr, (char *) &PeerAddr.sin_addr.s_addr,
								Peer_hostent->h_length);
						PeerAddr.sin_port = htons(atoi(PeerNumber));
						if (connect(PeerSocket, (struct sockaddr *) &PeerAddr, sizeof(PeerAddr))
								< 0) {
							perror("Fail to connect");
						}
						write(PeerSocket, Destination, strlen(Destination));
						bzero(Destination,1500);
						}
						if(IsPresent == 0)
						{
							bzero(Message,strlen(Message));strcpy(Message,TransferFile2);
							strcat(Message,";");strcat(Message,AddressIP);
							strcat(Message,";");strcat(Message,PeerNumber);
							LoopB = 0; while(LoopB<3) 
							{
								LoopC = peer_accept[LoopB];
								if(LoopC>0 && LoopC != acceptSock)
									write(LoopC, Message, strlen(Message));
								LoopB++;
							}
						}

		 				closedir (SharedPath);
						IsPresent =0;
 					}
				}
			}
		}
		if (FD_ISSET(0, &TFS))
		{
			bzero(sms,100);
			// GET INPUT FROM THE CONSOLE
			fgets(sms, 100, stdin);
			if (sms[0] == 'L' || sms[0] =='l')
			{
					Varcount=0;
					SharedPath = opendir (DirectoryPath);
					if (SharedPath != NULL)
					{
				  		while ((dirpoint = readdir (SharedPath)) != NULL){
							if(strcmp(dirpoint->d_name, ".") && strcmp(dirpoint->d_name,".."))
		  							printf (" %s\n",dirpoint->d_name);}
		 				closedir (SharedPath);
					}
					else perror ("Shared directory is not set up right");
			}
			else if (sms[0] == 'g' || sms[0] =='G')  /// GET
			{
					IsPresent = 0;
					memset(TransferFile,0,50);SharedPath = opendir (DirectoryPath);
					memset(Message,0,500);strncpy(TransferFile, sms + 4, strlen(sms) - 4);
					TransferFile[strlen(TransferFile)-1] = '\0';
					if (SharedPath != NULL)
					{
				  		while ((dirpoint = readdir (SharedPath)) != NULL) {
							dirpoint->d_name[strlen(dirpoint->d_name)] = '\0';
							if(strcmp(dirpoint->d_name,TransferFile) == 0 )
							{
								printf("%s is on this peer\n", TransferFile);IsPresent = 1;
								break;
							}
						}
						if(IsPresent == 0)
						{
						       strcat(TransferFile,";");
						       struct ifreq ifreqs[20];
					               struct ifconf ic;
		  				       ic.ifc_len = sizeof ifreqs;
					               ic.ifc_req = ifreqs;
                				       int tempSock;
               					       if ((tempSock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
									perror("Error in creating socketsocket");
									exit(1);
					    				}
	               				       if (ioctl(tempSock, SIOCGIFCONF, &ic) < 0) {
						                        perror("Fail to cntl function SIOCGIFCONF");
						                        exit(1);}
 					  	       for (op = 0; op < ic.ifc_len / sizeof(struct ifreq); ++op)
						       		if (!strcmp(ifreqs[op].ifr_name, "eth0")) {
						      	snprintf(IPmessage, 500, "%s",inet_ntoa(
								    ((struct sockaddr_in*) &ifreqs[op].ifr_addr)->sin_addr));}
							strcat(TransferFile,IPmessage);  
							strcat(TransferFile,";"); 
							strcat(TransferFile,argv[2]);
							for(LoopB = 0; LoopB< 3; LoopB++)
							{
								LoopC = peer_accept[LoopB];
								if(LoopC>0)
									write(LoopC, TransferFile, strlen(TransferFile));
							}
						}
		 				closedir (SharedPath);
 					}
					else perror ("Shared path is not present");
			}
			else if (sms[0] == 'Q' || sms[0] =='q')  //QUIT
			{
					printf("Leaving the peer network\n");exit(0);
			}
			else puts("In-correct input");continue;
		}
	}
}

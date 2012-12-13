fd_set RDF, TFS;
static int IsCheckFlag;
static int peerCount = 0;
int peerServerSock, IsPresent,LoopI, acceptSock, acceptChar, ClientSockFD, PortNum, LengthAddr,LoopY, IsActive, Rand_Var, Ser_sock, PID, LoopD,peerPort, peer_accept[3], Varcount, PeerSocket, LoopA, LoopB, present, LoopC;
char *copyArg[3],IPmessage[500];
DIR *SharedPath, *IsPath;
char DirectoryPath[500], TargetPath[500], Destination[1500],TransferFile[50],Message[500], Sec_msg[500], sms[100];
char *login, *TransferFile2, *FileTransfer,  * duplicate, *duplicateIP, *peerUnique, *port, *InternetAdd, *Temporary, *breakage,*AddressIP, *PeerNumber;
FILE *FDESC;
struct dirent *dirpoint;
struct sockaddr_in seraddr, clientaddr, copyaddr, PeerAddr;
struct hostent *server, *Peer_hostent;
int PeerAddedLoop = 0;

struct Peer {
  char PEERID[2];
	int actualPort;
	char PeerAddressIP[30];
	char PeerPortNum[10];
} peer[3];
void NextPeer() {
	int connectsock;
	struct hostent *dup_server;
	if ((connectsock = socket(AF_INET, SOCK_STREAM, 0))< 0) {
		perror("Fail to connect socket");
	}
	dup_server = server;
	dup_server = gethostbyname(InternetAdd);
	bzero((char *) &seraddr, sizeof(seraddr));
	bcopy((char *) dup_server->h_addr, (char *) &seraddr.sin_addr.s_addr,dup_server->h_length);
	seraddr.sin_port = htons(atoi(port));
	seraddr.sin_family = AF_INET;
	if (connect(connectsock, (struct sockaddr *) &seraddr, sizeof(seraddr))< 0) {
		perror("Fail to connect");
	}
	bzero(Message, 500);strcpy(Message,copyArg[2]);strcat(Message, ";");
	strcat(Message, copyArg[3]);write(connectsock, Message, strlen(Message));
	bzero(Message, 500);read(connectsock, Message, 500);Temporary = strtok(Message, ",");
	if (Temporary[0] == '6') {
		peerUnique = strtok(NULL, ",");
		port = strtok(NULL, ",");
		InternetAdd = strtok(NULL, ",");
		NextPeer();
	}
	else {
		FD_SET(connectsock, &RDF);
		strcpy(peer[peerCount].PEERID, peerUnique);
		strcpy(peer[peerCount].PeerAddressIP, InternetAdd);
		strcpy(peer[peerCount].PeerPortNum, port);
		peer[peerCount].actualPort = ntohs(clientaddr.sin_port);
		peerCount ++;
		peer_accept[PeerAddedLoop]=connectsock;
		PeerAddedLoop++;
	}
}

        int serverFD,LoopI, sockFD, portNum, Length, IsActive, Rand_var;
        struct sockaddr_in serverAddr, clientAddr;
        char Message[500], *breakage; char * copy;
	fd_set readfds;

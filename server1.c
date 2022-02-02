#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main(){
    //1. creat a socket for the server
    int serverSocketFD = socket(AF_INET, SOCK_STREAM, 0);
    if(serverSocketFD != -1)
    {
        printf("server Socket ID is : %d\n",serverSocketFD);
    }
    else 
    {
        printf("failed to create a socket \n");
        exit(1);
    }

    //2. bind the socket to a specific port number
    struct sockaddr_in serverAddress;
    memset(&serverAddress, 0, sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY);
    int port = 4444;
    serverAddress.sin_port = htons(port);

    if(bind(serverSocketFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == 0)
    {
        printf("server is binded to port %d\n",port);
    }
    else 
    {
        printf("binding failed \n");
        exit(1);
    }

    //3. listen to the clients connection requests
    if(listen(serverSocketFD, 1) == 0)
    {
        printf("listenning..........\n");
    }
    else
    {
        printf("failed to listen\n");
        exit(1);
    }

    //4. accept the connection request 
    struct sockaddr_in connectedClientAddress;
    memset(&connectedClientAddress, 0, sizeof(connectedClientAddress));

    int clientAddressLength = 0;
    int connectionServerSockFD = accept(serverSocketFD, (struct sockaddr*)&connectedClientAddress, &clientAddressLength);

    if(connectionServerSockFD == -1)
    {
        printf("failed to accept a connection \n");
    }
    else 
    {
        printf("accept a request at socket ID ; %d\n",connectionServerSockFD);
    }

    //5. send or receive data from the client 
    char receivedMsg[1024];
    memset(receivedMsg, 0, sizeof(receivedMsg));

    recv(connectionServerSockFD, receivedMsg, 1024 ,0);
    printf("received message : %s\n", receivedMsg);

    //6. close the socket 
    close(serverSocketFD);
    close(connectionServerSockFD);


    return 0;
}
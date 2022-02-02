#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <unistd.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/in.h>
#include <arpa/inet.h>

int main() {
    //1. create a socket for the client
    int clientSockFD = socket(AF_INET, SOCK_STREAM, 0); 
    if( clientSockFD != 0 )
    {
        printf("client socket id is : %d\n",clientSockFD);
    }
    else 
    {
        printf("Failed to create a socket \n"); 
        exit(1);
    }
    //2. connect the client tio a specific server 
    struct sockaddr_in serverAddress;
    memset(&serverAddress,0,sizeof(serverAddress));

    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr("127.0.0.1");
    serverAddress.sin_port = htons(4444);

    if(connect(clientSockFD, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) == 0)
    {
        printf("connected successfully \n");
    }
    else 
    {
        printf("failed to connect \n");
        exit(1);
    }
    //3. send data to the server
    char buffer[] = "hello i'm mohamed salah mouihbi\n" ;
    send(clientSockFD, buffer, strlen(buffer), 0);
    //4. close our socket
    close(clientSockFD);
    printf("client socket has been closed\n"); 

    return 0;
}
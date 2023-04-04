#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

void error(const char *msg) {
    perror(msg);
    exit(1); // 1 is the status which indicates that the code terminated with errors
}

int main(int argc, char *argv[]) {
    if (argc < 2) { //in this case there will be two command line arguments i.e, file name and port number
        fprintf(stderr, "Port number not provided.\n");
        exit(1); //exits with an error
    }

    int sockfd, newsockfd, portno, n;
    char buffer[256];

    struct sockaddr_in server_addr, client_addr; // making objects of sockaddr_in structures which will store client and server's socket address
    socklen_t clientlen; // socklen_t is a 32-bit data type from sys/types.h


////socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // creating socket
    if (sockfd < 0) {
        error("error opening the socket"); // any negative value of sockfd represents error of errors
    }

    bzero((char *) & server_addr, sizeof(server_addr)); // this basically clears any data ANY DATA that is there in its arguments
    // ye (char *) & server_addr ka kya matlab?

    portno = atoi(argv[1]);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(portno); //host to network short
    //until now we have not set the values for server_addr we have just set a boilerplate for it. bind() functioin will set values
    //bind() will ser the port value and the ip address on which the server will be hearing.
    //which is why it inputs the pointer to the stucture object.

////bind
    if (bind(sockfd, (struct sockaddr*) & server_addr, sizeof(server_addr)) < 0) { //binding the server
        error("binding failed");
    }

////listen
    listen(sockfd, 5);
    //this means the server will be waiting for max 5 clients at a time

    clientlen = sizeof(client_addr);

    newsockfd = accept(sockfd, (struct sockaddr *) &client_addr, &clientlen);
    //here we set the address for the client
    if (newsockfd < 0)
    error("error accepting connection");

    while(1) {
        bzero(buffer, 256);
        n = read(newsockfd, buffer, 256);
        if (n < 0) {
            error("reading failed");
        }
        int i = strncmp("Bye", buffer, 3);
        if (i == 0) break;
        printf("Client: %s\n", buffer);

        bzero(buffer, 256);
        fgets(buffer, 256, stdin);
        n = write(newsockfd, buffer, strlen(buffer));
        if (n < 0) printf("error writing");
        
        i = strncmp("Bye", buffer, 3);
        if (i == 0) break;
    }

    close(newsockfd);
    close(sockfd);
    return 0;

    // read about functions used on the highest priority tomorrow.
}

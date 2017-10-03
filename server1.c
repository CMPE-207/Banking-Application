#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

int main(int argc, char *argv[])
{

    int sockfd, newsockfd, portno, clilen, buffer, n;
    struct sockaddr_in serv_addr, cli_addr;
    int address_len = sizeof(serv_addr);

    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd == -1)
    {
        printf("Error calling Socket");
        exit(1);
    }

    bzero((char *) &serv_addr, sizeof(serv_addr));

    portno = atoi(argv[1]);
    printf("\nPort number received from command line is %d\n ",portno);

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    serv_addr.sin_port = htons(portno);

    if(bind(sockfd, (struct sockaddr *) &serv_addr,sizeof(serv_addr)) < 0)
    {
        printf("error binding");
        exit(1);
    }

    if(listen(sockfd,5) < 0)
    {
        printf("error listening");
        exit(1);
    }

    newsockfd = accept(sockfd,(struct sockaddr *) &serv_addr, (socklen_t*)&address_len);
    buffer = 0;
    n = read(newsockfd,&buffer,sizeof(int));
    if (n == -1)
    {
        printf("error reading");
        exit(1);
    }

    printf("Here is the numeric: %d\n",buffer);
    buffer = buffer - 1;
    printf("%d sent to the client", buffer);

    n = write(newsockfd,&buffer,sizeof(int));
    return 0;
}

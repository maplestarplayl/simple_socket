#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#define PORT 8000
/* Creator:LiFeng
   1.Creating socket file descriptior
*  2.Set socket FD's option OPTNAME at protocol level(not necessary)
*  3.Forcefully attaching socket to the port 8000 by using Bind
*  4.Listen
*  5.Accept the connect from the Client
*  6.Read and write
*/
int main(int argc, char *argv[])
{
    int socket_fd, new_socket_fd, numread;
    struct sockaddr_in address;
    char buffer[1024];
    // char *sendsentence = "Hello client";

    // 1.Create the socket file descriptor and exit if fails
    socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        perror("socket create failed");
        exit(1); // fail exit
    }

    // Intialize the memory
    memset(&address, '0', sizeof(address));

    address.sin_family = AF_INET;         // Use IP Protocol
    address.sin_addr.s_addr = INADDR_ANY; // Internet Address
    address.sin_port = htons(PORT);       // port

    // 3.Attaching socket to the port 8000
    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(1);
    }
    if (listen(socket_fd, 5) < 0)
    {
        perror("listen failed");
        exit(1);
    }
    if ((new_socket_fd = accept(socket_fd, NULL, NULL)) == -1)
    {
        perror("accept failed");
        exit(1);
    }
    printf("Connect to the client successfully\n");
    while (1)
    {
        // Get input from the cmd
        printf("Please input the message you want to sent:");
        fgets(buffer, sizeof(buffer), stdin);

        buffer[strcspn(buffer, "\n")] = '\0';
        // Send the meg to the client
        if (send(new_socket_fd, buffer, strlen(buffer), 0) == -1)
        {
            perror("Send msg failed");
            exit(1);
        }
        memset(&buffer, '\0', sizeof(buffer));
        numread = read(new_socket_fd, buffer, 1024);
        if (numread == -1)
        {
            perror("Read msg failed");
            exit(1);
        }
        printf("%s\n", buffer);
        memset(&buffer, '\0', sizeof(buffer));
        // send(new_socket_fd, sendsentence,     strlen(sendsentence), 0);
        // printf("Hello message sent\n");
    }
    // closing the connected socket
    close(new_socket_fd);
    close(socket_fd);
}
#include <arpa/inet.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdlib.h>
#define PORT 8000

/* Creator:LiFeng
   1.Creating socket file descriptior
*  2.Convert IPv4 and IPv6 addresses from text to binary
*  3.Connect
*  4.Send data
*  5.Read data
*/
int main(int argc, char *argv[])
{
    int socket_fd, numread;
    struct sockaddr_in address;
    char *sendsentence = "Hello server";
    char buffer[1024];
    // 1.Creating socket file descriptior
    if ((socket_fd = socket(AF_INET, SOCK_STREAM, 0)) < 0)
    {
        perror("Socket create failed");
        exit(1);
    }
    // set the memory to 0
    memset(&address, '0', sizeof(address));
    // Intialize the socket address
    address.sin_family = AF_INET;
    address.sin_port = htons(PORT);

    // 2.Convert IPv4 and IPv6 addresses from text to binary
    if (inet_pton(AF_INET, "127.0.0.1", &address.sin_addr) <= 0)
    {
        perror("Invalid address");
        exit(1);
    }
    // 3.Connect
    if (connect(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("Connect failed");
        exit(1);
    }
    // 4.Send data
    if (send(socket_fd, sendsentence, strlen(sendsentence), 0) == -1)
    {
        perror("Send failed");
        exit(1);
    }
    // 5.Read data
    numread = read(socket_fd, buffer, 1024);
    if (numread == -1 || numread == 0)
    {
        perror("Read failed");
        exit(1);
    }
    printf("%s\n", buffer);
    close(socket_fd);
    return 0;
}
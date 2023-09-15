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
#define BUFFER_SIZE 1024
void closeSocket(int socket_fd);
int *initSocket(); // return the new socket_fd(client)
void handleCommunication(int new_socket_fd, char *buffer);
void sendMessage(int socket_fd, char *message);
void receiveMessage(int socket_fd, char *buffer, int buffer_size);

int *initSocket()
{
    int socket_fd, new_socket_fd;
    int *socketArr = malloc(sizeof(int) * 2);
    struct sockaddr_in address;
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
    socketArr[0] = socket_fd;
    socketArr[1] = new_socket_fd;
    return socketArr;
}
int main(int argc, char *argv[])
{
    int socket_fd, new_socket_fd;
    new_socket_fd = initSocket()[1];
    printf("Connected to the client successfully\n");

    char buffer[] = "hi";
    handleCommunication(new_socket_fd, buffer);

    close(new_socket_fd);
    return 0;
}

void closeSocket(int socket_fd)
{
    close(socket_fd);
}
void handleCommunication(int new_socket_fd, char *buffer)
{
    // printf("Please input the message you want to send: ");
    // fgets(buffer, sizeof(buffer), stdin);
    buffer[strcspn(buffer, "\n")] = '\0';
    // Put the buffer(String) into an array
    sendMessage(new_socket_fd, buffer);
    receiveMessage(new_socket_fd, buffer, sizeof(buffer));
    printf("Received message: %s\n", buffer);
}

void sendMessage(int socket_fd, char *message)
{
    if (send(socket_fd, message, strlen(message), 0) == -1)
    {
        perror("Send message failed");
        exit(1);
    }
}

void receiveMessage(int socket_fd, char *buffer, int buffer_size)
{
    int numread = read(socket_fd, buffer, buffer_size);
    if (numread == -1)
    {
        perror("Read message failed");
        exit(1);
    }
}
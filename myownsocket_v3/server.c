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

int createSocket();
void bindSocket(int socket_fd);
void startListening(int socket_fd);
int acceptConnection(int socket_fd);
void handleCommunication(int new_socket_fd);
void sendMessage(int socket_fd, const char *message);
void receiveMessage(int socket_fd, char *buffer, int buffer_size);

int main(int argc, char *argv[])
{
    int socket_fd, new_socket_fd;

    socket_fd = createSocket();
    bindSocket(socket_fd);
    startListening(socket_fd);

    new_socket_fd = acceptConnection(socket_fd);
    printf("Connected to the client successfully\n");

    handleCommunication(new_socket_fd);

    close(new_socket_fd);
    close(socket_fd);

    return 0;
}

int createSocket()
{
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    if (socket_fd == -1)
    {
        perror("socket create failed");
        exit(1);
    }
    return socket_fd;
}

void bindSocket(int socket_fd)
{
    struct sockaddr_in address;
    memset(&address, '0', sizeof(address));

    address.sin_family = AF_INET;
    address.sin_addr.s_addr = INADDR_ANY;
    address.sin_port = htons(PORT);

    if (bind(socket_fd, (struct sockaddr *)&address, sizeof(address)) < 0)
    {
        perror("bind failed");
        exit(1);
    }
}

void startListening(int socket_fd)
{
    if (listen(socket_fd, 5) < 0)
    {
        perror("listen failed");
        exit(1);
    }
}

int acceptConnection(int socket_fd)
{
    int new_socket_fd = accept(socket_fd, NULL, NULL);
    if (new_socket_fd == -1)
    {
        perror("accept failed");
        exit(1);
    }
    return new_socket_fd;
}

void handleCommunication(int new_socket_fd)
{
    char buffer[BUFFER_SIZE];

    while (1)
    {
        printf("Please input the message you want to send: ");
        fgets(buffer, sizeof(buffer), stdin);
        buffer[strcspn(buffer, "\n")] = '\0';
        // Put the buffer(String) into an array
        sendMessage(new_socket_fd, buffer);
        receiveMessage(new_socket_fd, buffer, sizeof(buffer));

        printf("Received message: %s\n", buffer);
        memset(buffer, '\0', sizeof(buffer));
    }
}

void sendMessage(int socket_fd, const char *message)
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
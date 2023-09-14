# server.pyx
cdef extern from "server.c":
    int main(int argc, char *argv[])
    int initSocket()
    char *handleCommunication(int new_socket_fd,char *buffer)



#Main func: start the socket and wait for the msg to send and receive the msg
#Maybe multithread???

def handleCommunication(int new_socket_fd, bytes buffer):
    cdef char *c_buffer = buffer
    return handleCommunication(new_socket_fd, c_buffer)
#Fun1:create,bind,listen,accept socket
def init_socket():
    return initSocket()  #return the new socket_fd(client)
#Func2: Start the communication and get the msg 

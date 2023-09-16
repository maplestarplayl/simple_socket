# server.pyx
from cpython.bytes cimport PyBytes_FromStringAndSize
from cpython.bytes cimport PyBytes_AsString
from libc.stdlib cimport free
from libc.string cimport strcpy, strlen
cdef extern from "server.c":
    int* initSocket()
    void handleCommunication(int new_socket_fd,char *buffer)
    void closeSocket(int socket_fd)

def close_socket(int socket_fd):
    print("i'm closing socket")
    return closeSocket(socket_fd)
#Main func: start the socket and wait for the msg to send and receive the msg
#Maybe multithread???
#return the msg sent by the client
def handle_communication(int new_socket_fd, bytes buffer):
    cdef char *c_buffer = PyBytes_AsString(buffer)
    handleCommunication(new_socket_fd, c_buffer)
    cdef size_t result_len = strlen(c_buffer)
    py_buffer = PyBytes_FromStringAndSize(c_buffer,result_len)
    return py_buffer
#Fun1:create,bind,listen,accept socket
def init_socket():
    cdef int* socketArr = initSocket()
    py_socket_arr = []
    py_socket_arr.append(socketArr[0])
    py_socket_arr.append(socketArr[1])
    print("Linking Start")
    return  py_socket_arr
#Func2: Start the communication and get the msg 

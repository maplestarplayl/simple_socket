# server.pyx
cdef extern from "server.c":
    int main(int argc, char *argv[])

def server_main():
    cdef char *args[1]
    args[0] = b"server"  
    return main(1, args)
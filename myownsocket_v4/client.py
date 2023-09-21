import socket
import time
server = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
server.connect(('172.17.0.2', 8888))
request = None

try:
    while request != 'quit':
        request = "sdasss"
        time.sleep(2)
        if request:
            server.send(request.encode('utf8'))
            response = server.recv(255).decode('utf8')
            print(response)
except KeyboardInterrupt:
    server.close()

# import asyncio
import asyncio
import socket
# async def handle_client(reader, writer):
#     request = None
#     while request != 'quit':
#         request = (await reader.read(255)).decode('utf8')
#         print(f"Received {request!r}")
#         response = input("Input what you want to send as server")
#         writer.write(response.encode('utf8'))
#         await writer.drain()
#     writer.close()


# async def run_server():
#     server = await asyncio.start_server(handle_client, '127.0.0.1', 8888)
#     async with server:
#         await server.serve_forever()

def initialize_server():
    server_socket = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    server_socket.bind(('127.0.0.1', 8888))
    server_socket.listen(1)
    print('Server is running on 127.0.0.1:8888')
    conn, addr = server_socket.accept()
    print(f'The connect from {addr} has been established')
    return conn


def send_msg(conn, msg):
    conn.send(msg.encode('utf-8'))


async def read_msg(conn):
    request = await (conn.recv(255).decode('utf8'))
    return request

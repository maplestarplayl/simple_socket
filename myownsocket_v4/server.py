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
    server_socket.listen()
    print('Server is running on 127.0.0.1:8888')
    conn, addr = server_socket.accept()
    print(f'The connect from {addr} has been established')
    return conn


async def send_msg(conn, msg="123"):
    asyncio.sleep(3)
    conn.send(msg.encode('utf-8'))
    print(f"You send msg {msg}")


async def read_msg(conn):
    request = await (conn.recv(255).decode('utf8'))
    # return request
    print(f"You get msg {request}")


async def main():
    conn = initialize_server()
    asyncio.gather(send_msg(conn), read_msg(conn))

asyncio.run(main())

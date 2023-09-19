import asyncio


async def client(ip_addr):
    # 连接服务器

    reader, writer = await asyncio.open_connection(
        ip_addr, 8888)

    # 发送消息给服务器
    message = "Hello from the client!"
    writer.write(message.encode())
    await writer.drain()

    # 从服务器接收响应
    data = await reader.read(100)
    response = data.decode()
    print(f"Received from server: {response}")

    # 关闭连接
    writer.close()
    await writer.wait_closed()

ip_addr = input("Please specify the ip of the server")
asyncio.run(client(ip_addr))

import asyncio


async def client():
    # 连接服务器
    reader, writer = await asyncio.open_connection(
        '127.0.0.1', 8888)
    # await asyncio.sleep(5)
    # 发送消息给服务器
    while True:
        message = input("Input the msg you want send as client")
        writer.write(message.encode())
        await writer.drain()

    # 从服务器接收响应
        data = await reader.read(100)
        response = data.decode()
        print(f"Received from server: {response}")

    # 关闭连接
    writer.close()
    await writer.wait_closed()

# ip_addr = input("Please specify the ip of the server")
asyncio.run(client())

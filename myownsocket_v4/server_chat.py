import PySimpleGUI as sg
import asyncio
import server

"""
Purpose : Run the sever so that server could send msg while recv client's msg
How to Archieve : 
Current Diff :
    1.handle_client func : The send,recv operation must be processed inside it
    (Asyncio.gather() may be useful)
"""


# async def run_server():
#     server = await asyncio.start_server(handle_client, '127.0.0.1', 8888)
#     async with server:
#         await server.serve_forever()


# async def handle_client(reader, writer):
#     async def read_request():
#         nonlocal request
#         request = (await reader.read(255)).decode('utf8')
#         print(f"Received {request!r}")

#     async def send_response():
#         response = await consumer(asyncio.Queue())
#         writer.write(response.encode('utf8'))
#         print(f"Sent msg : {response}")
#         await writer.drain()

# request = None
# while request != 'quit':
#     await asyncio.gather(read_request(), send_response())
# writer.close()


sg.theme('GreenTan')  # give our window a spiffy set of colors

layout = [[sg.Text('Your output will go here', size=(40, 1))],
          [sg.Output(size=(110, 20), font=('Helvetica 10'))],
          [sg.Multiline(size=(70, 5), enter_submits=False, key='-QUERY-', do_not_clear=False),
           sg.Button('SEND', button_color=(
               sg.YELLOWS[0], sg.BLUES[0]), bind_return_key=True),
           sg.Button('EXIT', button_color=(sg.YELLOWS[0], sg.GREENS[0])),
           sg.Button('Connect', button_color=(sg.YELLOWS[0], sg.BLUES[0]))]]

window = sg.Window('Chat window', layout, font=('Helvetica', ' 13'),
                   default_button_element_size=(8, 2), use_default_focus=False)


# async def consumer(queue):
#     while True:
#         item = await queue.get()
#         if item is None:
#             break
#         print(f'Consumed: {item}')


# async def get_send_msg(queue, buffer_send_msg):
#     await queue.put(buffer_send_msg)
# The Event Loop
while True:
    event, value = window.read()
    if event in (sg.WIN_CLOSED, 'EXIT'):
        # quit if exit button or X
        break
    if event == 'Connect':                          # Start the server socket
        conn = server.initialize_server()
    if event == 'SEND':
        send_msg = value['-QUERY-'].rstrip()
        server.send_msg(conn, send_msg)
        asyncio.gather()
        # EXECUTE YOUR COMMAND HERE
        print('The message you send was: {}'.format(send_msg), flush=True)
        # receive_msg = sc.handle_communication(new_socket_fd, buffer_send_msg)
        # print('The message you get was: {}'.format(
        #   receive_msg.decode()), flush=True)
    asyncio.run(server.read_msg(conn))
window.close()

import PySimpleGUI as sg
import server_cython as sc
import time

'''
A simple send/response chat window.  Add call to your send-routine and print the response
If async responses can come in, then will need to use a different design that uses PySimpleGUI async design pattern
'''

sg.theme('GreenTan') # give our window a spiffy set of colors

layout = [[sg.Text('Your output will go here', size=(40, 1))],
          [sg.Output(size=(110, 20), font=('Helvetica 10'))],
          [sg.Multiline(size=(70, 5), enter_submits=False, key='-QUERY-', do_not_clear=False),
           sg.Button('SEND', button_color=(sg.YELLOWS[0], sg.BLUES[0]), bind_return_key=True),
           sg.Button('EXIT', button_color=(sg.YELLOWS[0], sg.GREENS[0])),
           sg.Button('Connect',button_color=(sg.YELLOWS[0],sg.BLUES[0]))]]

window = sg.Window('Chat window', layout, font=('Helvetica', ' 13'), default_button_element_size=(8,2), use_default_focus=False)

while True:     # The Event Loop
    event, value = window.read()
    if event in (sg.WIN_CLOSED, 'EXIT'):
        sc.close_socket(socket_fd)     
        sc.close_socket(new_socket_fd)
        print('socket has been closed')       # quit if exit button or X
        time.sleep(3)
        break
    if event == 'Connect':                          # Start the server socket
        py_socket_arr = sc.init_socket()
        socket_fd = py_socket_arr[0]
        new_socket_fd = py_socket_arr[1]
        #print(socket_fd)
        #print(new_socket_fd)
    if event == 'SEND':
        send_msg = value['-QUERY-'].rstrip()
        buffer_send_msg = send_msg.encode()
        # EXECUTE YOUR COMMAND HERE
        print('The message you send was: {}'.format(send_msg), flush=True)
        receive_msg = sc.handle_communication(new_socket_fd,buffer_send_msg)
        print('The message you get was: {}'.format(receive_msg.decode()),flush=True)

window.close()
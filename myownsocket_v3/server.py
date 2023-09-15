import server_cython

py_socket_arr = server_cython.init_socket()
socket_fd = py_socket_arr[0]
new_socket_fd = py_socket_arr[1]
server_cython.close_socket(socket_fd)
while (1):
    send_msg = input("Input msg you want to send")
    buffer_send_msg = send_msg.encode()
    receive_msg = server_cython.handle_communication(new_socket_fd,buffer_send_msg)
    print(receive_msg)

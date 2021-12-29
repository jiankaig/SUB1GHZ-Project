import socket

hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)

ip_Addr = local_ip  # Must set ip of PC
port = 4550  # Same port declare in cc3200 UDP receiver


def recv():
    opened_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = (ip_Addr, port)
    opened_socket.bind(server_address)

    # while True:
    #     data, addr = opened_socket.recvfrom(1024) # buffer size is 1024 bytes
    #     if data:
    #         print(data.decode('utf-8'))
    #         sendToTop(data.decode('utf-8'))


import socket



ip_Addr = "192.168.1.72" #  Must set ip of PC
port = 4550              #  Same port declare in cc3200 UDP receiver


opened_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = (ip_Addr, port)
opened_socket.bind(server_address)

while True:
    data, addr = opened_socket.recvfrom(1024) # buffer size is 1024 bytes
    print(data.decode('utf-8'))

s.close()

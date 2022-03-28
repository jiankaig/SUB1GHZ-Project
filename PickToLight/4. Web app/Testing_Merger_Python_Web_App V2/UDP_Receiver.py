import socket
import datetime
import SQLdb

hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)

print("Local IP: " + local_ip + " Running on port 4550")
ip_Addr = local_ip  # Must set ip of PC
port = 55007  # Same port declare in cc3200 UDP receiver
#ip_Addr = input("Enter your IP address of the PC running the server.py: \n")


def recv():
    opened_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    server_address = (ip_Addr, port)
    opened_socket.bind(server_address)

    while True:
        data, addr = opened_socket.recvfrom(1024) # buffer size is 1024 bytes
        print(data.decode('utf-8'))
        now = datetime.datetime.now()
        SQLdb.sendMessageDB(data, now)
        if data:
             print(data.decode('utf-8'))
             opened_socket.sendto("Success".encode('utf-8'),addr)


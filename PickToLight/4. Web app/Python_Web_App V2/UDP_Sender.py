import socket

ip_Addr = "192.168.18.4" #  Must set to address of cc3200
port = 2390              #  Same port declare in cc3200 UDP receiver

opened_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)




def udpSender(command):
    print(command)
    #while True:
    #msg = input("Enter command : ")
    byte_message = bytes(command, "utf-8")
    opened_socket.sendto(byte_message, (ip_Addr, port))


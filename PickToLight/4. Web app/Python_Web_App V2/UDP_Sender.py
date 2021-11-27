import socket

ip_Addr = "192.168.18.4" #  Must set to address of cc3200
port = 2390              #  Same port declare in cc3200 UDP receiver

opened_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)

ip_Addr = input("Enter IP address of CC3200: \n")


def udpSender(command):
    print(command)
    byte_message = bytes(command, "utf-8")
    opened_socket.sendto(byte_message, (ip_Addr, port))

    # data, addr = opened_socket.recvfrom(1024)
    # if data.decode('utf-8') == "Success":
    #     print("Success")


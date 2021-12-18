import socket

port = 2390  # Same port declare in cc3200 UDP receiver

opened_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)


def udpSender(command, ip_Addr):
    byte_message = bytes(command, "utf-8")
    opened_socket.sendto(byte_message, (ip_Addr, port))


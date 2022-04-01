import socket
ip_Addr = "192.168.18.8" #  Must set to address of cc3200
port = 55056 
opened_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
command="AAX00020R200G200B200BB"
print(command)
byte_message = bytes(command, "utf-8")
opened_socket.sendto(byte_message, (ip_Addr, port))

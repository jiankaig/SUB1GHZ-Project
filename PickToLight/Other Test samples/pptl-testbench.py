import socket
import time
from tokenize import Whitespace
from xml.etree.ElementPath import get_parent_map
# time.sleep(3) # Sleep for 3 seconds
ip_Addr = "192.168.18.8" #  Must set to address of cc3200
port = 55056 
class Color:
    def __init__(self, red, green, blue):
        self.r = red
        self.g = green
        self.b = blue

class testValues:
    Red = Color(255,0,0)
    Green = Color(0,255,0)
    Blue = Color(0,0,255)
    White = Color(255,255,255)
    NoColour = Color(0,0,0)

def parseLedCommand(boardId, red, green, blue):
    ledCommandString =  "AAX" + str(boardId).zfill(4) + "0R" + str(red).zfill(3) + "G" + str(green).zfill(3) + "B" + str(blue).zfill(3) + "BB"
    return ledCommandString

def Print(command):
    print("ip_Addr: {}\nport: {}\ncommand: {}\n".format(ip_Addr, port,command) )

def sendUdpCommand(command):
    opened_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
    opened_socket.sendto(command, (ip_Addr, port))

def sendToAllBoards(total, r, g, b, delay):
    for i in range(total):
        print("sending to board {}\n".format(i+1))
        command = parseLedCommand(i+1, r, g, b)
        sendUdpCommand(command)
    # time.sleep(delay) #  delay in seconds
    # for i in range(total):
    #     command = parseLedCommand(i+1, 0, 0, 0)
    #     sendUdpCommand(command)
def clearAllBoards(total):
    print("clear all..")
    for i in range(total):
        print("sending to board {}\n".format(i+1))
        command = parseLedCommand(i+1, 0, 0, 0)
        sendUdpCommand(command)
    
if __name__ == "__main__":
    # initialisations
    t = testValues()
    noOfBoards = 4
    delay = 1

    # test bench
    color = t.Red
    sendToAllBoards(noOfBoards,color.r,color.g,color.b,delay)
    # clearAllBoards(noOfBoards)

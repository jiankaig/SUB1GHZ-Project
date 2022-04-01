import socket
import time # time.sleep(3) # Sleep for 3 seconds
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
        command = parseLedCommand(i, r, g, b)
        try:
            sendUdpCommand(command)
            print("sending {} to board {}".format(command, i))
        except:
            print("error: something happened" )
    print("\n")

def sendToBoard(i, r, g, b):
    command = parseLedCommand(i, r, g, b)
    try:
        sendUdpCommand(command)
        print("sending {} to board {}\n".format(command, i))
    except:
        print("error: something happened" )
def sendToBoardCycleColours(index, delay):
    color = t.Red
    sendToBoard(index, color.r,color.g,color.b)
    time.sleep(delay)

    color = t.Green
    sendToBoard(index, color.r,color.g,color.b)
    time.sleep(delay)

    color = t.Blue
    sendToBoard(index, color.r,color.g,color.b)
    time.sleep(delay)

    color = t.White
    sendToBoard(index, color.r,color.g,color.b)
    time.sleep(delay)

    color = t.NoColour
    sendToBoard(index, color.r,color.g,color.b)

def clearAllBoards(total):
    print("clear all..")
    for i in range(total):
        command = parseLedCommand(i+1, 0, 0, 0)
        sendUdpCommand(command)
    
if __name__ == "__main__":
    # initialisations
    t = testValues()
    noOfBoards = 10
    delay = 10
    testCase = 1
    ### test bench ###
    if(testCase ==0):
            color = t.Red
            sendToAllBoards(noOfBoards,color.r,color.g,color.b,delay)
            clearAllBoards(noOfBoards)
    elif(testCase ==1):
            index = 3
            sendToBoardCycleColours(index, delay)
    elif(testCase ==2):
            print("All to Red")
            c = t.Red
            sendToAllBoards(noOfBoards, c.r, c.g, c.b, delay)
            time.sleep(delay) #give time for latency response

            print("All to Greeen")
            c = t.Green
            sendToAllBoards(noOfBoards, c.r, c.g, c.b, delay)
            time.sleep(delay)

            print("All to Blue")
            c = t.Blue
            sendToAllBoards(noOfBoards, c.r, c.g, c.b, delay)
            time.sleep(delay)

            print("All to NoColour")
            c = t.NoColour
            sendToAllBoards(noOfBoards, c.r, c.g, c.b, delay)
            time.sleep(delay)
    

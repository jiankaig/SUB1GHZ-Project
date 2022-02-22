from time import sleep

from flask import Flask, render_template,request
from flask_socketio import SocketIO
import UDP_Sender
import datetime
import SQLdb
import socket
import threading
from threading import Thread , Event
import json

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

#turn the flask app into a socketio app


# Make sure you have these version for socketio to work
# pip install --upgrade python-socketio==4.6.0
#
# pip install --upgrade python-engineio==3.13.2
#
# pip install --upgrade Flask-SocketIO==4.3.1


hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)
print("Local IP: http://127.0.0.1:5000 ,Running on port 5000")
print("For access on other device: " + local_ip + ", Running on port 5000")
ip_Addr = local_ip  # Must set ip of PC
port = 4550  # Same port declare in cc3200

global commandDict

thread = Thread()
thread_stop_event = Event()


class RandomThread(Thread):
    def __init__(self):
        self.delay = 1
        super(RandomThread, self).__init__()

    def recv(self):
        opened_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
        server_address = (ip_Addr, port)
        opened_socket.bind(server_address)

        #infinite loop of listening for udp
        while not thread_stop_event.isSet():
            data, addr = opened_socket.recvfrom(1024)  # buffer size is 1024 bytes
            data = data.decode('utf-8') #Received UDP
            last_digit = data[-1] #Check the last character of the string is of what value
            compareString = data[3:-15] #Remove characters from the UDP to find the device chosen
            data = data[8:-3] #Remove characters from the UDP to find the rbg sent
            print("This is data: "+data)
            print("This is compareString: "+compareString)
            global commandDict #Set global to utilized the variable set previously
            commandListDict = commandDict[0][9:-14]  #Remove characters from the 1st value of list to find the device chosen
            print("This is commandListDict: "+ commandListDict)
            print("This is last digit: "+ last_digit)
            if compareString == commandListDict:
                print("I'm in!")
                if last_digit == "1":
                    with open('log.txt', 'a+') as f:
                        f.writelines(str(datetime.datetime.now()) + " " + commandListDict + " Success \n")
                    socketio.emit('acknowledge', {'data': compareString})

                elif last_digit == "2":
                    if len(commandDict) > 1:
                        commandDict = commandDict[1:]
                        UDP_Sender.udpSender(commandDict[0])
                    socketio.emit('buttonPressed', {'data': compareString})
                    pass
                elif last_digit == "4":
                    socketio.emit('error', {'data': commandDict[0]})
                    with open('log.txt', 'a+') as f:
                        f.writelines(str(datetime.datetime.now()) + " " + commandListDict + " Fail \n")
                    print("I'm in 4!")
            print(commandDict)
            #socketio.emit('event', {'data': data})
            #now = datetime.datetime.now()
            #SQLdb.sendMessageDB(data, now)
            sleep(self.delay)

    def run(self):
        self.recv()


#For initial connection
@socketio.on('connect')
def test_connect():
    #print('Client connected')

    # need visibility of the global thread object
    global thread

    # Start the random number generator thread only if the thread has not been started before.
    if not thread.is_alive():
        #print("Starting Thread")
        thread = RandomThread()
        thread.start()


# def buttonListener(commands):
#     opened_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
#     server_address = (ip_Addr, port)
#     opened_socket.bind(server_address)
#     while 1:
#         data, addr = opened_socket.recvfrom(1024)  # buffer size is 1024 bytes
#         print("data recv: " + data.decode('utf-8'))
#     print(commands)



@app.route('/')
def index():
    #device_data = SQLdb.getDevices()
    return render_template('index.html')


@app.route('/fullCmd')
def fullCmd():
    val = request.args.get('rgbValues')
    id = request.args.get('deviceID')
    UDP_Sender.udpSender(val)
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("Device ID: " + id + " " + val + " " + str(now) + "\n")

    #SQLdb.sendCommandDB(id, val, now)

    return "success"



@app.route('/retryCmd')
def retryCmd():
    val = request.args.get("cmd")
    UDP_Sender.udpSender(val)
    return "success"


@app.route('/nextCmd')
def nextCmd():
    global commandDict
    commandDict = commandDict[1:]
    UDP_Sender.udpSender(commandDict[0])
    return "success"


@app.route('/getProduct')
def getProduct():
    val = request.args.get("product_ID")
    product_title = SQLdb.getProduct(val)
    if product_title == "false": #If nothing is retrieve from db, give global list an empty string
        global commandDict
        commandDict = ""
    return product_title


@app.route('/getParts')
def getParts():
    val = request.args.get("product_ID")
    parts_data = SQLdb.getParts(val)
    result = []
    command = []
    for row in parts_data:
        result.append([x for x in row])
        if len(row[0]) == 1:
            part_ID = "000" + row[0]
        elif len(row[0]) == 2:
            part_ID = "00" + row[0]
        elif len(row[0]) == 3:
            part_ID = "0" + row[0]
        else:
            part_ID = row[0]
        command.append("AT+TX AAX" + part_ID + "0R255G255B255BB")

    global commandDict #Declare global to be used elsewhere
    commandDict = command #Assign local List to global List

    #Write to log.txt
    with open('log.txt', 'a+') as f:
        f.writelines("Command: " + commandDict[0] + " " + str(datetime.datetime.now()) + "\n")

    UDP_Sender.udpSender(commandDict[0]) #Send the first command in the List of parts
    return json.dumps(result)



if __name__ == '__main__':
    #threading.Thread(target=lambda: app.run(host='127.0.0.1', port=5000, debug=True, use_reloader=False)).start()
    #threading.Thread(target=lambda: socketio.run(app, host='127.0.0.1', port=5000, debug=True, use_reloader=False)).start()
    #threading.Thread(target=UDP_Receiver.recv).start()

    #Can change to  0.0.0.0 to make it visible
    socketio.run(app, debug=True, host='0.0.0.0', port=5000, use_reloader=False)

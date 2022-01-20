from time import sleep

from flask import Flask, render_template,request
from flask_socketio import SocketIO
import UDP_Sender
import datetime
import SQLdb
import socket
from threading import Thread , Event

app = Flask(__name__)
app.config['SECRET_KEY'] = 'secret!'
socketio = SocketIO(app)

#turn the flask app into a socketio app
socketio = SocketIO(app)


# Make sure you have these version for socketio to work
# pip install --upgrade python-socketio==4.6.0
#
# pip install --upgrade python-engineio==3.13.2
#
# pip install --upgrade Flask-SocketIO==4.3.1


hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)
print("Local IP: " + local_ip + " Running on port 4550")
ip_Addr = local_ip  # Must set ip of PC
port = 4550  # Same port declare in cc3200 UDP receiver

#Random Number Generator Thread

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
            print("data recv: " + data.decode('utf-8'))
            socketio.emit('event', {'data': data.decode('utf-8')})
            now = datetime.datetime.now()
            SQLdb.sendMessageDB(data, now)
            sleep(self.delay)

    def run(self):
        self.recv()

#For initial connection
@socketio.on('connect')
def test_connect():
    print('Client connected')

    # need visibility of the global thread object
    global thread

    # Start the random number generator thread only if the thread has not been started before.
    if not thread.is_alive():
        print("Starting Thread")
        thread = RandomThread()
        thread.start()


@app.route('/')
def index():
    device_data = SQLdb.getDevices()
    return render_template('index.html', devices=device_data)


@app.route('/device2')
def device2():
    device_data = SQLdb.getDevices()
    return render_template('device2.html', devices=device_data)


@app.route('/individualBtnLED')
def individualBtnLED():
    val = request.args.get('rgbValues')
    id = request.args.get('deviceID')
    UDP_Sender.udpSender(val)
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("Device ID: " + id + " " + val + " " + str(now)+"\n")

    SQLdb.sendCommandDB(id,val, now)

    return "success"


@app.route('/textPart')
def textInputFunc():
    val = request.args.get('rgbValues')
    id = request.args.get('deviceID')
    UDP_Sender.udpSender(val)
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("Device ID: " + id + " " + val + " " + str(now) + "\n")

    SQLdb.sendCommandDB(id, val, now)

    return "success"


@app.route('/fullCmd')
def fullCmd():
    val = request.args.get('rgbValues')
    id = request.args.get('deviceID')
    UDP_Sender.udpSender(val)
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("Device ID: " + id + " " + val + " " + str(now) + "\n")

    SQLdb.sendCommandDB(id, val, now)

    return "success"


@app.route('/singleSubmit')
def singleSubmit():
    val = request.args.get('rgbValues')
    id = request.args.get('deviceID')
    UDP_Sender.udpSender(val)
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("Device ID: " + id + " " + val + " " + str(now) + "\n")

    SQLdb.sendCommandDB(id, val, now)

    return "success"


@app.route('/rgbVal', methods=['POST'])
def rbgPost():
    Val = request.get_json()
    for val in Val:
        UDP_Sender.udpSender(val['rgbValues'])
        now = datetime.datetime.now()

        with open('log.txt', 'a+') as f:
            f.writelines("Device ID: " + val['id'] + " " + val['rgbValues'] + " " + str(now) + "\n")
        SQLdb.sendCommandDB(val['id'], val['rgbValues'], now)

    return "success"



if __name__ == '__main__':
    #threading.Thread(target=lambda: app.run(host='127.0.0.1', port=5000, debug=True, use_reloader=False)).start()
    #threading.Thread(target=lambda: socketio.run(app, host='127.0.0.1', port=5000, debug=True, use_reloader=False)).start()
    #threading.Thread(target=UDP_Receiver.recv).start()

    #Can change to  0.0.0.0 to make it visible
    socketio.run(app, debug=True, host='127.0.0.1', port=5000, use_reloader=False)

from flask import Flask, render_template,request
import UDP_Sender
import UDP_Receiver
import datetime
import SQLdb
import threading

app = Flask(__name__)

@app.route('/')
def index():
    return render_template('index.html')


@app.route('/device2.html')
def device2():
    return render_template('device2.html')

@app.route('/1-GH')
def GH1():

    UDP_Sender.udpSender("AT+TX AAX00020R000G255B000BB") #edit here hard code

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00020R255G000B255BB " + str(now) + "\n")

    SQLdb.sendCommandDB("AT+TX AAX00020R000G255B000BB", now)

    return "Success"


@app.route('/1-GL')
def GL1():
    UDP_Sender.udpSender("AT+TX AAX00020R000G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00010R255G255B255BB " + str(now) + "\n")

    return "Success"


@app.route('/1-RH')
def RH1():
    UDP_Sender.udpSender("AT+TX AAX00020R125G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00010R000G255B255BB " + str(now) + "\n")

    return "Success"


@app.route('/1-RL')
def RL1():
    UDP_Sender.udpSender("AT+TX AAX00020R000G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00010R255G255B255BB " + str(now) + "\n")

    return "Success"


@app.route('/1-BH')
def BH1():
    UDP_Sender.udpSender("AT+TX AAX00040R000G000B255BB2") #hardcode for LED strip

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AT+TX AAX00040R000G000B255BB2" + str(now) + "\n")

    return "Success"


@app.route('/1-BL')
def BL1():
    UDP_Sender.udpSender("AT+TX AAX00040R000G000B000BB2") #hardcode for LED strip

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00010R255G255B255BB " + str(now) + "\n")

    return "Success"


@app.route('/2-GH')
def GH2():
    UDP_Sender.udpSender("AAX00020R000G255B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00020R000G255B000BB " + str(now) + "\n")

    return "Success"


@app.route('/2-GL')
def GL2():
    UDP_Sender.udpSender("AAX00020R000G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00020R000G000B000BB " + str(now) + "\n")

    return "Success"


@app.route('/2-RH')
def RH2():
    UDP_Sender.udpSender("AAX00020R255G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00020R255G000B000BB " + str(now) + "\n")

    return "Success"


@app.route('/2-RL')
def RL2():
    UDP_Sender.udpSender("AAX00020R000G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00020R000G000B000BB " + str(now) + "\n")

    return "Success"


@app.route('/2-BH')
def BH2():
    UDP_Sender.udpSender("AAX00020R000G000B255BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00020R000G000B255BB " + str(now) + "\n")

    return "Success"


@app.route('/2-BL')
def BL2():
    UDP_Sender.udpSender("AAX00020R000G000B000BB")
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00020R000G000B000BB " + str(now) + "\n")

    return "Success"


@app.route('/rgbVal',methods=['POST'])
def rbgPost():
    Val = request.get_json()
    for val in Val:
        UDP_Sender.udpSender(val)
        now = datetime.datetime.now()

        with open('log.txt', 'a+') as f:
            f.writelines(val + " " + str(now)+"\n")
        SQLdb.sendCommandDB(val, now)

    return "success"



if __name__ == '__main__':
    threading.Thread(target=lambda: app.run(host='127.0.0.1', port=5000, debug=True, use_reloader=False)).start()
    threading.Thread(target=UDP_Receiver.recv).start()

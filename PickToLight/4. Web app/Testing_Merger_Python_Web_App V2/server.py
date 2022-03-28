from flask import Flask, render_template,request
import UDP_Sender
import UDP_Receiver
import datetime
import SQLdb
import threading

app = Flask(__name__)

def parseLedCommand(boardId, red, green, blue):
    ledCommandString =  "AAX" + str(boardId).zfill(4) + "R" + str(red).zfill(3) + "G" + str(green).zfill(3) + "B" + str(blue).zfill(3) + "BB"
    return ledCommandString

@app.route('/')
def index():
    return render_template('index.html')


@app.route('/device2.html')
def device2():
    return render_template('device2.html')

@app.route('/3-GH')
def GH3():
    msg = parseLedCommand(3,0,255,0)
    UDP_Sender.udpSender(msg) #edit here hard code

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")

    SQLdb.sendCommandDB("LED3_GREEN_ON", now)

    return "Success"


@app.route('/3-GL')
def GL3():
    UDP_Sender.udpSender("AAX00030R000G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00010R000G000B000BB" + str(now) + "\n")
        
    SQLdb.sendCommandDB("LED3_GREEN_OFF", now)
    
    return "Success"


@app.route('/3-RH')
def RH3():
    UDP_Sender.udpSender("AAX00030R135G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00030R135G000B000BB" + str(now) + "\n")
    
    SQLdb.sendCommandDB("LED3_RED_ON", now)
    return "Success"


@app.route('/3-RL')
def RL3():
    UDP_Sender.udpSender("AAX00030R000G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00030R355G355B355BB " + str(now) + "\n")
        
    SQLdb.sendCommandDB("LED3_RED_OFF", now)
    return "Success"


@app.route('/3-BH')
def BH3():
    UDP_Sender.udpSender("AAX00030R000G000B355BB") 

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00010R000G000B255BB" + str(now) + "\n")
    
    SQLdb.sendCommandDB("LED3_BLUE_ON", now)
    return "Success"


@app.route('/3-BL')
def BL3():
    UDP_Sender.udpSender("AAX00030R000G000B000BB") 
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00030R000G000B000BB" + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_BLUE_OFF", now)
    return "Success"

@app.route('/4-GH')
def GH4():
    UDP_Sender.udpSender("AAX00040R000G255B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00040R000G255B000BB " + str(now) + "\n")
        
    SQLdb.sendCommandDB("LED4_GREEN_ON", now)
    return "Success"


@app.route('/4-GL')
def GL4():
    UDP_Sender.udpSender("AAX00040R000G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00040R000G000B000BB " + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_GREEN_OFF", now)
    return "Success"


@app.route('/4-RH')
def RH4():
    UDP_Sender.udpSender("AAX00040R255G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00040R255G000B000BB " + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_RED_ON", now)
    return "Success"


@app.route('/4-RL')
def RL4():
    UDP_Sender.udpSender("AAX00040R000G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00040R000G000B000BB " + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_RED_OFF", now)
    return "Success"


@app.route('/4-BH')
def BH4():
    UDP_Sender.udpSender("AAX00040R000G000B255BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00040R000G000B255BB" + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_BLUE_ON", now)
    return "Success"


@app.route('/3-BL')
def BL4():
    UDP_Sender.udpSender("AAX00040R000G000B000BB")
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00040R000G000B000BB" + str(now) + "\n")
    
    SQLdb.sendCommandDB("LED3_BLUE_OFF", now)
    return "Success"

@app.route('/1-SRH')
def SRH1():
    UDP_Sender.udpSender("AAX00050R255G000B000BB") 

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00050R255G000B000BB" + str(now) + "\n")
    
    SQLdb.sendCommandDB("STRIP_RED_HIGH", now)
    return "Success"

@app.route('/1-SRL')
def SRL1():
    UDP_Sender.udpSender("AAX00050R000G000B000BB") 
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00050R000G000B000BB" + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_RED_LOW", now)
    return "Success"

@app.route('/1-SGH')
def SGH1():
    UDP_Sender.udpSender("AAX00060R000G225B000BB") 

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00060R000G255B000BB" + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_GREEN_HIGH", now)
    return "Success"

@app.route('/1-SGL')
def SGL1():
    UDP_Sender.udpSender("AAX00060R000G000B000BB") 
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00060R000G000B000BB" + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_GREEN_LOW", now)
    return "Success"
    
@app.route('/1-SBH')
def SBH1():
    UDP_Sender.udpSender("AAX00070R000G000B255BB") 

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00070R000G255B000BB" + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_BLUE_HIGH", now)
    return "Success"

@app.route('/1-SBL')
def SBL1():
    UDP_Sender.udpSender("AAX00070R000G000B000BB") 
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00070R000G000B000BB" + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_BLUE_LOW", now)
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
    threading.Thread(target=lambda: app.run(host="0.0.0.0", port=5000, debug=True, use_reloader=False)).start()
    threading.Thread(target=UDP_Receiver.recv).start()

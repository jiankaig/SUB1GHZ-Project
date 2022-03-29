from flask import Flask, render_template,request
import UDP_Sender
import UDP_Receiver
import datetime
import SQLdb
import threading

app = Flask(__name__)
#LED Function 
def parseLedCommand(boardId, red, green, blue):
    ledCommandString =  "AAX" + str(boardId).zfill(4) + "R" + str(red).zfill(3) + "G" + str(green).zfill(3) + "B" + str(blue).zfill(3) + "BB"
    return ledCommandString

@app.route('/')
def index():
    return render_template('index.html')


@app.route('/device2.html')
def device2():
    return render_template('device2.html')

#########
#Slave 2#
#########
                #####
                #RED#
                #####
@app.route('/2-RH')
def RH2():
    msg = parseLedCommand(2,100,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_RED_ON", now)
    return "Success"

@app.route('/2-RL')
def RL2():
    msg = parseLedCommand(2,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_RED_OFF", now)
    return "Success"

                #######
                #Green#
                #######
@app.route('/2-GH') #For Slave 2 Green High
def GH2():
    msg = parseLedCommand(2,0,100,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_GREEN_ON", now)
    return "Success"

@app.route('/2-GL') #For Slave 2 Green Low
def GL2():
    msg = parseLedCommand(2,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_GREEN_OFF", now)
    return "Success"

                ######
                #BLUE#
                ######
@app.route('/2-BH')
def BH2():
    msg = parseLedCommand(2,0,0,100)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_BLue_ON", now)
    return "Success"


@app.route('/2-BL')
def BL2():
    msg = parseLedCommand(2,0,0,0)
    UDP_Sender.udpSender(msg) 
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_BLue_OFF", now)
    return "Success"

#########
#Slave 3#
#########

                #####
                #RED#
                #####
@app.route('/3-RH')
def RH3():
    msg = parseLedCommand(3,100,0,0)
    UDP_Sender.udpSender(msg) 
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_RED_ON", now)
    return "Success"

@app.route('/3-RL')
def RL3():
    msg = parseLedCommand(3,0,0,0)
    UDP_Sender.udpSender(msg) 
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_RED_OFF", now)
    return "Success"

                #######
                #Green#
                #######
@app.route('/3-GH') 
def GH3():
    msg = parseLedCommand(3,0,100,0)
    UDP_Sender.udpSender(msg) 
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_GREEN_ON", now)
    return "Success"

@app.route('/3-GL') 
def GL3():
    msg = parseLedCommand(3,0,0,0)
    UDP_Sender.udpSender(msg) 
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_GREEN_OFF", now)
    return "Success"

                ######
                #BLUE#
                ######
@app.route('/3-BH')
def BH3():
    msg = parseLedCommand(3,0,0,100)
    UDP_Sender.udpSender(msg) 
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_BLue_ON", now)
    return "Success"


@app.route('/3-BL')
def BL3():
    msg = parseLedCommand(3,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_BLue_OFF", now)
    return "Success"


#########
#Slave 4#
#########

                #####
                #RED#
                #####
@app.route('/4-RH')
def RH4():
    msg = parseLedCommand(4,100,0,0)
    UDP_Sender.udpSender(msg) 
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_RED_ON", now)
    return "Success"

@app.route('/4-RL')
def RL4():
    msg = parseLedCommand(4,0,0,0)
    UDP_Sender.udpSender(msg) 
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_RED_OFF", now)
    return "Success"

                #######
                #Green#
                #######
@app.route('/4-GH') 
def GH4():
    msg = parseLedCommand(4,0,100,0)
    UDP_Sender.udpSender(msg) 
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_GREEN_ON", now)
    return "Success"

@app.route('/4-GL') 
def GL4():
    msg = parseLedCommand(4,0,0,0)
    UDP_Sender.udpSender(msg) 
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_GREEN_OFF", now)
    return "Success"

                ######
                #BLUE#
                ######
@app.route('/4-BH')
def BH4():
    msg = parseLedCommand(4,0,0,100)
    UDP_Sender.udpSender(msg) 
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_BLUE_ON", now)
    return "Success"


@app.route('/4-BL')
def BL4():
    msg = parseLedCommand(3,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_BLUE_OFF", now)
    return "Success"


#########
#Slave 5#
#########

@app.route('/1-SRH')
def SRH1():
    msg = parseLedCommand(5,100,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_LED5_RED_ON", now)
    return "Success"



@app.route('/1-SRL')
def SRL1():
    msg = parseLedCommand(5,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_LED5_RED_OFF", now)
    return "Success"

#########
#Slave 6#
#########
@app.route('/1-SGH')
def SGH1():
    msg = parseLedCommand(6,0,100,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_LED5_GREEN_ON", now)
    return "Success"

@app.route('/1-SGL')
def SGL1():

    msg = parseLedCommand(6,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_LED5_GREEN_OFF", now)
    return "Success"

#########
#Slave 7#
#########
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

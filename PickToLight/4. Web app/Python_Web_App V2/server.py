from flask import Flask, render_template,request
import UDP_Sender
import UDP_Receiver
import datetime
import SQLdb
import threading

app = Flask(__name__)

def parseLedCommand(boardId, red, green, blue):
    ledCommandString =  "AAX" + str(boardId).zfill(4) + "0R" + str(red).zfill(3) + "G" + str(green).zfill(3) + "B" + str(blue).zfill(3) + "BB"
    return ledCommandString

@app.route('/')
def welcome():
    return render_template('welcome.html')

@app.route('/index.html')
def index():
    return render_template('index.html')


@app.route('/device2.html')
def device2():
    return render_template('device2.html')

#########
#Slave 0#
#########

                ###
                #R#
                ###
@app.route('/0-RH')
def RH0():
    msg = parseLedCommand(0,100,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED0_RED_ON", now)
    return render_template('index.html')

@app.route('/0-RL')
def RL0():
    msg = parseLedCommand(0,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED0_RED_OFF", now)
    return render_template('index.html')

                ###
                #G#
                ###

@app.route('/0-GH') #For Slave 0 Green High
def GH0():
    msg = parseLedCommand(0,0,0,100)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED0_GREEN_ON", now)
    return render_template('index.html')

@app.route('/0-GL') #For Slave 1 Green Low
def GL0():
    msg = parseLedCommand(0,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED0_GREEN_OFF", now)
    return render_template('index.html')

                ###
                #B#
                ###
@app.route('/0-BH')
def BH0():
    msg = parseLedCommand(0,0,100,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED0_BLue_ON", now)
    return render_template('index.html')



@app.route('/0-BL')
def BL0():
    msg = parseLedCommand(0,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED0_BLue_OFF", now)
    return render_template('index.html')



#########
#Slave 1# Swap green & Blue due to diff 
#########
                ###
                #G#
                ###
@app.route('/1-GH') #Green and blue swap
def GH1():
    msg = parseLedCommand(1,0,0,100)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED1_GREEN_ON", now)
    return render_template('index.html')

@app.route('/1-GL') #For Slave 1 Green Low
def GL1():
    msg = parseLedCommand(1,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED1_GREEN_OFF", now)
    return render_template('index.html')

                ###
                #R#
                ###
@app.route('/1-RH')
def RH1():
    msg = parseLedCommand(1,100,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED1_RED_ON", now)
    return render_template('index.html')

@app.route('/1-RL')
def RL1():
    msg = parseLedCommand(1,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED1_RED_OFF", now)
    return render_template('index.html')

                ###
                #B#
                ###
@app.route('/1-BH')#Green and blue swap
def BH1():
    msg = parseLedCommand(1,0,100,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED1_BLUE_ON", now)
    return render_template('index.html')


@app.route('/1-BL')
def BL1():
    msg = parseLedCommand(1,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED1_BLUE_OFF", now)
    return render_template('index.html')

#########
#Slave 2#
#########
                ###
                #G#
                ###
@app.route('/2-GH') #For Slave 2 Green High
def GH2():
    msg = parseLedCommand(2,0,100,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_GREEN_ON", now)
    return render_template('index.html')

@app.route('/2-GL') #For Slave 2 Green Low
def GL2():
    msg = parseLedCommand(2,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_GREEN_OFF", now)
    return render_template('index.html')

                ###
                #R#
                ###
@app.route('/2-RH')
def RH2():
    msg = parseLedCommand(2,100,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_RED_ON", now)
    return render_template('index.html')

@app.route('/2-RL')
def RL2():
    msg = parseLedCommand(2,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_RED_OFF", now)
    return render_template('index.html')


@app.route('/2-BH')
def BH2():
    msg = parseLedCommand(2,0,0,100)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_BLue_ON", now)
    return render_template('index.html')



@app.route('/2-BL')
def BL2():
    msg = parseLedCommand(2,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_BLue_OFF", now)
    return render_template('index.html')

#########
#Slave 3#
#########

                ###
                #R#
                ###
@app.route('/3-RH')
def RH3():
    msg = parseLedCommand(3,100,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_RED_ON", now)
    return render_template('index.html')

@app.route('/3-RL')
def RL3():
    msg = parseLedCommand(3,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_RED_OFF", now)
    return render_template('index.html')

                ###
                #G#
                ###

@app.route('/3-GH') #For Slave 0 Green High
def GH3():
    msg = parseLedCommand(3,0,0,100)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_GREEN_ON", now)
    return render_template('index.html')

@app.route('/3-GL') #For Slave 1 Green Low
def GL3():
    msg = parseLedCommand(3,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_GREEN_OFF", now)
    return render_template('index.html')

                ###
                #B#
                ###
@app.route('/3-BH')
def BH3():
    msg = parseLedCommand(3,0,100,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_BLue_ON", now)
    return render_template('index.html')



@app.route('/3-BL')
def BL3():
    msg = parseLedCommand(3,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_BLue_OFF", now)
    return render_template('index.html')

#########
#Slave 4#
#########

                ###
                #R#
                ###
@app.route('/4-RH')
def RH4():
    msg = parseLedCommand(4,100,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_RED_ON", now)
    return render_template('index.html')

@app.route('/4-RL')
def RL4():
    msg = parseLedCommand(4,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_RED_OFF", now)
    return render_template('index.html')

                ###
                #G#
                ###

@app.route('/4-GH') #For Slave 0 Green High
def GH4():
    msg = parseLedCommand(4,0,0,100)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_GREEN_ON", now)
    return render_template('index.html')

@app.route('/4-GL') #For Slave 1 Green Low
def GL4():
    msg = parseLedCommand(4,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_GREEN_OFF", now)
    return render_template('index.html')

                ###
                #B#
                ###
@app.route('/4-BH')
def BH4():
    msg = parseLedCommand(4,0,100,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_BLue_ON", now)
    return render_template('index.html')



@app.route('/4-BL')
def BL4():
    msg = parseLedCommand(4,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED4_BLue_OFF", now)
    return render_template('index.html')

#########
#Slave 5#
#########

                ###
                #R#
                ###
@app.route('/5-RH')
def RH5():
    msg = parseLedCommand(5,100,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED5_RED_ON", now)
    return render_template('index.html')

@app.route('/5-RL')
def RL5():
    msg = parseLedCommand(5,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED5_RED_OFF", now)
    return render_template('index.html')

                ###
                #G#
                ###

@app.route('/5-GH') #For Slave 0 Green High
def GH5():
    msg = parseLedCommand(5,0,100,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED5_GREEN_ON", now)
    return render_template('index.html')

@app.route('/5-GL') #For Slave 1 Green Low
def GL5():
    msg = parseLedCommand(5,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED5_GREEN_OFF", now)
    return render_template('index.html')

                ###
                #B#
                ###
@app.route('/5-BH')
def BH5():
    msg = parseLedCommand(5,0,0,100)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED5_BLue_ON", now)
    return render_template('index.html')



@app.route('/5-BL')
def BL5():
    msg = parseLedCommand(5,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED5_BLue_OFF", now)
    return render_template('index.html')

#########
#Slave 6#
#########

                ###
                #R#
                ###
@app.route('/6-RH')
def RH6():
    msg = parseLedCommand(6,100,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED6_RED_ON", now)
    return render_template('index.html')

@app.route('/6-RL')
def RL6():
    msg = parseLedCommand(6,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED6_RED_OFF", now)
    return render_template('index.html')

                ###
                #G#
                ###

@app.route('/6-GH') #For Slave 0 Green High
def GH6():
    msg = parseLedCommand(6,0,100,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED6_GREEN_ON", now)
    return render_template('index.html')

@app.route('/6-GL') #For Slave 1 Green Low
def GL6():
    msg = parseLedCommand(6,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED6_GREEN_OFF", now)
    return render_template('index.html')

                ###
                #B#
                ###
@app.route('/6-BH')
def BH6():
    msg = parseLedCommand(6,0,0,100)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED6_BLue_ON", now)
    return render_template('index.html')



@app.route('/6-BL')
def BL6():
    msg = parseLedCommand(6,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED6_BLue_OFF", now)
    return render_template('index.html')

#########
#Slave 7#
#########

                ###
                #R#
                ###
@app.route('/7-RH')
def RH7():
    msg = parseLedCommand(7,100,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED7_RED_ON", now)
    return render_template('index.html')

@app.route('/7-RL')
def RL7():
    msg = parseLedCommand(7,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED7_RED_OFF", now)
    return render_template('index.html')

                ###
                #G#
                ###

@app.route('/7-GH') 
def GH7():
    msg = parseLedCommand(7,0,100,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED7_GREEN_ON", now)
    return render_template('index.html')

@app.route('/7-GL') 
def GL7():
    msg = parseLedCommand(7,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED7_GREEN_OFF", now)
    return render_template('index.html')

                ###
                #B#
                ###
@app.route('/7-BH')
def BH7():
    msg = parseLedCommand(7,0,0,100)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED7_BLue_ON", now)
    return render_template('index.html')



@app.route('/7-BL')
def BL7():
    msg = parseLedCommand(7,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED7_BLue_OFF", now)
    return render_template('index.html')


#########
#Slave 8#
#########

                ###
                #R#
                ###
@app.route('/8-RH')
def RH8():
    msg = parseLedCommand(8,100,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED8_RED_ON", now)
    return render_template('index.html')

@app.route('/8-RL')
def RL8():
    msg = parseLedCommand(8,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED8_RED_OFF", now)
    return render_template('index.html')

                ###
                #G#
                ###

@app.route('/8-GH') 
def GH8():
    msg = parseLedCommand(8,0,100,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED8_GREEN_ON", now)
    return render_template('index.html')

@app.route('/8-GL') 
def GL8():
    msg = parseLedCommand(8,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED8_GREEN_OFF", now)
    return render_template('index.html')

                ###
                #B#
                ###
@app.route('/8-BH')
def BH8():
    msg = parseLedCommand(8,0,0,100)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED8_BLue_ON", now)
    return render_template('index.html')



@app.route('/8-BL')
def BL8():
    msg = parseLedCommand(8,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED8_BLue_OFF", now)
    return render_template('index.html')


#########
#Slave 9#
#########

                ###
                #R#
                ###
@app.route('/9-RH')
def RH9():
    msg = parseLedCommand(9,100,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED9_RED_ON", now)
    return render_template('index.html')

@app.route('/9-RL')
def RL9():
    msg = parseLedCommand(9,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED9_RED_OFF", now)
    return render_template('index.html')

                ###
                #G#
                ###

@app.route('/9-GH') 
def GH9():
    msg = parseLedCommand(9,0,100,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED9_GREEN_ON", now)
    return render_template('index.html')

@app.route('/9-GL') 
def GL9():
    msg = parseLedCommand(9,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED9_GREEN_OFF", now)
    return render_template('index.html')

                ###
                #B#
                ###
@app.route('/9-BH')
def BH9():
    msg = parseLedCommand(9,0,0,100)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED9_BLue_ON", now)
    return render_template('index.html')



@app.route('/9-BL')
def BL9():
    msg = parseLedCommand(8,0,0,0)
    UDP_Sender.udpSender(msg) #edit here hard code
    now = datetime.datetime.now()
    with open('log.txt', 'a+') as f:
        f.writelines(msg + str(now) + "\n")
    SQLdb.sendCommandDB("LED9_BLue_OFF", now)
    return render_template('index.html')


@app.route('/rgbVal',methods=['POST'])
def rbgPost():
    Val = request.get_json()
    for val in Val:
        UDP_Sender.udpSender(val)
        now = datetime.datetime.now()

        with open('log.txt', 'a+') as f:
            f.writelines(val + " " + str(now)+"\n")
        SQLdb.sendCommandDB(val, now)

    return render_template('index.html')


if __name__ == '__main__':
    threading.Thread(target=lambda: app.run(host="0.0.0.0", port=5000, debug=True, use_reloader=False)).start()
    threading.Thread(target=UDP_Receiver.recv).start()

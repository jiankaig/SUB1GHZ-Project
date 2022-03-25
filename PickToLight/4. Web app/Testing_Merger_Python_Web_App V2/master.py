from flask import Flask, render_template, request
import UDP_Sender
import UDP_Receiver
import datetime
import SQLdb
import requests as req
import re
import sys
sys.path.insert(0, "../../../Downloads")
from datetime import timedelta
import pyodbc
from datetime import datetime as dt
from time import sleep
import random
from opcua import ua, Server
import threading



ip_address = "http://192.168.18.8"
#192.168.18.16
#change on top line to fit webserver ip address //192.168.43.84 for YT
strip_html = "<[^<]+?>"

db_server = "192.168.18.6"
#"192.168.18.5" YT
#change on top
database = 'Web_App'
username = 'sa'
password = '123' #'12345' for yt
driver = "{ODBC Driver 17 for SQL Server}"
pESD_1_value=""
x = 'AA'

app = Flask(__name__)


@app.route('/')
def index():
    return render_template('index.html')


@app.route('/device2.html')
def device2():
    return render_template('device2.html')


@app.route('/2-GH')
def GH2():
    UDP_Sender.udpSender("AAX00020R000G255B000BB")  # edit here hard code

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00020R255G000B255BB " + str(now) + "\n")

    SQLdb.sendCommandDB("LED2_GREEN_ON", now)

    return "Success"


@app.route('/2-GL')
def GL2():
    UDP_Sender.udpSender("AAX00020R000G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00010R000G000B000BB" + str(now) + "\n")

    SQLdb.sendCommandDB("LED2_GREEN_OFF", now)

    return "Success"


@app.route('/2-RH')
def RH2():
    UDP_Sender.udpSender("AAX00020R125G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00020R125G000B000BB" + str(now) + "\n")

    SQLdb.sendCommandDB("LED2_RED_ON", now)
    return "Success"


@app.route('/2-RL')
def RL2():
    UDP_Sender.udpSender("AAX00020R000G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00020R255G255B255BB " + str(now) + "\n")

    SQLdb.sendCommandDB("LED2_RED_OFF", now)
    return "Success"


@app.route('/2-BH')
def BH2():
    UDP_Sender.udpSender("AAX00020R000G000B255BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00010R000G000B255BB" + str(now) + "\n")

    SQLdb.sendCommandDB("LED2_BLUE_ON", now)
    return "Success"


@app.route('/2-BL')
def BL2():
    UDP_Sender.udpSender("AAX00020R000G000B000BB")
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AT+TX AAX00020R000G000B000BB" + str(now) + "\n")
    SQLdb.sendCommandDB("LED2_BLUE_OFF", now)
    return "Success"


@app.route('/3-GH')
def GH3():
    UDP_Sender.udpSender("AT+TX AAX00030R000G255B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00030R000G255B000BB " + str(now) + "\n")

    SQLdb.sendCommandDB("LED3_GREEN_ON", now)
    return "Success"


@app.route('/3-GL')
def GL3():
    UDP_Sender.udpSender("AAX00030R000G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00030R000G000B000BB " + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_GREEN_OFF", now)
    return "Success"


@app.route('/3-RH')
def RH3():
    UDP_Sender.udpSender("AAX00030R255G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00030R255G000B000BB " + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_RED_ON", now)
    return "Success"


@app.route('/3-RL')
def RL3():
    UDP_Sender.udpSender("AAX00030R000G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00030R000G000B000BB " + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_RED_OFF", now)
    return "Success"


@app.route('/3-BH')
def BH3():
    UDP_Sender.udpSender("AAX00030R000G000B255BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AT+TX AAX00030R000G000B255BB " + str(now) + "\n")
    SQLdb.sendCommandDB("LED3_BLUE_ON", now)
    return "Success"


@app.route('/3-BL')
def BL3():
    UDP_Sender.udpSender("AAX00030R000G000B000BB")
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AAX00030R000G000B000BB " + str(now) + "\n")

    SQLdb.sendCommandDB("LED3_BLUE_OFF", now)
    return "Success"


@app.route('/1-SRH')
def SRH1():
    UDP_Sender.udpSender("AT+TX AAX00040R255G000B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AT+TX AAX00040R255G000B000BB" + str(now) + "\n")

    SQLdb.sendCommandDB("STRIP_RED_HIGH", now)
    return "Success"


@app.route('/1-SRL')
def SRL1():
    UDP_Sender.udpSender("AT+TX AAX00040R000G000B000BB")
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AT+TX AAX00040R000G000B000BB" + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_RED_LOW", now)
    return "Success"


@app.route('/1-SGH')
def SGH1():
    UDP_Sender.udpSender("AT+TX AAX01040R000G255B000BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AT+TX AAX01040R000G255B000BB" + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_GREEN_HIGH", now)
    return "Success"


@app.route('/1-SGL')
def SGL1():
    UDP_Sender.udpSender("AT+TX AAX01040R000G000B000BB")
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AT+TX AAX01040R000G000B000BB" + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_GREEN_LOW", now)
    return "Success"


@app.route('/1-SBH')
def SBH1():
    UDP_Sender.udpSender("AT+TX AAX02040R000G000B255BB")

    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AT+TX AAX02040R000G255B000BB" + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_BLUE_HIGH", now)
    return "Success"


@app.route('/1-SBL')
def SBL1():
    UDP_Sender.udpSender("AT+TX AAX02040R000G000B000BB")
    now = datetime.datetime.now()

    with open('log.txt', 'a+') as f:
        f.writelines("AT+TX AAX02040R000G000B000BB" + str(now) + "\n")
    SQLdb.sendCommandDB("STRIP_BLUE_LOW", now)
    return "Success"


@app.route('/rgbVal', methods=['POST'])
def rbgPost():
    Val = request.get_json()
    for val in Val:
        UDP_Sender.udpSender(val)
        now = datetime.datetime.now()

        with open('log.txt', 'a+') as f:
            f.writelines(val + " " + str(now) + "\n")
        SQLdb.sendCommandDB(val, now)

    return "success"


if __name__ == '__main__':
    threading.Thread(target=lambda: app.run(host="0.0.0.0", port=5000, debug=True, use_reloader=False)).start()
    threading.Thread(target=UDP_Receiver.recv).start()
    server = Server()
    server.set_endpoint("opc.tcp://192.168.18.6:4840")
    # Change above line here to fit your computer ip address
    # "opc.tcp://192.168.18.5:4840"

    # setup our own namespace, not really necessary but should as spec
    uri = "http://examples.freeopcua.github.io"
    idx = server.register_namespace(uri)

    # get Objects node, this is where we should put our nodes
    objects = server.get_objects_node()

    # starting!
    server.start()

    # populating our address space
    myobj = objects.add_object(idx, "MyObject")
    myvar = myobj.add_variable(idx, "ESD_1", 0)
    myvar.set_writable()  # Set MyVariable to be writable by clients

    while (1):
        resp = req.get(ip_address)
        content = resp.text
        stripped = re.sub(strip_html, '', content)

        ESD_1_tag = stripped[4:26]
        ESD_1_value = int(stripped[26:27])

        if x in chr(ESD_1_value):
            sys.stdout.flush()

        if pESD_1_value != ESD_1_value:
            currentDateTime = dt.now()
            date = currentDateTime.strftime("%Y-%m-%d")
            time = currentDateTime.strftime("%H:%M:%S")
            print(date)
            print(time)
            print(ESD_1_tag)
            print(ESD_1_value)
            print("\n")

            myvar.set_value(ESD_1_value)

            sys.stdout.flush()

            with pyodbc.connect(
                    'DRIVER=' + driver + ';SERVER=' + db_server + ";PORT=1433;DATABASE=" + database + ";UID=" + username + ";PWD=" + password) as conn:
                with conn.cursor() as cursor:
                    query = "INSERT INTO dbo.BwAnaChgLog (ProjNodeId, TagName, LogDate, LogTime, LogMilliSecond, LogValue) VALUES (7,?,?,?,4,?)"
                    val = [ESD_1_tag, date, time, ESD_1_value]
                    cursor.execute(query, val)
                    conn.commit()

        pESD_1_value = ESD_1_value

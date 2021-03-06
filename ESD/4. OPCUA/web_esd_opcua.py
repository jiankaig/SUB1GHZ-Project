import requests as req
import re
import sys
sys.path.insert(0, "..")
from datetime import timedelta 
import pyodbc
from datetime import datetime as dt
from time import sleep
import random
from opcua import ua, Server
import enum

class COMMAND_TYPE(enum.Enum):
    NO_TYPE = 0
    ESD_COMMAND = 1
    LED_COMMAND = 2
CommandType = COMMAND_TYPE.NO_TYPE

ip_address = "http://192.168.18.16"  #Input the CC3200 Webserver IP address
#192.168.18.16 
#change on top line to fit webserver ip address //192.168.43.84 (YT)
strip_html = "<[^<]+?>"

db_server = "192.168.18.5" 
#change on top 
database = 'Web_App'
username = 'sa'
password = "12345"
driver = "{ODBC Driver 17 for SQL Server}"
pESD_1_value=""
ESD_1_value=""
pintRGB_concat=""
intRGB_concat=""

if __name__ == "__main__":
    server = Server()
    server.set_endpoint("opc.tcp://192.168.18.5:4840")
    #Change above line here to fit your computer ip address
    #"opc.tcp://192.168.18.5:4840"

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
    myvar.set_writable() # Set MyVarialbe to be writable by clients
    # populating address space for Board
    myobj1 = objects.add_object(idx, "MyObject1")
    myvar1 = myobj1.add_variable(idx, "BOARD_NO", 0)
    myvar1.set_writable() # set myvar1 to be writable by client
    #For LEDs
    myobj2 = objects.add_object(idx, "MyObject2")
    myvar2 = myobj2.add_variable(idx, "LED_R", 0)
    myvar2.set_writable() # set myvar2 to be writable by client

    myobj3 = objects.add_object(idx, "MyObject3")
    myvar3 = myobj3.add_variable(idx, "LED_G", 0)
    myvar3.set_writable() # set myvar3 to be writable by client

    myobj4 = objects.add_object(idx, "MyObject4")
    myvar4 = myobj4.add_variable(idx, "LED_B", 0)
    myvar4.set_writable() # set myvar4 to be writable by client
    
    while(1):
        resp = req.get(ip_address)
        content = resp.text
        stripped = re.sub(strip_html, '', content)
        #stripped = stripped[4:]
        print("content: {}".format(content))
        print("stripped: {}".format(stripped))
        print("stripped[0:2]: {}".format(stripped[4:6]))

        if(stripped[4:6] == "L9"):
            CommandType = COMMAND_TYPE.ESD_COMMAND
            print(CommandType)
        elif(stripped[4:6] == "AA"):
            CommandType = COMMAND_TYPE.LED_COMMAND
            print(CommandType)
        if(CommandType == COMMAND_TYPE.ESD_COMMAND):
            ESD_1_tag = stripped[4:26]
            ESD_1_value = int(stripped[26:27]) #26:27
        elif(CommandType == COMMAND_TYPE.LED_COMMAND):
            LED_Location = int(stripped[7:11])
            LED_Picker = int(stripped[11:12])
            LED_RED = int(stripped[13:16]) #13:16
            LED_GREEN = int(stripped[17:20]) #17:20
            LED_BLUE = int(stripped[21:24]) #21:24
            intRGB_concat = str(stripped[13:16]+stripped[17:20]+stripped[21:24]).zfill(9)
            # print("intRGB_concat: {}".format(intRGB_concat))
        CommandType = COMMAND_TYPE.NO_TYPE
        
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
            
            with pyodbc.connect('DRIVER='+driver+';SERVER='+db_server+";PORT=1433;DATABASE="+database+";UID="+username+";PWD="+password) as conn:
                with conn.cursor() as cursor:
                    query = "INSERT INTO dbo.BwAnaChgLog (ProjNodeId, TagName, LogDate, LogTime, LogMilliSecond, LogValue) VALUES (7,?,?,?,4,?)"
                    val = [ESD_1_tag , date, time, ESD_1_value]
                    cursor.execute(query, val)
                    conn.commit()



        if pintRGB_concat != intRGB_concat:
            print("intRGB_concat changed: {}".format(intRGB_concat))
            currentDateTime = dt.now()
            date = currentDateTime.strftime("%Y-%m-%d")
            time = currentDateTime.strftime("%H:%M:%S")

            myvar1.set_value(LED_Location)
            myvar2.set_value(LED_RED)
            myvar3.set_value(LED_GREEN)
            myvar4.set_value(LED_BLUE)
            
            sys.stdout.flush()
            
            with pyodbc.connect('DRIVER='+driver+';SERVER='+db_server+";PORT=1433;DATABASE="+database+";UID="+username+";PWD="+password) as conn:
                with conn.cursor() as cursor:
                    query = "INSERT INTO dbo.LedLog1 (LED_Location, LED_Picker, LED_RED, LED_GREEN, LED_BLUE, LogDate, LogTime, intRGB_concat) VALUES (?,?,?,?,?,?,?,?)"
                    val = [LED_Location, LED_Picker, LED_RED, LED_GREEN, LED_BLUE , date, time, intRGB_concat]
                    cursor.execute(query, val)
                    conn.commit()
                    
        pESD_1_value = ESD_1_value
        pintRGB_concat = intRGB_concat

    
server.stop()
    
    

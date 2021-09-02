import requests as req
import re
import sys
from datetime import timedelta 
import pyodbc
from datetime import datetime as dt
from time import sleep
import random

ip_address = "http://192.168.172.167/80" #CC3200 ip 
strip_html = "<[^<]+?>"

server = "192.168.172.246" #localhost Server
database = 'VDBDemoDB'
username = 'sa'
password = "12qw!@QW"
driver = "{ODBC Driver 17 for SQL Server}"
pESD_1_value=""

while(1):
    resp = req.get(ip_address)
    content = resp.text
    stripped = re.sub(strip_html, '', content)
    
    ESD_1_tag = stripped[4:26]
    ESD_1_value = int(stripped[26:27])

    if pESD_1_value != ESD_1_value:
        currentDateTime = dt.now()
        date = currentDateTime.strftime("%Y-%m-%d")
        time = currentDateTime.strftime("%H:%M:%S")
        print(date)
        print(time)
        print(ESD_1_tag)
        print(ESD_1_value)        
        print("\n")
        sys.stdout.flush()
        
        with pyodbc.connect('DRIVER='+driver+';SERVER='+server+";PORT=1433;DATABASE="+database+";UID="+username+";PWD="+password) as conn:
            with conn.cursor() as cursor:
                query = "INSERT INTO dbo.BwAnaChgLog (ProjNodeId, TagName, LogDate, LogTime, LogMilliSecond, LogValue) VALUES (7,?,?,?,4,?)"
                val = [ESD_1_tag , date, time, ESD_1_value]
                cursor.execute(query, val)
                conn.commit()
        
    pESD_1_value = ESD_1_value
    

    
    


# Program to request information from CC3200 Webserver
# send web server content to SQL Server

import re
import sys
import pyodbc
import random
import requests as req
from time import sleep
from datetime import timedelta
from datetime import datetime as dt

ip_address = "http://192.168.133.133/80" # CC3200 IP Address [Obtained when running CC3200 WebServer, press reset button necesarily]
strip_html = "<[^<]+?>"

# SQL Server Information
server = "NB-X280-S331" 
database = 'VDBDemoDB'
username = 'sa'
password = '12qw!@QW'
driver = "{ODBC Driver 17 for SQL Server}"

p_data = "" # Initial value or the CC3200 Web Server String (store previous_data)

while(1):
    # request information from CC3200 Web Server
    resp = req.get(ip_address)
    content  = resp.text
    data = re.sub(strip_html, '', content) # Filter and get actual data

    if p_data != data:
        currentDateTime = dt.now()
        date = currentDateTime.strftime("%Y-%m-%d")
        time = currentDateTime.strftime("%H:%M:%S")
        
        esd_regex = re.compile(r'(\w\d+\w+ESD_\d\w+\d)\s(\d)') # pattern matching for ESD

        pESD = esd_regex.findall(p_data)
        ESD = esd_regex.findall(data)

        ESD_delta = list(set(ESD) - set(pESD)) # get difference from previous data

        for i in ESD_delta: # Get TagName and its value, store into SQL Server
            tagname = i[0]
            value = i[1]
            print("TagName : " + tagname + \
                  "\nValue : " + value + \
                  "\n")
            
            with pyodbc.connect('DRIVER='+driver+';SERVER='+server+";PORT=1433;DATABASE="+database+";UID="+username+";PWD="+password) as conn:
                with conn.cursor() as cursor:
                    query = "INSERT INTO dbo.BwAnaChgLog (ProjNodeId, TagName, LogDate, LogTime, LogMilliSecond, LogValue) VALUES (7,?,?,?,4,?)"
                    val = [tagname , date, time, value]
                    cursor.execute(query, val)
                    conn.commit()
                    
    sys.stdout.flush()
    
    p_data = data   #Store current data to update previous data

        


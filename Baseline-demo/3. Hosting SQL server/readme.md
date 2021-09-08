# Hosting SQL server

## Directory Contents:
- Installing Microsoft SQL Server v2.docx
- DBscript.sql 
- web_request_esd.py

### Installing Microsoft SQL Server v2.docx
- follow instructions in order to configure and install SQL database

### DBscript.sql 
- As mentioned in Installing Microsoft SQL Server v2.docx
- after Installing Microsoft SQL Server
- create a database(right click)
- drag and drop the ``DBscript.sql`` into **SQL server managenent studio**
- change the ``nameofdatabase`` in line 1 

```USE [nameofdatabase]``` 
- run the script ``DBscript.sql`` in **SQL server managenent studio** to import dummy table/database

### web_request_esd.py

#### pre-requisites
- python complier and IDE
- requests package
- pyodbc package

install packages via pip or pip3 or any relevant installer framework. 

#### purpose
- this python script serves two purpose
- one purpose is to receive data from the webserver(hosted on CC3200)
as such: 
```
resp = req.get(ip_address)
content = resp.text
stripped = re.sub(strip_html, '', content)

ESD_1_tag = stripped[4:26]
ESD_1_value = int(stripped[26:27])
```

- another purpose is to send and store this data in the SQL database 
as such:
```
with pyodbc.connect('DRIVER='+driver+'; SERVER='+server+"; PORT=1433;
	DATABASE="+database+"; UID="+username+"; PWD="+password) as conn:
	with conn.cursor() as cursor:
		query = "INSERT INTO dbo.BwAnaChgLog (ProjNodeId, TagName, LogDate, LogTime, LogMilliSecond, LogValue) VALUES (7,?,?,?,4,?)"
		val = [ESD_1_tag , date, time, ESD_1_value]
		cursor.execute(query, val)
		conn.commit()
``` 

#### Config

The following fields are required to change depending on setup:
- ip_address(ip address of webserver hosted on CC3200)
- server(ip address of SQL databse host)
- database(name of database)
- username(credantials for loging in SQL server)
- password(credantials for loging in SQL server)


```
ip_address = "http://192.168.172.167/80" #CC3200 ip 
strip_html = "<[^<]+?>"

server = "192.168.172.246" #localhost Server
database = 'VDBDemoDB'
username = 'sa'
password = "12qw!@QW"
driver = "{ODBC Driver 17 for SQL Server}"
pESD_1_value=""
```
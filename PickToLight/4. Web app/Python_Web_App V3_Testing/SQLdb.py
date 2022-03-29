import pyodbc


server = 'SPICYV'
database = 'Web_App'
username = 'sa'
password = '123'

conn = pyodbc.connect('DRIVER={ODBC Driver 17 for SQL Server};SERVER='+server+';DATABASE='+database+';UID='+username+';PWD='+ password)
cursor = conn.cursor()


def sendCommandDB(command,datetime):
    query = "INSERT INTO dbo.Command (Command, Datetime) VALUES (?,?)"
    val = [command, datetime]
    cursor.execute(query, val)
    conn.commit()

    return "success"

def sendMessageDB(message,datetime):
    query = "INSERT INTO dbo.message (Message,Datetime) VALUES (?,?)"
    val = [message,datetime]
    cursor.execute(query, val)
    conn.commit()

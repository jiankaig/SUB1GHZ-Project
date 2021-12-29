import pyodbc


server = 'SPICYV'
database = 'Web_App_1'
username = 'sa'
password = '123'

conn = pyodbc.connect('DRIVER={ODBC Driver 17 for SQL Server};SERVER='+server+';DATABASE='+database+';UID='+username+';PWD='+ password)
cursor = conn.cursor()


def sendCommandDB(id, command,datetime):
    query = "INSERT INTO dbo.Command (Device_ID, Command, Datetime) VALUES (?,?,?)"
    val = [id, command, datetime]
    cursor.execute(query, val)
    conn.commit()

    return "success"


def sendMessageDB(message,datetime):
    query = "INSERT INTO dbo.Message (Message,Datetime) VALUES (?,?)"
    val = [message,datetime]
    cursor.execute(query, val)
    conn.commit()

    return "success"


# def getDevices():
#     #query = "SELECT * FROM dbo.Device"
#     query = "select a.*, m.* from Device a cross apply" \
#             " (select top 1 * from Command m where m.Device_ID = a.Device_ID" \
#             " order by m.Datetime desc ) m"
#     cursor.execute(query)
#     resultQuery = []
#     data = cursor.fetchall()
#     for data in data:
#         rgbval = data[4]
#         rgbval = rgbval[-14:]
#         rgbval = rgbval[:-2]
#         rgbval = rgbval.replace('R', '').replace('G', ',').replace('B', ',')
#         data[4] = "rgb("+ rgbval + ")"
#         resultQuery.append(data)
#     #print(resultQuery)
#
#     return resultQuery


def getProduct(val):
    query = "SELECT * FROM dbo.Product WHERE Product_ID='" + val + "'"
    cursor.execute(query)
    #queryResult = cursor.fetchone()
    queryResult = cursor.fetchone()
    if queryResult is None:
        return "false"
    else:
        return queryResult[1]



def getParts(val):
    query = "SELECT a.Part_ID, p.Part_Name, a.Per " \
            "FROM dbo.Part p, dbo.Product_Parts a " \
            "WHERE p.Part_ID = a.Part_ID AND a.Product_ID='"+val+"'"
    cursor.execute(query)
    queryResult = cursor.fetchall()

    return queryResult

from flask import Flask, render_template,request
app = Flask(__name__)
import UDP_Sender


@app.route('/')
def index():
  return render_template('index.html')


@app.route('/device2.html')
def device2():
  return render_template('device2.html')

@app.route('/1-GH')
def GH1():
    UDP_Sender.udpSender("AAX00010R000G255B00BB")

    return "Success"


@app.route('/1-GL')
def GL1():
    UDP_Sender.udpSender("AAX00010R000G000B000BB")

    return "Success"


@app.route('/1-RH')
def RH1():
    UDP_Sender.udpSender("AAX00010R255G000B000BB")

    return "Success"


@app.route('/1-RL')
def RL1():
    UDP_Sender.udpSender("AAX00010R000G000B000BB")

    return "Success"


@app.route('/1-BH')
def BH1():
    UDP_Sender.udpSender("AAX00010R000G000B255BB")

    return "Success"


@app.route('/1-BL')
def BL1():
    UDP_Sender.udpSender("AAX00010R000G000B000BB")

    return "Success"


@app.route('/2-GH')
def GH2():
    UDP_Sender.udpSender("AAX00020R000G255B000BB")

    return "Success"


@app.route('/2-GL')
def GL2():
    UDP_Sender.udpSender("AAX00020R000G000B000BB")

    return "Success"


@app.route('/2-RH')
def RH2():
    UDP_Sender.udpSender("AAX00020R255G000B000BB")

    return "Success"


@app.route('/2-RL')
def RL2():
    UDP_Sender.udpSender("AAX00020R000G000B000BB")

    return "Success"


@app.route('/2-BH')
def BH2():
    UDP_Sender.udpSender("AAX00020R000G000B255BB")

    return "Success"


@app.route('/2-BL')
def BL2():
    UDP_Sender.udpSender("AAX00020R000G000B000BB")

    return "Success"


@app.route('/rgbVal')
def rbgPost():

    Val = request.args.get('rgbValues')
    print(Val)
    UDP_Sender.udpSender(Val)

    return "Success"


if __name__ == '__main__':
    app.run(debug=True)
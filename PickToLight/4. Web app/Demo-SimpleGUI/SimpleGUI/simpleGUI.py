# img_viewer.py

import PySimpleGUI as sg
import UDP_Sender
import UDP_Receiver
import threading
import socket

hostname = socket.gethostname()
local_ip = socket.gethostbyname(hostname)

ip_Addr = "192.168.1.72"  # Must set ip of PC
port = 4550  # Same port declare in cc3200 UDP receiver
opened_socket = socket.socket(socket.AF_INET, socket.SOCK_DGRAM)
server_address = (ip_Addr, port)
opened_socket.bind(server_address)
opened_socket.settimeout(2)


def simpleGUI():
    # First the window layout in 2 columns

    file_list_column = [
        [
            sg.Text("CC3200 IP Address",size=(15, 1)),
            sg.In(size=(25, 1), key="-IP-"),
        ],
        [
            sg.Text("Message to send",size=(15, 1)),
            sg.In(size=(25, 1), key="-MSGSENT-"),
            sg.Button('Send')
        ],
        [
            sg.HorizontalSeparator(),
        ],
        [
            sg.Text("Message Received", size=(15, 1)),
            sg.In(size=(25, 1), key="-MSGRECV-"),
        ]
    ]


    # image_viewer_column = [
    #     [sg.Text("Choose an image from list on left:")],
    #     [sg.Text(size=(40, 1), key="-TOUT-")],
    #     [sg.Image(key="-IMAGE-")],
    # ]


    layout = [
        [
            sg.Column(file_list_column),
            #sg.VSeparator(),
            #sg.Column(image_viewer_column),
        ]
    ]


    window = sg.Window("Image Viewer", layout)


    while True:
        event, values = window.read()
        if event == "Exit" or event == sg.WIN_CLOSED:
            break
        #
        if event == "Send":
            ipAdd = values["-IP-"]
            cmd = values["-MSGSENT-"]
            UDP_Sender.udpSender(cmd, ipAdd)

        try:
            data, addr = opened_socket.recvfrom(1024)
            #print("data is: ",data)
            window["-MSGRECV-"].update(data.decode('utf-8'))
        except socket.timeout:
            continue

        #print("test")


        # elif event == "-FILE LIST-":  # A file was chosen from the listbox
        #     try:
        #         filename = os.path.join(
        #             values["-FOLDER-"], values["-FILE LIST-"][0]
        #         )
        #         window["-TOUT-"].update(filename)
        #         window["-IMAGE-"].update(filename=filename)
        #     except:
        #         pass

    window.close()

if __name__ == '__main__':
    threading.Thread(target=simpleGUI())
    #threading.Thread(target=UDP_Receiver.recv).start()

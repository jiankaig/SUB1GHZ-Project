import time # time.sleep(3) # Sleep for 3 seconds
from pptl_helper import parseLedCommand, sendUdpCommand, sendToAllBoards, sendToBoardCycleColours, clearAllBoards
from pptl_helper import testValues
import argparse as ap

if __name__ == "__main__":
    parser = ap.ArgumentParser(description='PPTL Test Bench.. ')
    parser.add_argument('-t', default=0, type=int,
                        help='selects testcase from 0 to...')
    parser.add_argument('-d', default=0, type=int,
                        help='set delay in seconds.')
    parser.add_argument('-n', default=9, type=int,
                        help='set noOfBoards.')

    args = parser.parse_args()
    
    # initialisations
    t = testValues()
    noOfBoards = args.n
    delay = args.d
    testCase = args.t
    # testCase = input("select test case: ")
    ### test bench ###
    print("Start testCase {}...".format(testCase))
    if(testCase == 0):
            color = t.Green
            sendToAllBoards(noOfBoards,color.r,color.g,color.b,delay)
            clearAllBoards(noOfBoards)
    elif(testCase == 1):
            index = 6
            sendToBoardCycleColours(t, index, delay)
    elif(testCase == 2):
            print("All to Red")
            c = t.Red
            sendToAllBoards(noOfBoards, c.r, c.g, c.b, delay)
            time.sleep(delay) #give time for latency response

            print("All to Greeen")
            c = t.Green
            sendToAllBoards(noOfBoards, c.r, c.g, c.b, delay)
            time.sleep(delay)

            print("All to Blue")
            c = t.Blue
            sendToAllBoards(noOfBoards, c.r, c.g, c.b, delay)
            time.sleep(delay)

            print("All to NoColour")
            c = t.NoColour
            sendToAllBoards(noOfBoards, c.r, c.g, c.b, delay)
            time.sleep(delay)
    elif(testCase == 3):
        noOfBoards = 9
        delay = 2
        lwrBrdLimit = 1 
        uppBrdLimit = 2
        index = input("Enter Board Id to test, from {} to {}: ".format(lwrBrdLimit, uppBrdLimit))
        print("starting test case 3...with board ({})".format(index))
        strIndex = str(index)
        print("AT+I 0"+strIndex+"<CR>")
        sendUdpCommand("AT+I 0"+strIndex+"<CR>")
        sendToBoardCycleColours(t, index, delay)
        print("end of test case 3...with board ({})".format(index))
    elif(testCase == 4):
        # protocol test; only board 1 and 2 
        noOfBoards = 2
        delay = 2
        index = 1
        print("start test case 4...with board ({})".format(index))
        strIndex = str(index)
        print("AT+I 0"+strIndex+"<CR>")
        sendUdpCommand("AT+I 0"+strIndex+"<CR>")
        sendToBoardCycleColours(t, index, delay)
        index = 2
        print("con't test case 4...with board ({})".format(index))
        strIndex = str(index)
        print("AT+I 0"+strIndex+"<CR>")
        sendUdpCommand("AT+I 0"+strIndex+"<CR>")
        sendToBoardCycleColours(t, index, delay)
        print("end of test case 3...with board ({})".format(index))
    elif(testCase == 5):
        # led strip test
        for i in range(5,9):
            sendToBoardCycleColours(t, i, delay)

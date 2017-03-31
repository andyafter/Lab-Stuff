'''
Flask server
'''
from flask import Flask
app = Flask(__name__)

import serial, time
import sys
#from psychopy import core
condition = True
OutString = "r"
MaxNumERMs=24
currentvalues = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]

# change port number accordingly 
ard = serial.Serial('COM3', 57600, timeout = None)

ard.flushInput()
ard.flushOutput()
val = True
x = 1
z =1
msg = ""

while True:			# read message from glove first
    msg = ard.read(1)
    print(msg)
    print(msg)
    if(msg is not ""):
        break
ard.flush()

stopvalue = "r," + str(currentvalues)
currentvalues = [100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100]
cvalue = "r," + str(currentvalues)

@app.route('/')
def hello_world():
	# vibrate for 0.1 sec
    ard.write(cvalue)
    time.sleep(0.1)
    ard.write(stopvalue)
    for x in range(0,1000):
        x = x+1
    ard.flush()
    return 'Success!'

if __name__ == "__main__":
    app.run()

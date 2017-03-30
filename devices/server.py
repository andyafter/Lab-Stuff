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
ard = serial.Serial('COM3', 57600, timeout = None)

ard.flushInput()
ard.flushOutput()
val = True
x = 1
z =1
msg = ""

while True:
    msg = ard.read(1)
    print(msg)
    print(msg)
    if(msg is not ""):
        break
ard.flush()

stopvalue = b"r," + b",".join(str(x).encode() for x in currentvalues)+b','
currentvalues = [100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100]
cvalue = b"r," + b",".join(str(x).encode() for x in currentvalues)+b','


@app.route('/')
def hello_world():
    ard.write(cvalue)
    time.sleep(0.1)
    ard.write(stopvalue)
    for x in range(0,1000):
        x = x+1
    ard.flush()
    return 'Hello, World!'

if __name__ == "__main__":
    app.run()

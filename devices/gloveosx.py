'''
This is python2 version of the glove vibration
'''

import serial, time
import sys
import serial.tools.list_ports


ports = list(serial.tools.list_ports.comports())
for port in ports:
    print(port)

condition = True
OutString = "r"
MaxNumERMs=24
currentvalues = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0]
ard = serial.Serial('/dev/cu.usbserial-DN01DT3O', 57600, timeout = None)

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
stopvalue = "r," + str(currentvalues)

currentvalues = [100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100]

cvalue = "r," + str(currentvalues)

print(cvalue, len(currentvalues))
ard.write(cvalue)
#ard.flush()
for x in range(0,1000):
    x = x+1
#ard.flush()


time.sleep(0.1)
ard.write(stopvalue)
for x in range(0,1000):
    x = x+1
#ard.flush()


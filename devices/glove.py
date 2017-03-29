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

'''
while (condition==True):
 if val == True: 
   #y = raw_input('Press y to begin')
   #print (y)
   ard.flush()
   time.sleep(5)
   if ard.inWaiting():
     msg = ard.read(1)
     print (msg)
 
   if msg == 'r':
     val = False 
     
 if val == False:
   print ('off')
   
   currentvalues = [100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100]
   currentvalues = str(currentvalues)  
   ard.write(currentvalues)  
   for x in range(0,1000):
    x = x+1
   ard.flush()
   currentvalues = [0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0] 
   currentvalues = str(currentvalues)  
   ard.write(currentvalues)  
   print ('on')
   condition = False
   #print ("off")
   #currentvalues = ['r', 100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100,100]
   
   #currentvalues = str(currentvalues)  
   #ard.write(currentvalues)
   
 '''
    
#else:
 #print 'Exiting'
#exit()

import socket
import time

'''
Testing Universal Robot Connection and Controlling
'''

HOST = "172.16.205.209"    # The remote host
PORT = 30002            # The same port as used by the server
s = socket.socket()

s.connect((HOST, PORT))

moves = []

moves.append("movej([-0.14, -2.4, -1.5, -2.2775736604458237, 3.3528323423665642, -1.2291967454894914], a=1.3962634015954636, v=0.1071975511965976)\n")
moves.append("movej([-0.06, -2.4, -1.5, -2.2775736604458237, 3.3528323423665642, -1.2291967454894914], a=1.3962634015954636, v=0.1071975511965976)\n")

s.send(moves[0])
time.sleep(0.2)
s.send(moves[1])


data = s.recv(1024)
s.close()
print ("Received", repr(data))

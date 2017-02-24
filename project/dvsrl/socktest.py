from socket import *


TCP_IP = 'localhost'
TCP_PORT = 30001
BUFFER_SIZE = 1024
MESSAGE = "Connected!"

robot_socket = socket()
try:
    print "trying to connect"
    robot_socket.connect((TCP_IP, TCP_PORT))
    print "after trying"
except:
    print "failed to connect"

robot_socket.sendall(MESSAGE)

robot_socket.close()

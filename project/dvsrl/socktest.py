from socket import *


TCP_IP = '172.23.18.227'
TCP_PORT = 30001
BUFFER_SIZE = 1024
MESSAGE = "Connected!"

robot_socket = socket(AF_INET, SOCK_DGRAM)
try:
    print "trying to connect"
    robot_socket.connect((TCP_IP, TCP_PORT))
except:
    print "failed to connect"

robot_socket.send(MESSAGE)

robot_socket.close()

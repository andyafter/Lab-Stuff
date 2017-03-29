from socket import *
import struct
import numpy as np
import time

# change the name of this function, since it only take cares of the parsing now
def net_raw_UDP_jAER(data="", num_read=250, camera='DBS128', debug=0):
    EVT_DVS = 0
    EVT_APS = 1

    # later maybe move these out to increase speed

    if camera == 'DBS128':
        xmask =  0x00fe
        xshift = 1
        ymask = 0x7f00
        yshift = 8
        pmask = 0x1
        pshift = 0

    xaddr = []
    yaddr = []
    pol = []
    timestamps = []
    frames = []
    addr = []
    eventtype = EVT_DVS

    # print "read_done"
    sequence_number = struct.unpack('>I', data[0:4])[0]
    # print sequence_number
    counter = 4
    while(counter < len(data)):
        addr = struct.unpack('>I', data[counter:counter + 4])[0]
        ts = struct.unpack('>I', data[counter + 4:counter + 8])[0]
        counter = counter + 8
        # print(addr, ts)
        # print "addr\t\t", addr
        # print "timestamp\t", ts

        x_addr = (addr & xmask) >> xshift
        y_addr = (addr & ymask) >> yshift
        a_pol = (addr & pmask) >> pshift
        timestamps.append(ts)
        xaddr.append(x_addr)
        yaddr.append(y_addr)
        pol.append(a_pol)
    return timestamps, xaddr, yaddr, pol, frames


def action(host='localhost', port=8991, buf_size=8192):
    data_socket = socket(AF_INET, SOCK_DGRAM)
    data_socket.bind((host, port))

    TCP_IP = '172.16.205.209'
    TCP_PORT = 30002
    BUFFER_SIZE = 1024
    MESSAGE = "Connected!"
    moves = []

    # \n is very important 
    moves.append("movej([-0.26, -2.4, -1.5, -2.2775736604458237, 3.3528323423665642, -1.2291967454894914], a=0.3962634015954636, v=0.1071975511965976)\n")
    moves.append("movej([-0.1, -2.4, -1.5, -2.2775736604458237, 3.3528323423665642, -1.2291967454894914], a=0.3962634015954636, v=0.1071975511965976)\n")

    robot_socket = socket()
    robot_socket.connect((TCP_IP, TCP_PORT))

    n = 0

    for i in range(3000):
        data = data_socket.recv(buf_size)
        net_raw_UDP_jAER(data)
        if i%300 == 0:
            n += 1
            robot_socket.send(moves[n%2])
    robot_socket.close()

#action()

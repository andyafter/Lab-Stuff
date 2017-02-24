lfrom socket import *
import struct
import numpy as np

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
    elif camera ==  'DAVIS240':
        sizeX = 240
        sizeY = 180
        x0 = 1
        y0 = 1
        xmask = 0x003ff000
        xshift = 12
        ymask = 0x7fc00000
        yshift = 22
        pmask = 0x800
        pshift = 11
        eventtypeshift = 31
        adcmask = 0x3ff

        frame = np.zeros([7, sizeX, sizeY])

        # frames[1, :, :] = resetBuffer
        # frames[2, :, :] = readBuffer
        # frames[3, :, :] = cdsSignal
        # frames[4, :, :] = readTsBuffer
        # frames[5, :, :] = resetTsBuffer
        # frames[6, :, :] = exposures

    xaddr = []
    yaddr = []
    pol = []
    timestamps = []
    frames = []

    # print "read_done"
    sequence_number = struct.unpack('>I', data[0:4])[0]
    # print sequence_number
    counter = 4
    while(counter < len(data)):
        addr = struct.unpack('>I', data[counter:counter + 4])[0]
        ts = struct.unpack('>I', data[counter + 4:counter + 8])[0]
        counter = counter + 8
        # print "addr\t\t", addr
        # print "timestamp\t", ts

    if(camera == 'DAVIS240'):
        eventtype = (addr >> eventtypeshift) & 0x01
    else:
        eventtype = EVT_DVS

    if(eventtype == 0):  # this is a DVS event
        x_addr = (addr & xmask) >> xshift
        y_addr = (addr & ymask) >> yshift
        a_pol = (addr & pmask) >> pshift
        if debug >= 3:
            print("ts->", ts)  # ok
            print("x-> ", x_addr)
            print("y-> ", y_addr)
            print("pol->", a_pol)
        timestamps.append(ts)
        xaddr.append(x_addr)
        yaddr.append(y_addr)
        pol.append(a_pol)

    if(eventtype == 1):  # this is an APS packet
        x1 = sizeX
        y1 = sizeY

        x_addr = (addr & xmask) >> xshift
        y_addr = (addr & ymask) >> yshift
        adc_data = addr & adcmask
        read_reset = (addr >> 10) & 3

        if(x_addr >= x0 and x_addr < x1 and y_addr >= y0 and y_addr < y1):
            if(read_reset == 0):  # is reset read
                # print "reset", read_reset
                frame[1, x_addr, y_addr] = adc_data
                frame[5, x_addr, y_addr] = ts[0]  # resetTsBuffer;
            if(read_reset == 1):  # is read signal
                # print "read", read_reset
                frame[2, x_addr, y_addr] = adc_data
                frame[4, x_addr, y_addr] = ts[0]  # readTsBuffer;
            # if(read_reset == 3):    # is imu read
            # print "read_reset", read_reset
            # TODO: implement this
        if((read_reset == 0) and x_addr == 0 and y_addr == 0):
            frame = np.zeros([7, sizeX, sizeY]);
            frames.append(frame)
    return timestamps, xaddr, yaddr, pol, frames


def action(host='localhost', port=8991, buf_size=8192):
    data_socket = socket(AF_INET, SOCK_DGRAM)
    data_socket.bind((host, port))

    TCP_IP = '127.0.0.1'
    TCP_PORT = 30001
    BUFFER_SIZE = 1024
    MESSAGE = "Connected!"

    robot_socket = socket(AF_INET, SOCK_DGRAM)
    robot_socket.connect((TCP_IP, TCP_PORT))
    robot_socket.send(MESSAGE)

    for i in range(100):
        data = data_socket.recv(buf_size)
        print net_raw_UDP_jAER(data)
        robot_socket.send("event")
    robot_socket.close()

action()

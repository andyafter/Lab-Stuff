from socket import *
import struct
import numpy as np
import time

from action import net_raw_UDP_jAER


def action(host='localhost', port=8991, buf_size=8192):
    data_socket = socket(AF_INET, SOCK_DGRAM)
    data_socket.bind((host, port))

    data = data_socket.recv(buf_size)
    timestamp, x, y, pol, frames= net_raw_UDP_jAER(data)
    sec = timestamp[0]//10000

    events = 0
    event_sequence = []
    last_observation = []  # all the event positions in the last time slot of 10ms
    observation = []       # events in the current time slot
    for i in range(1000):
        data = data_socket.recv(buf_size)
        timestamp, x, y, pol, frames= net_raw_UDP_jAER(data)
        sec_t = timestamp[0]//10000
        observation.append([x,y])
        
        if sec_t != sec:
            sec = sec_t
            ###print(len(observation))
            event_sequence.append(len(observation))
            events = 0
            if not last_observation:
                # this is only to checkout if no observation will duplicate
                print("No last observation")
            else:
                # do the knn
                pass
            last_observation = observation
            observation = []


action ()

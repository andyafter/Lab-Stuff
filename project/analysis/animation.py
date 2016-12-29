import matplotlib.pyplot as plt
import numpy as np
#from mpl_toolkits.mplot3d import Axes3D
import matplotlib.animation as animation

import time


class AnimatedScatter():
    marker_ids = {}
    num_dframes = 0
    marker_data = []      # when dataset gets bigger you need to change it to something else
    time_stamps = []      # should be added to other data structures later

    def get_data(self, fname):
        f = open(fname, 'r')
        n_loop, self.marker_data, self.marker_ids = 0, [], {}
        #while n_loop < 2000000:
        with open(fname,'r') as f:
            for line in f:
                n_loop += 1          # for getting testing data
                if line == "":
                    continue
                if line[:2] == "3d":
                    self.num_dframes += 1
                    d = line.split()[1:]
                    data = []
                    # number of vectors
                    num = int(d[0])
                    for k in range(num):
                        # data stores all the points inside the marker
                        # every group is 4 elements, the second element would be something like 1.000][227.002
                        # very dirty code, just use it
                        i = k*4
                        self.marker_ids[int(d[i+1][1:])] = 1
                        vec_marker = [float(d[i+2].split('[')[-1]), float(d[i+3]), float(d[i+4].split(']')[0])]
                        if vec_marker[2]>2250:
                            continue          # cause these are not markers for use
                        data.append(vec_marker)
                    self.marker_data.append(data)

    def data_stream(self):
        for frame_data in self.marker_data:
            yield frame_data

    def show(self):
        self.get_data("./data/data.txt")

    def data_gen(self):
        for data in self.marker_data:
            yield np.array(data)


#a = AnimatedScatter()
#print "Reading Data", len(a.marker_data)
#a.get_data("./data/data.txt")

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
        n_loop = 0
        while n_loop < 2000000:
            n_loop += 1          # for getting testing data
            line = f.readline()
            if not line:
                print "end of file"
                break
            if line[:2] == "3d":
                self.num_dframes += 1
                d = line.split()[1:]
                data = []
                # number of vectors
                num = int(d[0])
                if num<10:
                    continue # here to save some time for the data analysis
                for k in range(num):
                    # data stores all the points inside the marker
                    # every group is 4 elements, the second element would be something like 1.000][227.002
                    # very dirty code, just use it
                    i = k*4
                    self.marker_ids[int(d[i+1][1:])] = 1
                    vec_marker = [float(d[i+2].split('[')[-1]), float(d[i+3]), float(d[i+4].split(']')[0])]
                    data.append(vec_marker)
                self.marker_data.append(data)
        f.close()

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

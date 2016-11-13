import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
#from mpl_toolkits.mplot3d import Axes3D
import mpl_toolkits.mplot3d.axes3d as p3

import time


class AnimatedScatter():
    marker_ids = {}
    num_dframes = 0
    marker_data = []      # when dataset gets bigger you need to change it to something else
    time_stamps = []      # should be added to other data structures later

    def read_data(self, fname):
        print "reading data"
        f = open(fname, 'r')
        n_loop = 0
        while n_loop < 200000:
            n_loop += 1          # for getting testing data
            line = f.readline()
            if not line:
                break
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
                    data.append(vec_marker)
                yield self.marker_data.append(data)
        f.close()

    def data_stream(self):
        for frame_data in self.marker_data:
            yield frame_data

    def show(self):
        print "showing"
        self.read_data("./data/data.txt")


a = AnimatedScatter()
print a.marker_data
a.read_data("./data/data.txt")
plt.ion()
fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')
sc = ax.scatter([0.1], [0.2], [0.3])
fig.show()
for frame_data in a.marker_data:
    data = np.array(frame_data)
    if not data:
        continue
    plt.pause(0.01)
    print data
    sc._offsets3d = (data[:, 0], data[:, 1], data[:, 2])
    plt.draw()

import matplotlib.pyplot as plt
import matplotlib.animation as animation
import numpy as np
from mpl_toolkits.mplot3d import Axes3D
import mpl_toolkits.mplot3d.axes3d as p3


class AnimatedScatter():
    marker_ids = {}
    num_dframes = 0
    marker_data = []      # when dataset gets bigger you need to change it to something else
    time_stamps = []      # should be added to other data structures later
    
    def read_data(self, fname):
        f = open(fname, 'r')
        n_loop = 0 
        while n_loop <200000:
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

    def animation_update_data(self, data):
        return 0 

    def show(self):
        for frame_data in self.read_data("./data/data.txt"):
            data = np.array(frame_data)
        fig = plt.figure()
        ax = p3.Axes3D(fig)

        # Setting the axes properties
        ax.set_xlim3d([0.0, 2000.0])
        ax.set_xlabel('X')

        ax.set_ylim3d([0.0, 2000.0])
        ax.set_ylabel('Y')

        ax.set_zlim3d([0.0, 2000.0])
        ax.set_zlabel('Z')
        ax.set_title('Humanoid Motion')


a = AnimatedScatter()

a.show()

import matplotlib.pyplot as plt
import numpy as np
from numpy import linalg as LA
from sklearn.cluster import KMeans

import time

from animation import AnimatedScatter


for ndata in range(2,21):
    data = AnimatedScatter()
    data.get_data("./gesdata/data{}.txt".format(str(ndata)))

    s = data.marker_data[-1]
    marker_data = np.array(data.marker_data)

    dis = np.array([])

    print len(marker_data)

    for frame in marker_data:
        sum_dis = 0
        for i in range(len(frame)-1):
            for j in range(1, len(frame)):
                sum_dis += LA.norm(np.array(frame[i])-np.array(frame[j]))
        dis = np.append(dis, sum_dis)

    plt.clf()
    plt.plot(range(len(dis)), dis)
    plt.savefig("grab{}.png".format(str(ndata)))

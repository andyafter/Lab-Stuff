import matplotlib.pyplot as plt
import numpy as np
from numpy import linalg as LA
from sklearn.cluster import KMeans

import time

from animation import AnimatedScatter



for ndata in range(2,21):
    data = AnimatedScatter()
    data.get_data("./gesdata/data{}.txt".format(str(ndata)))

    n = 0
    plt.clf()
    for frame in data.marker_data:
        plt.scatter([n]*len(frame), np.array(frame)[:, 0])
        n += 1
    plt.savefig("data{}xaxis.png".format(str(ndata)))

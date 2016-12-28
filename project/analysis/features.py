import matplotlib.pyplot as plt
import numpy as np
from numpy import linalg as LA
from sklearn.cluster import KMeans

import time

from animation import AnimatedScatter


data = AnimatedScatter()
data.get_data("./gesdata/data2.txt")

s = data.marker_data[-1]
marker_data = np.array(data.marker_data)

dis = np.array([])

for frame in marker_data:
    sum_dis = 0
    for i in range(len(frame)-1):
        for j in range(1, len(frame)):
            sum_dis += LA.norm(frame[i]-frame[j])
    dis = np.append(dis, sum_dis)

plt.plot(range(len(dis)), dis)
plt.show()

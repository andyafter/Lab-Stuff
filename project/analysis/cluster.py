import matplotlib.pyplot as plt
import numpy as np
from sklearn.cluster import KMeans
from mpl_toolkits.mplot3d import Axes3D

import time

from animation import AnimatedScatter


data = AnimatedScatter()
data.get_data("./gesdata/data3.txt")

print len(data.marker_data)
s = data.marker_data[-1]
print s

X = np.array(s)

kmeans = KMeans(n_clusters=2, random_state=0).fit(X)

prediction = kmeans.fit_predict(X)

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

ax.scatter(X[:,0], X[:,1], X[:,2])

plt.show()


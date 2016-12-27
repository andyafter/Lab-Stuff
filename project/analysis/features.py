import matplotlib.pyplot as plt
import numpy as np
from sklearn.cluster import KMeans

import time

from animation import AnimatedScatter


data = AnimatedScatter()
data.get_data("./data/data.txt")

s = data.marker_data[-1]
print s

X = np.array(s)

kmeans = KMeans(n_clusters=7, random_state=0).fit(X)

prediction = kmeans.fit_predict(X)



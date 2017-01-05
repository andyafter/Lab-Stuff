import matplotlib.pyplot as plt
import numpy as np
from numpy import linalg as LA
from sklearn.cluster import KMeans

import time

from animation import AnimatedScatter


data = AnimatedScatter()
data.get_data("./gesdata/data15.txt")


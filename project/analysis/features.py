import matplotlib.pyplot as plt
import numpy as np

import time

from animation import AnimatedScatter


data = AnimatedScatter()
data.get_data("./data/data.txt")

s = data.marker_data[-1]
print s

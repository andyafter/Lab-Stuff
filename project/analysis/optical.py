import numpy as np
import matplotlib.pyplot as plt

number_of_frames = 1000  # frequency multiplied by time
stream = []

with open('capture_optical1.txt', 'rb') as f:
    data = f.read()
    
    for i in range(number_of_frames):
        num = ord(data[2*i]) << 8
        num += ord(data[2*i+1])
        stream.append(num)
plt.plot(stream)

plt.show()

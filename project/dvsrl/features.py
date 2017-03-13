from loadaerdat import loadaerdat
import numpy as np

import time 

#timestamps, xaddr, yaddr, pol = loadaerdat(datafile='dvsdata.aedat')

'''
Timestep is 1us
'''

def gaussian_distribution():
    #loadaerdat(datafile="dvsdata.aedat")
    
    return []

X = np.array([171, 184, 210, 198, 166, 167])
Y = np.array([78, 77, 98, 110, 80, 69])
cov = np.cov([X, Y], ddof=0)
print cov

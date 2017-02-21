from loadaerdat import loadaerdat
import time 

print time.time()
timestamps, xaddr, yaddr, pol = loadaerdat(datafile='dvsdata.aedat')
print time.time()
print type(timestamps[0])
import sys
import numpy as np

'''
   The Robot class should be able to limit the real robot arm in a specific area in space.
'''

class Robot(self):
    
    def __init__(self):
        # legal actions
        self.actions = []

    def action(self):
        # do some actions here with TCP/UDP on the ur10
        pass

    def observation(self):
        # return processed image data
        # should be used with action as the atari.next() function
        pass


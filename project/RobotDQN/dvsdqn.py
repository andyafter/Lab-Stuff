import theano
import numpy as np

# Hyper Parameters:
FRAME_PER_ACTION = 1
GAMMA = 0.95 # decay rate of past observations
OBSERVE = 50000. # timesteps to observe before training
EXPLORE = 1000000. # frames over which to anneal epsilon
FINAL_EPSILON = 0.1#0.001 # final value of epsilon
INITIAL_EPSILON = 1.0#0.01 # starting value of epsilon
REPLAY_MEMORY = 1000000 # number of previous transitions to remember
BATCH_SIZE = 32 # size of minibatch
UPDATE_TIME = 10000

class RobotDQN:

    def __init__(self, actions):
        # init replay memory
	self.replayMemory = deque()
	# init some parameters
	self.timeStep = 0
	self.epsilon = INITIAL_EPSILON
	self.actions = actions

    def createQNetwork(self):
        return []

    def copyTargetQNetwork(self):
        # here you should run copy target network operation in theano or lasgane
        pass

    def trainQNetwork(self):
        # here you should run the process for training
        pass

    def setPerception(self, nectObservation, action, reward, terminal):
        # checkout the braindqn code
        pass

    def getAction(self):
        action = np.zeros(self.actions)
        return action

    def setInitState(self, observation):
        pass

    def weight_variable(self, shape):
        # return tf variables
        pass

    def bias_variable(self, shape):
        # return some variables
        pass

    def conv2d(self, x, W, stride):
        # return convolution 2d with x, W, and strides
        pass

    def max_pool_2x2(self, x):
        # return a max pool
        pass

if __name__ == '__main__':
    print "Starting Robot DQN"
    pass

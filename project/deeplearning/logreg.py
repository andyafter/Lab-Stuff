import cPickle, gzip, numpy
import theano
import theano.tensor as T

# load the dataset
f = gzip.open('mnist.pkl.gz', 'rb')
train_set, valid_set, test_set, = cPickle.load(f)
f.close()

def shared_dataset(data_xy):
    data_x, data_y = data_xy
    share_x = theano.shared(numpt.asarray(data_x, dtype = theano.config.floatX))
    share_y = theano.shared(numpt.asarray(data_y, dtype = theano.config.floatX))
    return shared_x, T.cast(shared_y, 'int32')

test_set_x, test_set_y =  shared_dataset(test_set)
valid_set_x, valid_set_y = shared_dataset(valid_set)
train_set_x, train_set_y = shared_dataset(train_set)

batch_size = 500

data = train_set_x[2*batch_size : 3*batch_size]
label = train_set_y[2*batch_size : 3*batch_size]

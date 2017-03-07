import lasagne
import theano
import theano.tensor as T
from theano.tensor.nnet import conv2d

import numpy
from PIL import Image

n,m = 512, 512

im = Image.open("lena.bmp")
pixles = im.load()
output = Image.new("L", (n, m), "white")
pix = output.load()
print im.size
for i in range(n):
    for j in range(m):
        pix[i,j] = pixles[i,j]

output = theano.tensor.nnet.conv2d(
    pixles, filters, input_shape=(b, c2, i1, i2), filter_shape=(c1, c2, k1, k2),
    border_mode='half', subsample=(1, 1))


im.close()
output.close()

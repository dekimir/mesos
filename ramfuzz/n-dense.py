#!/Users/dejan2/anaconda2/bin/python
import numpy as np
import sys
from keras import backend as K
from keras.layers import Dense, Input
from keras.layers.merge import multiply
from keras.layers.normalization import BatchNormalization
from keras.metrics import mse
from keras.models import Model
from keras.optimizers import Adam
from theano import tensor as T

datrn = []
labtrn = []
for _ in xrange(50000):
    r = np.random.randint(-99999, 99999, 4)
    datrn.append(r)
    labtrn.append(r[0] <= r[2] and r[1] <= r[3])
datrn = np.array(datrn)
labtrn = np.array(labtrn)

dense_count = int(sys.argv[1]) if len(sys.argv) > 1 else 5

inp = Input(shape=(4, ))
bnorm = BatchNormalization(input_shape=(4, ))(inp)
dense_list = []
for i in range(dense_count):
    dense_list.append(Dense(1, activation='sigmoid')(bnorm))
mult = multiply(dense_list)
ml = Model(inputs=inp, outputs=mult)
ml.compile(Adam(lr=0.01), metrics=['acc'], loss=mse)
ml.fit(datrn, labtrn, batch_size=1000, epochs=50, verbose=0)

threshold = 0.2
predictions = ml.predict(datrn)[:, 0]
errx = ((predictions > threshold) != labtrn).nonzero()[0]
print 1. - len(errx) / float(len(datrn))


def discrep(i):
    return predictions[i], labtrn[i]


def fitmore(epochs=5):
    ml.fit(datrn, labtrn, batch_size=1000, epochs=epochs)
    predictions = ml.predict(datrn)[:, 0]
    errx = ((predictions > threshold) != labtrn).nonzero()[0]
    print 1. - len(errx) / float(len(datrn))


def layer_output(layer_tensor, corpus):
    f = K.function([inp, K.learning_phase()], layer_tensor)
    return f([corpus] + [0.])[:, 0]


def despite_layer(layer_tensor):
    return labtrn * (layer_output(layer_tensor, datrn) == 0)


def despite_layer_indices(layer_tensor):
    return despite_layer(layer_tensor).nonzero()[0]


def effective_weights(lix):
    batchnorm_weights = ml.layers[1].get_weights()
    epsilon = ml.layers[1].epsilon
    gamma = batchnorm_weights[0]
    beta = batchnorm_weights[1]
    mean = batchnorm_weights[2]
    varce = batchnorm_weights[3]
    dense_weights = ml.layers[lix].get_weights()
    kernel = dense_weights[0][:, 0]
    bias = dense_weights[1][0]
    F = gamma / np.sqrt(varce + epsilon)
    eff_bias = bias + np.dot(kernel, beta - mean * F)
    return [kernel * F, eff_bias]


for i in range(dense_count):
    print "Weights%d: %r" % (i, effective_weights(i + 2))
    print 'Tests succeeded despite dens%d fail: %d' % (
        i, len(despite_layer_indices(dense_list[i])))

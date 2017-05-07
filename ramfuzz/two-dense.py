#!/Users/dejan2/anaconda2/bin/python
import numpy as np
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

inp = Input(shape=(4, ))
bnorm = BatchNormalization(input_shape=(4, ))(inp)
dens1 = Dense(1, activation='sigmoid')(bnorm)
dens2 = Dense(1, activation='sigmoid')(bnorm)
mult = multiply([dens1, dens2])
ml = Model(inputs=inp, outputs=mult)
ml.compile(Adam(lr=0.01), metrics=['acc'], loss=mse)
ml.fit(datrn, labtrn, batch_size=1000, epochs=50, verbose=0)

predictions = ml.predict(datrn)[:, 0]
errx = ((predictions > 0.44) != labtrn).nonzero()[0]
print 1. - len(errx) / float(len(datrn))


def discrep(i):
    return predictions[i], labtrn[i]


def call_layer(layer, corpus):
    f = K.function([inp, K.learning_phase()], layer)
    return f([corpus] + [0.])[:, 0]


def despite_layer(layer):
    return labtrn * (call_layer(layer, datrn) == 0)


def despite_layer_indices(layer):
    return despite_layer(layer).nonzero()[0]


def fitmore(epochs=5):
    ml.fit(datrn, labtrn, batch_size=1000, epochs=epochs)
    predictions = ml.predict(datrn)[:, 0]
    errx = ((predictions > 0.44) != labtrn).nonzero()[0]
    print 1. - len(errx) / float(len(datrn))


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


wt1 = effective_weights(2)
wt2 = effective_weights(3)
print wt1
print wt2


reluin = T.scalar('reluin', dtype='float32')
relufun = K.function([reluin], K.relu(reluin))


def relu(x):
    return relufun([x])


def dns(x, wt):
    return relu(np.dot(x, wt[0]) + wt[1])


def altpred(x):
    return dns(x, wt1) * dns(x, wt2)


print 'Success despite dens1 fail: ', len(despite_layer_indices(dens1))
print 'Success despite dens2 fail: ', len(despite_layer_indices(dens2))

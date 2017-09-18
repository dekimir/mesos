#!/Users/dejan2/anaconda2/bin/python
import glob
import fileinput
import numpy as np


class indexes:
    def __init__(self):
        self.d = dict()
        self.watermark = 1

    def get(self, x):
        if x not in self.d:
            self.d[x] = self.watermark
            self.watermark += 1
        return self.d[x]


pos_count = 0
mp = indexes()
gl = glob.glob('train/*.[sf]')
for f in gl:
    for ln in fileinput.input(f):
        br = ln.split(' ')
        if len(br) > 3:
            mp.get(br[3])
    pos_count = max(pos_count, fileinput.filelineno())
loc_count = len(mp.d)

data = []
labels = []
for f in gl:
    locs = np.empty(pos_count, np.float_)
    vals = np.empty(pos_count, np.float_)
    for ln in fileinput.input(f):
        br = ln.split(' ')
        if len(br) > 3:
            pos = fileinput.filelineno() - 1
            locs[pos] = mp.get(br[3])
            vals[pos] = br[0]
    data.append([locs, vals])
    labels.append(f.endswith('.s'))
data = np.array(data)
labels = np.array(labels)

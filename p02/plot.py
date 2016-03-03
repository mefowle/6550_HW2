#!/usr/bin/python

print "Hello, Python"

import matplotlib
matplotlib.use('Agg'
)
import matplotlib.pyplot as plt
import numpy as np

t = np.arange(1,10000, 0.01)

plt.loglog(t, 20*np.exp(-t/10.0), basex=2)
plt.grid(True)
plt.title('log x & y');
plt.savefig('myfig')


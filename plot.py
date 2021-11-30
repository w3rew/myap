#!/usr/bin/python
import numpy as np
from matplotlib import pyplot as plt
plt.rcParams["figure.figsize"] = (10,4)

hsize = 1000
tsize = 10000
h = 10.0 / hsize
tau = 0.01 / tsize

y = np.loadtxt("n.txt")

x = np.array([h * i for i in range(hsize)])

plt.plot(x, y)
plt.xlabel("x")
plt.ylabel("n")
plt.savefig("plot.png", dpi = 200, bbox_inches = "tight")
plt.show()

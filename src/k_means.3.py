import random
import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# I can plot in 3d! I don't know what the 111 is for

fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")

xs = [random.random() for x in range(10)]
ys = [random.random() for x in range(10)]
zs = [random.random() for x in range(10)]
ax.scatter(xs, ys, zs)
plt.show()

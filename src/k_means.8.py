import random, math
import numpy as np

import matplotlib

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# added something to control how many steps it rotates through
# made it smoother

fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")

precision = 10
length = 10
for color in ["red", "green", "blue"]:
    xs = [random.random() for x in range(length)]
    ys = [random.random() for x in range(length)]
    zs = [random.random() for x in range(length)]
    ax.scatter(xs, ys, zs, c=color)
for i in range(100):
    for r in [x / precision for x in range(int(2*math.pi*precision))]:
        ax.view_init(30 + math.sin(r), 30 + math.cos(r+180))
        # fig.saveFig("/tmp/plotPic{:04d}.png".format(r))
        plt.draw()
        plt.pause(.01)


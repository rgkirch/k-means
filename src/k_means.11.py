import subprocess
import random, math
import numpy as np

import matplotlib
matplotlib.use('Agg')

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# fixed a bug, made it smooth
# convert -delay 10 /tmp/plotPic*.png ~/plotPics.gif

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

precision = 30
rotationScale = 2
length = 10
for color in ["red", "green", "blue"]:
    xs = [random.random() for x in range(length)]
    ys = [random.random() for x in range(length)]
    zs = [random.random() for x in range(length)]
    ax.scatter(xs, ys, zs, c=color)
for i,r in enumerate([x / precision for x in range(int(2*math.pi*precision))]):
    ax.view_init(30 + math.sin(r) * rotationScale, 30 + math.cos(r+180) * rotationScale)
    fig.savefig('/tmp/plotPic{:04d}.png'.format(i))

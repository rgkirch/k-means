import subprocess, math
from numpy.random import random

import matplotlib
matplotlib.use('Agg')

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

def genPoints(length):
    for color in ["red", "green", "blue"]:
        xs = random(length)
        ys = random(length)
        zs = random(length)
    return (xs, ys, zs)

precision = 2
rotationScale = 4
length = 30
xs, ys, zs = genPoints(length)
ax.scatter(xs, ys, zs)
steps = [x / precision for x in range(int(2*math.pi*precision))]
for i,r in enumerate(steps):
    view_init_x = 30 + math.sin(r) * rotationScale
    view_init_y = 30 + math.cos(r+math.pi) * rotationScale
    ax.view_init(view_init_x, view_init_y)
    fig.savefig('/tmp/plotPic{:04d}.png'.format(i))
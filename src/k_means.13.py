import subprocess, math
from numpy.random import random

import matplotlib
matplotlib.use('Agg')

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# ok cool, i made three distinct groups of points,
# let's put three random points on the graph and start
# iterating

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

def genPoints(length):
    for color in ["red", "green", "blue"]:
        xs = random(length)
        ys = random(length)
        zs = random(length)
    return (xs, ys, zs)

precision = 10
rotationScale = 2
length = 100
xs, ys, zs = genPoints(length)
ax.scatter(xs/2, ys/2, zs/2)
xs, ys, zs = genPoints(length)
ax.scatter(xs/2 + .5, ys/2, zs/2)
xs, ys, zs = genPoints(length)
ax.scatter(xs/2, ys/2 + .5, zs/2 + .5)
for i,r in enumerate([x / precision for x in range(int(2*math.pi*precision))]):
    ax.view_init(30 + math.sin(r) * rotationScale, 30 + math.cos(r+math.pi) * rotationScale)
    fig.savefig('/tmp/plotPic{:04d}.png'.format(i))

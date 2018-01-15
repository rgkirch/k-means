import subprocess, math
from numpy.random import random

import matplotlib
matplotlib.use('Agg')

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

# let's have three distinct groups of points
# and then mark their averages

# first step to that is to make a function that
# generates the points, I'll call the function
# three times and scale the points and translate
# them to a quarter of the final graph

# numpy arrays support dividing by a scalar
# (and i want to use numpy because it sounds cool)
# so I'll use numpy

# i fixed the rotation to be a circle, i still had 180 degrees
# as the offset when it's in radians

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
for i,r in enumerate([x / precision for x in range(int(2*math.pi*precision))]):
    ax.view_init(30 + math.sin(r) * rotationScale, 30 + math.cos(r+math.pi) * rotationScale)
    fig.savefig('/tmp/plotPic{:04d}.png'.format(i))

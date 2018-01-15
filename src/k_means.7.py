import random, math
import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# rotating the view by a little bit to show the depth

fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")

length = 10
for color in ["red", "green", "blue"]:
    xs = [random.random() for x in range(length)]
    ys = [random.random() for x in range(length)]
    zs = [random.random() for x in range(length)]
    ax.scatter(xs, ys, zs, c=color)
for r in range(360):
    ax.view_init(30 + math.sin(r), 30 + math.cos(r+180))
    plt.draw()
    plt.pause(.01)

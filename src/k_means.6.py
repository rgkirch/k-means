import random
import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# i want to be able to rotate the plot from the program so that I can render
# it with some motion

fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")

length = 1000
for color in ["red", "green", "blue"]:
    xs = [random.random() for x in range(length)]
    ys = [random.random() for x in range(length)]
    zs = [random.random() for x in range(length)]
    ax.scatter(xs, ys, zs, c=color)
for angle in range(360):
    ax.view_init(30, angle)
    plt.draw()
    plt.pause(.001)

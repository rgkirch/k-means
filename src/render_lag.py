import random
import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")

length = 100
for color in ["red", "green", "blue"]:
    xs = [random.random() for x in range(length)]
    ys = [random.random() for x in range(length)]
    zs = [random.random() for x in range(length)]
    ax.scatter(xs, ys, zs, c=color)
plt.show()
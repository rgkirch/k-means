import random
import numpy as np
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

# more points. I can tell that it's rendering ever slower.
# I wonder if I can render a little video offline instead of viewing it in real time

fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")

length = 1000
for color in ["red", "green", "blue"]:
    xs = [random.random() for x in range(length)]
    ys = [random.random() for x in range(length)]
    zs = [random.random() for x in range(length)]
    ax.scatter(xs, ys, zs, c=color)
plt.show()

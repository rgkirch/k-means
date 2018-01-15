import random
import numpy as np
from matplotlib import pyplot as plt

# a basic scatter plot

xs = [random.random() for x in range(10)]
ys = [random.random() for x in range(10)]
plt.scatter(xs, ys)
plt.show()

import random
import numpy as np
from matplotlib import pyplot as plt

xs = [random.random() for x in range(10)]
ys = [random.random() for x in range(10)]
plt.scatter(xs, ys, c="blue")
xs = [random.random() for x in range(10)]
ys = [random.random() for x in range(10)]
plt.scatter(xs, ys, c="green")
plt.show()

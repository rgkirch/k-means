import subprocess, math
import numpy
from numpy.random import random
from PIL import Image

import matplotlib
matplotlib.use('Agg')

from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
ax = fig.add_subplot(111, projection='3d')

image = Image.open("../resources/mnms.jpg")

precision = 1
rotationScale = 2
length = 100
color = "black"

print(image.getdata(0))

with open("mnms.data", "w") as out:
    li = zip(image.getdata(0), image.getdata(1), image.getdata(2))
    b = ["{} {} {}".format(a,b,c) for a,b,c in li]
    data = "\n".join(b)
    out.write(data)
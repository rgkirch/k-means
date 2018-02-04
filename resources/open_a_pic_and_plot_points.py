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

image = Image.open("mnms.jpg")

precision = 1
rotationScale = 2
length = 100
color = "black"

print(image.getdata(0))

ax.scatter(image.getdata(0), image.getdata(1), image.getdata(2), s=1)
ax.set_xlabel("red")
ax.set_ylabel("green")
ax.set_zlabel("blue")

total_number_of_frames = int(2*math.pi*precision)
for i,r in enumerate([x / precision for x in range(int(2*math.pi*precision))]):
    print("{:2.2f}%".format(i/total_number_of_frames*100))
    ax.view_init(30 + math.sin(r) * rotationScale, 30 + math.cos(r+math.pi) * rotationScale)
    fig.savefig('/tmp/plotPic{:04d}.png'.format(i))
import io
import imageio
import math
from numpy.random import random
from PIL import Image
import matplotlib
matplotlib.use('Agg')

from matplotlib import pyplot as plt
from matplotlib import animation
from mpl_toolkits.mplot3d import Axes3D

fig = plt.figure()
plt.title("umm")
ax = fig.add_subplot(111, projection='3d')

buf = io.BytesIO()

precision = 2
rotationScale = 4
length = 30
xs = random(length)
ys = random(length)
zs = random(length)
ax.scatter(xs, ys, zs)
steps = [x / precision for x in range(int(2*math.pi*precision))]
with imageio.get_writer('whatever.gif', mode='I') as writer:
    for i, r in enumerate(steps):
        view_init_x = 30 + math.sin(r) * rotationScale
        view_init_y = 30 + math.cos(r+math.pi) * rotationScale
        ax.view_init(view_init_x, view_init_y)
        fig.savefig(buf, format='png')
        buf.seek(0)
        im = Image.open(buf)
        image = imageio.imread(im)
        writer.append_data(image)
        buf.close()

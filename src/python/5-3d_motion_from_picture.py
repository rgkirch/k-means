import matplotlib
matplotlib.use('Agg')
from PIL import Image
from matplotlib import animation
from matplotlib import pyplot as plt
from mpl_toolkits.mplot3d import Axes3D
from numpy.random import random
import imageio
import io
import math
import sys
import os
import time


def f(frame_number):
    frames_per_rotation = frames_per_second * seconds_per_rotation
    fraction_of_rotation = frame_number / frames_per_rotation
    radians = fraction_of_rotation * 2 * math.pi
    view_init_x = 30
    view_init_y = fraction_of_rotation * 360
    ax.view_init(view_init_x, view_init_y)


number_of_rotations = 1
seconds_per_rotation = 8
frames_per_second = 30

plt.title('umm')
fig = plt.figure()
image = Image.open(sys.argv[1])
xs = image.getdata(0)
ys = image.getdata(1)
zs = image.getdata(2)
colors = [[r/256, g/256, b/256] for r, g, b in zip(xs, ys, zs)]
ax = fig.add_subplot(111, projection='3d')
ax.axis('off')
ax.scatter(xs, ys, zs, c=colors, label=sys.argv[1], s=1)
# ax.set_xlabel('red')
# ax.set_ylabel('green')
# ax.set_zlabel('blue')

ax.set_xlim(0, 255)
ax.set_ylim(0, 255)
ax.set_zlim(0, 255)

anim = animation.FuncAnimation(
    fig, f, frames=frames_per_second*seconds_per_rotation*number_of_rotations, interval=1/frames_per_second)
targetFile = sys.argv[0][:-3]+'_' + \
    os.path.basename(sys.argv[1]) + \
    str(math.floor(time.time())) + \
    '.mp4'
anim.save(targetFile,
          writer='imagemagick', fps=frames_per_second, dpi=200)
print('')

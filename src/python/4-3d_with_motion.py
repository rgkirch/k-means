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


def scale_rotation_magnitude(x): return x * 4


def f(frame_number):
    frames_per_rotation = frames_per_second * seconds_per_rotation
    fraction_of_rotation = frame_number / frames_per_rotation
    radians = fraction_of_rotation * 2 * math.pi
    view_init_x = 30 + scale_rotation_magnitude(math.sin(radians))
    view_init_y = 30 + scale_rotation_magnitude(math.cos(radians+math.pi))
    ax.view_init(view_init_x, view_init_y)


number_of_points = 30
number_of_rotations = 3
seconds_per_rotation = 1
frames_per_second = 30

fig = plt.figure()
plt.title("umm")
ax = fig.add_subplot(111, projection='3d')

xs = random(number_of_points)
ys = random(number_of_points)
zs = random(number_of_points)
ax.set_xlim(0, 1)
ax.set_ylim(0, 1)
ax.set_zlim(0, 1)
ax.scatter(xs, ys, zs)
anim = animation.FuncAnimation(
    fig, f, frames=frames_per_second*seconds_per_rotation*number_of_rotations, interval=1/frames_per_second)
anim.save('whatever.mp4', writer='imagemagick', fps=frames_per_second)

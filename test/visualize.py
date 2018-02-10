import sys
from mpl_toolkits.mplot3d import Axes3D
from matplotlib import pyplot as plt
from PIL import Image

fig = plt.figure()
ax = fig.add_subplot(111, projection="3d")
#image = Image.open("/tmp/randomVariation.png")
image = Image.open(sys.argv[1])
red = image.getdata(0)
green = image.getdata(1)
blue = image.getdata(2)
colors = [[r/256, g/256, b/256] for r, g, b in zip(red, green, blue)]
ax.scatter(red, green, blue, c=colors)
ax.set_xlabel("red")
ax.set_ylabel("green")
ax.set_zlabel("blue")
ax.set_xlim(0, 255)
ax.set_ylim(0, 255)
ax.set_zlim(0, 255)

plt.show()

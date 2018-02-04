import subprocess
import math
from PIL import Image

image = Image.open("small-image.jpg")

with open("small-image.data", "w") as out:
    li = zip(image.getdata(0), image.getdata(1), image.getdata(2))
    b = ["{} {} {}".format(a, b, c) for a, b, c in li]
    data = "\n".join(b)
    out.write(data)

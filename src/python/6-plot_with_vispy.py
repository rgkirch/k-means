import numpy as np

from vispy import gloo
from vispy import app
from vispy.util.transforms import perspective, translate, rotate
from PIL import Image
import sys

vert = """
//# version 120

uniform mat4 u_model;
uniform mat4 u_view;
uniform mat4 u_projection;
uniform float u_size;

attribute vec3  a_position;

varying vec4 v_color;

void main (void) {
    v_color  = vec4(a_position,1.0);
    gl_Position = u_projection * u_view * u_model * vec4(a_position,1.0);
    gl_PointSize = u_size;
}
"""

frag = """
varying vec4 v_color;

void main()
{
    float r = sqrt(pow(gl_PointCoord.x - 0.5, 2) + pow(gl_PointCoord.y - 0.5, 2));

    if( r > 0.5)
    {
        discard;
    }
    else
    {
       gl_FragColor = v_color;
    }
}
"""


class Canvas(app.Canvas):

    def __init__(self):
        app.Canvas.__init__(self, title="k-means vispy canvas", fullscreen=True, position=(-1920, 0),
                            keys='interactive', size=(800, 600))
        ps = self.pixel_scale

        image = Image.open(sys.argv[1])
        xs = image.getdata(0)
        ys = image.getdata(1)
        zs = image.getdata(2)
        colors = [[r/256, g/256, b/256] for r, g, b in zip(xs, ys, zs)]

        # Create vertices
        n = len(colors)
        data = np.zeros(n, [('a_position', np.float32, 3)])
        data['a_position'] = np.asarray(colors)
        # data['a_position'] = 0.45 * np.random.randn(n, 3)

        self.translate = 5
        self.point_size = 20*ps
        self.program = gloo.Program(vert, frag)
        self.view = translate((0, 0, -self.translate))
        self.model = np.eye(4, dtype=np.float32)
        # self.model = translate(-1, (1, 1, 0))
        self.projection = np.eye(4, dtype=np.float32)

        self.apply_zoom()

        self.program.bind(gloo.VertexBuffer(data))
        self.program['u_model'] = self.model
        self.program['u_view'] = self.view
        self.program['u_size'] = self.point_size

        self.theta = 0
        self.phi = 0

        gloo.set_state('translucent', clear_color='white')

        self.timer = app.Timer('auto', connect=self.on_timer, start=True)

        self.show()

    def on_key_press(self, event):
        if event.text == ' ':
            if self.timer.running:
                self.timer.stop()
            else:
                self.timer.start()
        if event.text == '.':
            self.translate -= 1.0
            self.view = translate((0, 0, -self.translate))
        if event.text == 'e':
            self.translate += 1.0
            self.view = translate((0, 0, -self.translate))
            self.update()

    def on_timer(self, event):
        self.theta += 0.5
        self.phi += 0.5
        self.model = np.dot(rotate(self.theta, (0, 0, 1)),
                            rotate(self.phi, (0, 1, 0)))
        self.program['u_model'] = self.model
        self.update()

    def on_resize(self, event):
        self.apply_zoom()

    def on_mouse_wheel(self, event):
        self.point_size -= event.delta[1]
        self.point_size = max(1, self.point_size)
        self.program['u_size'] = self.point_size
        self.update()

    def on_draw(self, event):
        gloo.clear()
        self.program.draw('points')

    def apply_zoom(self):
        gloo.set_viewport(0, 0, self.physical_size[0], self.physical_size[1])
        self.projection = perspective(45.0, self.size[0] /
                                      float(self.size[1]), 1.0, 1000.0)
        self.program['u_projection'] = self.projection


if __name__ == '__main__':
    c = Canvas()
    app.run()

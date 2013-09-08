uniform mat4 matrix;
attribute vec3 vertices;
attribute vec2 texcoord;
varying vec2 uvs;


void main(void) {
  gl_Position = matrix * vec4(vertices, 1.0);
  uvs = texcoord;
}

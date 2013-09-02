uniform mat4 matrix;
attribute vec3 vertices;

void main(void) {
  gl_Position = matrix * vec4(vertices, 1.0);
}

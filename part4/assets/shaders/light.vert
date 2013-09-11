uniform mat4 matrix;
uniform mat4 modelMatrix;
uniform vec3 color;
attribute vec3 vertices;

out vec3 _color;
out vec3 _vertex;
out vec4 _screenCoord;

void		main()
{
  gl_Position = matrix * modelMatrix * vec4(vertices, 1.0);
  _color = color;
  _vertex = vertices;
  _screenCoord = gl_Position;
}

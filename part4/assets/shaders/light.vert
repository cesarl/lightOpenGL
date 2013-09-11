uniform mat4 matrix;
uniform mat4 modelMatrix;
uniform vec3 color;
attribute vec3 vertices;

out vec3 _spacePos;
out vec3 _color;

void		main()
{
  gl_Position = matrix * modelMatrix * vec4(vertices, 1.0);
  _spacePos = gl_Position.xyz;
  _color = color;
}

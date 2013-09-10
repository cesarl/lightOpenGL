uniform mat4 matrix;
uniform mat4 modelMatrix;
attribute vec3 vertices;
attribute vec2 texcoord;
attribute vec3 normals;

out vec3 _spacePos;
out vec3 _normals;
out vec3 _texcoord;

void		main()
{
  gl_Position = matrix * modelMatrix * vec4(vertices, 1.0);
  _spacePos = gl_Position.xyz;
  _normals = (matrix * vec4(normals, 0.0)).xyz;
  _texcoord = vec3(texcoord, 0.0);
}

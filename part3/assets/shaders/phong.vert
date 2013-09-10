uniform mat4 matrix;
uniform mat4 modelMatrix;
attribute vec3 vertices;
attribute vec2 texcoord;
attribute vec3 normals;

varying vec2 uvs;

out vec3 cameraPosition;
out vec3 cameraNormal;
out mat4 viewMatrix;


void main(void) {
  gl_Position = matrix * modelMatrix * vec4(vertices, 1.0);
  uvs = texcoord;
  cameraPosition = vec3(matrix * modelMatrix * vec4(vertices, 1.0));
  cameraNormal = vec3(matrix * modelMatrix * vec4(normals, 0.0));
  viewMatrix = matrix;
}

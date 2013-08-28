in vec3 vertices;
in vec3 normals;
in vec2 uvs;

/* out vec3 v; */
/* out vec3 n; */
/* out vec2 u; */

void		main()
{
  /* v = vertices; */
  /* n = normals; */
  /* u = uvs; */

  /* gl_Position = ftransform() * vec4(vertices, 1.0f); */
  /* gl_FrontColor = vec4(1.0f, 0.0f, 1.0f, 1.0f); */
  /* gl_FrontColor = vec4(1.0f, 0.0f, 1.0f, 1.0f); */

  gl_Position = ftransform();
  gl_FrontColor = gl_Color;
  /* gl_TexCoord[0]  = gl_MultiTexCoord0; */
}

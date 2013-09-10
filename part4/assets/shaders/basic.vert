uniform mat4 matrix;

void		main()
{
  gl_Position = matrix * vec4(gl_Vertex.xyz, 1);
  gl_FrontColor = gl_Color;
  /* gl_TexCoord[0]  = gl_MultiTexCoord0; */
}

uniform mat4 matrix;

void		main()
{
  gl_Position = matrix * gl_Vertex;
  gl_FrontColor = gl_Color;
  /* gl_TexCoord[0]  = gl_MultiTexCoord0; */
}

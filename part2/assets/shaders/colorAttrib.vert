attribute vec3 myColor;// = vec3(1.0f, 1.0f, 1.0f);

void		main()
{
  gl_Position = ftransform();
  gl_FrontColor = vec4(myColor, 1.0f);
}

/* layout(location = 0) in vec4 position; */
/* layout(location = 1) in vec4 diffuse; */
/* layout(location = 2) in vec4 normal; */
/* layout(location = 3) in vec4 texture; */

void		main()
{
  gl_FragData[0] = gl_ProjectionMatrix * gl_ModelViewMatrix * gl_Vertex;
  //  gl_FrontColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);
  //  gl_Position = ftransform();// *position;
}

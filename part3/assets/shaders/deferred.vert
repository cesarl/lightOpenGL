/* in vec3 vertices; */
/* in vec3 normals; */
/* in vec2 uvs; */

/* out vec2 u; */

/* void		main() */
/* { */
/*   gl_Position = ftransform() * vec4(vertices.rg, 0.0f, 1.0f); */
/*   u = uvs; */
/*   gl_FrontColor = vec4(uvs, 1.0f, 1.0f); */
/*   gl_TexCoord[0]  = gl_MultiTexCoord0; */
/* } */


#if __VERSION__ >= 130

//Vertex position attribute
in vec2 vertices;

//Texture coordinate attribute
in vec2 uvs;
out vec2 texCoord;

#else

//Vertex position attribute
attribute vec2 vertices;

//Texture coordinate attribute
attribute vec2 uvs;
varying vec2 texCoord;

#endif

void main()
{
  //Process texCoord
  texCoord = uvs;
  
  //Process vertex
  gl_Position = ftransform() * vec4( vertices.x, vertices.y, 0.0, 1.0 );
}

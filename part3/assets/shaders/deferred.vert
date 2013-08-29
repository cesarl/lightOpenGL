//Vertex position attribute
in vec3 vertices;

//Texture coordinate attribute
in vec2 uvs;
out vec2 texCoord;


void main()
{
  //Process texCoord
  texCoord = uvs;
  
  //Process vertex
  gl_Position = ftransform() * vec4( vertices.x, vertices.y, vertices.z, 1.0 );
}

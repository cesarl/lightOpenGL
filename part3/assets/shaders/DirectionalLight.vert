attribute vec4	vCoord;
attribute vec3	vNormal;

uniform mat4	m, v, p;
uniform mat3	trans;

varying vec4	color;

struct		lightSource
{
  vec4		position;
  vec4		diffuse;
};

lightSource	light0 = lightSource(
		     vec4(-1.0, 1.0, -1.0, 0.0),
		     vec4(1.0, 1.0, 1.0, 1.0)
		     );

struct		material
{
  vec4		diffuse;
};

  material	myMaterial = material(vec4(1.0, 0.8, 0.8, 1.0));

void		main()
{
  mat4 mvp = p * v * m;
  vec3 normalDirection = normalize(trans * vNormal);
  vec3 lightDirection = normalize(vec3(light0.position));
  
  vec3 diffuseReflexion =
    vec3(light0.diffuse) * vec3(myMaterial.diffuse)
    * max(0.0, dot(normalDirection, lightDirection));

  color = vec4(diffuseReflexion, 1.0);

  gl_Position = mvp * vCoord;
}

#ifndef					__OBJ_LOADER_HH__
# define				__OBJ_LOADER_HH__

#include				<iostream>
#include				<fstream>
#include				<string>
#include				<vector>
#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<glm/glm.hpp>
#include				<tiny_obj_loader.h>
#include				"Loader.hpp"
#include				"ObjModelMedia.hpp"

class					ObjLoader : public Loader<ObjModelMedia>
{
public:
  ObjLoader() : Loader<ObjModelMedia>()
  {}

  virtual ~ObjLoader()
  {}

  virtual ObjModelMedia			*load(const File &file, bool force = false)
  {


    std::vector<glm::vec3>		resVertices;
    std::vector<glm::vec2>		resUvs;
    std::vector<glm::vec3>		resNormals;

    std::string inputfile = file.getFullName();
    std::vector<tinyobj::shape_t> shapes;

    std::string err = tinyobj::LoadObj(shapes, inputfile.c_str());

    if (!err.empty())
      {
    throw LoadingFailed(file.getFullName(), err);
    }

    std::cout << "# of shapes : " << shapes.size() << std::endl;

    for (size_t i = 0; i < shapes.size(); i++)
      {
	for (size_t v = 0; v < shapes[i].mesh.indices.size(); v++)
	  {
	    if (shapes[i].mesh.positions.size() > 0)
	      resVertices.push_back(glm::vec3(shapes[i].mesh.positions[shapes[i].mesh.indices[v] * 3 + 0],
					      shapes[i].mesh.positions[shapes[i].mesh.indices[v] * 3 + 1],
					      shapes[i].mesh.positions[shapes[i].mesh.indices[v] * 3 + 2]));
	    if (shapes[i].mesh.normals.size() > 0)
	      resNormals.push_back(glm::vec3(shapes[i].mesh.normals[shapes[i].mesh.indices[v] * 3 + 0],
					     shapes[i].mesh.normals[shapes[i].mesh.indices[v] * 3 + 1],
					     shapes[i].mesh.normals[shapes[i].mesh.indices[v] * 3 + 2]));
	    if (shapes[i].mesh.texcoords.size() > 0)
	      resUvs.push_back(glm::vec2(shapes[i].mesh.texcoords[shapes[i].mesh.indices[v] * 2 + 0],
					 shapes[i].mesh.texcoords[shapes[i].mesh.indices[v] * 2 + 1]));
	  }
	printf("shape[%ld].material.name = %s\n", i, shapes[i].material.name.c_str());
	printf("  material.Ka = (%f, %f ,%f)\n", shapes[i].material.ambient[0], shapes[i].material.ambient[1], shapes[i].material.ambient[2]);
	printf("  material.Kd = (%f, %f ,%f)\n", shapes[i].material.diffuse[0], shapes[i].material.diffuse[1], shapes[i].material.diffuse[2]);
	printf("  material.Ks = (%f, %f ,%f)\n", shapes[i].material.specular[0], shapes[i].material.specular[1], shapes[i].material.specular[2]);
	printf("  material.Tr = (%f, %f ,%f)\n", shapes[i].material.transmittance[0], shapes[i].material.transmittance[1], shapes[i].material.transmittance[2]);
	printf("  material.Ke = (%f, %f ,%f)\n", shapes[i].material.emission[0], shapes[i].material.emission[1], shapes[i].material.emission[2]);
	printf("  material.Ns = %f\n", shapes[i].material.shininess);
	printf("  material.map_Ka = %s\n", shapes[i].material.ambient_texname.c_str());
	printf("  material.map_Kd = %s\n", shapes[i].material.diffuse_texname.c_str());
	printf("  material.map_Ks = %s\n", shapes[i].material.specular_texname.c_str());
	printf("  material.map_Ns = %s\n", shapes[i].material.normal_texname.c_str());
	std::map<std::string, std::string>::iterator it(shapes[i].material.unknown_parameter.begin());
	std::map<std::string, std::string>::iterator itEnd(shapes[i].material.unknown_parameter.end());
	for (; it != itEnd; it++) {
	  printf("  material.%s = %s\n", it->first.c_str(), it->second.c_str());
	}
	printf("\n");
      }

    GLuint				vertexBuffer;

    glGenBuffers(1, &vertexBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    glBufferData(GL_ARRAY_BUFFER, resVertices.size() * sizeof(glm::vec3), &resVertices[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);

    GLuint				uvBuffer;

    glGenBuffers(1, &uvBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    glBufferData(GL_ARRAY_BUFFER, resUvs.size() * sizeof(glm::vec2), &resUvs[0], GL_STATIC_DRAW);
    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return new ObjModelMedia(vertexBuffer, uvBuffer, resVertices.size(), file.getFileName(), force);
  }
  virtual void				save(const ObjModelMedia *, const std::string &name)
  {
    throw LoadingFailed(name, "ObjLoader doesn't support SAVE.");
  }
};

#endif					// __OBJ_LOADER_HH__

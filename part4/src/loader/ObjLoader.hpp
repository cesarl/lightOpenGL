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
	printf("\n");
      }


    GLuint				vertexBuffer = 0;

    if (shapes[0].mesh.positions.size() > 0)
      {
	glGenBuffers(1, &vertexBuffer);
	if (vertexBuffer <= 0)
	  {
	    std::cout << "Vertex buffer error" << std::endl;
	  }
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glBufferData(GL_ARRAY_BUFFER, resVertices.size() * sizeof(glm::vec3), &resVertices[0], GL_STATIC_DRAW);
      }

    GLuint				texcoords = 0;

    if (shapes[0].mesh.texcoords.size() > 0)
      {
	glGenBuffers(1, &texcoords);
	if (vertexBuffer <= 0)
	  {
	    std::cout << "TexCoords buffer error" << std::endl;
	  }
	glBindBuffer(GL_ARRAY_BUFFER, texcoords);
	glBufferData(GL_ARRAY_BUFFER, resUvs.size() * sizeof(glm::vec2), &resUvs[0], GL_STATIC_DRAW);
      }

    GLuint				normalBuffer = 0;

    if (shapes[0].mesh.normals.size() > 0)
      {
	glGenBuffers(1, &normalBuffer);
	if (normalBuffer <= 0)
	  {
	    std::cout << "Normal buffer error" << std::endl;
	  }
	glBindBuffer(GL_ARRAY_BUFFER, normalBuffer);
	glBufferData(GL_ARRAY_BUFFER, resNormals.size() * sizeof(glm::vec3), &resNormals[0], GL_STATIC_DRAW);
      }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    return new ObjModelMedia(vertexBuffer, texcoords, normalBuffer, resVertices.size(), file.getFileName(), force);
  }
  virtual void				save(const ObjModelMedia *, const std::string &name)
  {
    throw LoadingFailed(name, "ObjLoader doesn't support SAVE.");
  }
};

#endif					// __OBJ_LOADER_HH__

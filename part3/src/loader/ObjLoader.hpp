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
    std::vector<glm::vec3>		vertex;
    std::vector<glm::vec2>		texCoord;
    std::vector<glm::vec3>		normals;
    std::vector<ObjModelMedia::Face>	faces;

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
	    ObjModelMedia::Face		f;

	    if (shapes[i].mesh.positions.size() > 0)
	      {
		vertex.push_back(glm::vec3(shapes[i].mesh.positions[shapes[i].mesh.indices[v] * 3 + 0],
					   shapes[i].mesh.positions[shapes[i].mesh.indices[v] * 3 + 1],
					   shapes[i].mesh.positions[shapes[i].mesh.indices[v] * 3 + 2]));
		f.vertexIndex = glm::vec3(shapes[i].mesh.positions[shapes[i].mesh.indices[v] * 3 + 0],
					  shapes[i].mesh.positions[shapes[i].mesh.indices[v] * 3 + 1],
					  shapes[i].mesh.positions[shapes[i].mesh.indices[v] * 3 + 2]);
	      }
	    if (shapes[i].mesh.normals.size() > 0)
	      {
		normals.push_back(glm::vec3(shapes[i].mesh.normals[shapes[i].mesh.indices[v] * 3 + 0],
					    shapes[i].mesh.normals[shapes[i].mesh.indices[v] * 3 + 1],
					    shapes[i].mesh.normals[shapes[i].mesh.indices[v] * 3 + 2]));
		f.normalIndex = glm::vec3(shapes[i].mesh.normals[shapes[i].mesh.indices[v] * 3 + 0],
				      shapes[i].mesh.normals[shapes[i].mesh.indices[v] * 3 + 1],
				      shapes[i].mesh.normals[shapes[i].mesh.indices[v] * 3 + 2]);
	      }
	    if (shapes[i].mesh.texcoords.size() > 0)
	      {
		texCoord.push_back(glm::vec2(shapes[i].mesh.texcoords[shapes[i].mesh.indices[v] * 2 + 0],
					     shapes[i].mesh.texcoords[shapes[i].mesh.indices[v] * 2 + 1]));
		f.texCoordIndex = glm::vec2(shapes[i].mesh.texcoords[shapes[i].mesh.indices[v] * 2 + 0],
					    shapes[i].mesh.texcoords[shapes[i].mesh.indices[v] * 2 + 1]);
	      }
	    faces.push_back(f);
	  }
      }

    // GLuint				vertexBuffer;

    // glGenBuffers(1, &vertexBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
    // glBufferData(GL_ARRAY_BUFFER, vertex.size() * sizeof(glm::vec3), &vertex[0], GL_STATIC_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);

    // GLuint				uvBuffer;

    // glGenBuffers(1, &uvBuffer);
    // glBindBuffer(GL_ARRAY_BUFFER, uvBuffer);
    // glBufferData(GL_ARRAY_BUFFER, texCoord.size() * sizeof(glm::vec2), &texCoord[0], GL_STATIC_DRAW);
    // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // return new ObjModelMedia(vertexBuffer, uvBuffer, vertex.size(), file.getFileName(), force);
    return new ObjModelMedia(vertex, texCoord, normals, faces, file.getFileName(), force);
  }
  virtual void				save(const ObjModelMedia *, const std::string &name)
  {
    throw LoadingFailed(name, "ObjLoader doesn't support SAVE.");
  }
};

#endif					// __OBJ_LOADER_HH__

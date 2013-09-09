#ifndef					__MESH_HH__
# define				__MESH_HH__

#include				"ObjModelMedia.hpp"

class					Shader;

class					Mesh
{
private:
  ObjModelMediaPtr			model_;
  Shader				*shader_;
public:
  Mesh();
  ~Mesh();
  void					init(const std::string &fileName);
  void					operator=(Mesh & o);
  void					attachShader(Shader &shader);
  void					render(GLuint shaderId);
};

#endif					// __MESH_HH__

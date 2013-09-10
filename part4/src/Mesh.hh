#ifndef					__MESH_HH__
# define				__MESH_HH__

#include				"ObjModelMedia.hpp"
#include				"AObject.hpp"

class					Shader;

class					Mesh : public AObject
{
private:
  ObjModelMediaPtr			model_;
  Shader				*shader_;
public:
  Mesh();
  virtual ~Mesh();
  void					init(const std::string &fileName);
  void					operator=(Mesh & o);
  void					attachShader(Shader &shader);
  void					render(GLuint shaderId);
};

#endif					// __MESH_HH__

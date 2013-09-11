#ifndef					__MESH_HH__
# define				__MESH_HH__

#include				"ObjModelMedia.hpp"
#include				"AObject.hpp"
#include				"GBufferManager.hpp"

class					Shader;

class					Mesh : public AObject
{
protected:
  ObjModelMediaPtr			model_;
  Shader				*shader_;
public:
  Mesh();
  virtual ~Mesh();
  virtual void				init(const std::string &fileName);
  virtual void				operator=(Mesh & o);
  void					attachShader(Shader &shader);
  virtual void				render(GLuint shaderId);
};

#endif					// __MESH_HH__

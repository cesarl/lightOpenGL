#ifndef					__SHADER_HPP__
# define				__SHADER_HPP__

#include				<map>
#include				<list>
#include				"Uniforms.hh"
#include				"ShaderMedia.hpp"

class					Mesh;

class					Shader
{
private:
  std::list<Mesh*>			mesh_;
  GLuint				id_;
  ShaderMediaPtr			shaders_[2];
public:
  Shader();
  ~Shader();
  void					init(const std::string &vertex = "",
						     const std::string &fragment = "");
  void					operator=(Shader & o);
  GLuint				getId() const;
  void					setUniform(std::string const &name, Uniform &uniform);
  void					use();
  void					unuse();
  void					attach(Mesh *mesh);
  void					detach(Mesh *mesh);
  void					render();
  int					getUniformId(const std::string &name);
  int					getAttribId(const std::string &name);
};

#endif					// __SHADER_HPP__

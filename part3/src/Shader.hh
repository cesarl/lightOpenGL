#ifndef					__SHADER_HPP__
# define				__SHADER_HPP__

#include				<map>
#include				<list>
#include				"Uniforms.hh"
#include				"ShaderProgramMedia.hpp"

class					Mesh;

class					Shader
{
private:
  ShaderProgramMediaPtr			prgm_;
  std::map<std::string, Uniform*>	uniforms_;
  std::list<Mesh*>			mesh_;
public:
  Shader();
  ~Shader();
  void					init(const std::string &fileName);
  void					operator=(Shader & o);
  ShaderProgramMediaPtr			&getProgram();
  GLuint				getId();
  void					setUniform(std::string const &name, Uniform *uniform);
  void					use();
  void					unuse();
  void					attach(Mesh *mesh);
  void					detach(Mesh *mesh);
  void					render();
};

#endif					// __SHADER_HPP__

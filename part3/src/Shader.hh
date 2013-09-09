#ifndef					__SHADER_HPP__
# define				__SHADER_HPP__

#include				<map>
#include				"Uniforms.hh"
#include				"ShaderProgramMedia.hpp"

class					Shader
{
private:
  ShaderProgramMediaPtr			prgm_;
  std::map<std::string, Uniform*>	uniforms_;
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
};

#endif					// __SHADER_HPP__

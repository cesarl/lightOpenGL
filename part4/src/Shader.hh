#ifndef					__SHADER_HPP__
# define				__SHADER_HPP__

#include				<list>
#include				"Uniforms.hh"
#include				"ShaderMedia.hpp"

class					Mesh;

class					Shader
{
private:
  struct s_texture
  {
    GLuint				texture;
    GLuint				index;
    std::string				name;
    s_texture(GLuint _texture, GLuint _index, const std::string &_name) :
      texture(_texture),
      index(_index),
      name(_name)
    {}
  };

  unsigned int				pass_;
  std::list<Mesh*>			mesh_;
  GLuint				id_;
  ShaderMediaPtr			shaders_[2];
  std::list<s_texture>			textures_;
public:
  Shader(unsigned int pass = 0);
  ~Shader();
  void					init(const std::string &vertex = "",
						     const std::string &fragment = "");
  void					operator=(Shader & o);
  GLuint				getId() const;
  void					setUniform(std::string const &name, Uniform &uniform);
  void					setTexture(std::string const &name, GLuint index, GLuint texture);
  void					use();
  void					unuse();
  void					attach(Mesh *mesh);
  void					detach(Mesh *mesh);
  void					render();
  int					getUniformId(const std::string &name);
  int					getAttribId(const std::string &name);
  unsigned int				getPass() const;
};

#endif					// __SHADER_HPP__

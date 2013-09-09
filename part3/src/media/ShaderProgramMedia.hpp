#ifndef					__SHADER_PROGRAM_MEDIA_HH__
# define				__SHADER_PROGRAM_MEDIA_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<GL/glu.h>
#include				"Resource.hh"
#include				"Uniforms.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"
#include				"Vector3d.hh"

class					ShaderProgramMedia : public Resource
{
public:
  ShaderProgramMedia(GLuint id, std::string const & name, bool force) :
    Resource(name, force),
    id_(id)
  {
    shaders_[0] = 0;
    shaders_[1] = 0;
  }

  virtual void				operator=(ShaderProgramMedia & o)
  {
    id_ = o.id_;
    shaders_[0] = o.shaders_[0];
    shaders_[1] = o.shaders_[1];
    textures_ = o.textures_;
  }

  virtual ~ShaderProgramMedia()
  {
    if (id_ != 0)
      glDeleteProgram(id_);
  }

  void					add(GLuint shader)
  {
    if (shaders_[0] != 0)
      {
	if (shaders_[1] == 0)
	  {
	    shaders_[1] = shader;
	  }
      }
    else
      shaders_[0] = shader;
  }

  GLuint				getId() const
  {
    return id_;
  }

  void					use()
  {
    glUseProgram(id_);
  }

  void					unuse()
  {
    glUseProgram(0);
  }

  int					getUniformId(const std::string &name)
  {
    int					res;

    return glGetUniformLocation(id_, name.c_str());
    if (res < 0)
      {
	throw UniformLocationUnknown(name, gluErrorString(glGetError()));
      }
    return res;
  }

  int					getAttribId(const std::string &name)
  {
    int					res;

    return glGetAttribLocation(id_, name.c_str());
    if (res < 0)
      {
	throw AttribLocationUnknown(name, gluErrorString(glGetError()));
      }
    return res;
  }

  void					setUniform(std::string const &name, Uniform *uniform)
  {
    if (uniforms_[name])
      delete uniforms_[name];
    uniforms_[name] = uniform;
    uniform->init(name, id_);
    uniform->update();
  }

private:
  GLuint				id_;
  GLuint				shaders_[2];
  std::map<std::string, std::string> textures_;
  std::map<std::string, Uniform*>	uniforms_;
};

typedef					SmartPtr<ShaderProgramMedia, InternalRef> ShaderProgramMediaPtr;

#endif					// __SHADER_PROGRAM_MEDIA_HH__

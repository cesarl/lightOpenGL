#ifndef					__SHADER_MEDIA_HH__
# define				__SHADER_MEDIA_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<GL/glu.h>
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"
#include				"Vector3d.hh"

class					ShaderMedia : public Resource
{
public:
  ShaderMedia(GLuint id, std::string const & name, bool force) :
    Resource(name, force),
    id_(id)
  {
  }

  virtual void				operator=(ShaderMedia & o)
  {
    id_ = o.id_;
  }

  virtual ~ShaderMedia()
  {
    if (id_ != 0)
      glDeleteShader(id_);
  }

  GLuint				getId() const
  {
    return id_;
  }
private:
  GLuint				id_;
};

typedef					SmartPtr<ShaderMedia, InternalRef> ShaderMediaPtr;

#endif					// __SHADER_MEDIA_HH__

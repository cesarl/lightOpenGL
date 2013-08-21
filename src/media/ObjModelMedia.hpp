#ifndef					__OBJ_MODEL_MEDIA_HH__
# define				__OBJ_MODEL_MEDIA_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<GL/glu.h>
#include				<glm/glm.hpp>
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"
#include				"Vector3d.hh"

class					ObjModelMedia : public Resource
{
public:
  ObjModelMedia(GLuint vertices,
	   GLuint uvs,
	   unsigned int verticesNumber,
	   std::string const & name, bool force) :
    Resource(name, force),
    vertices_(vertices),
    uvs_(uvs),
    verticesNumber_(verticesNumber)
  {
  }

  virtual void				operator=(ObjModelMedia & o)
  {
    vertices_ = o.vertices_;
    uvs_ = o.uvs_;
    verticesNumber_ = o.verticesNumber_;
  }

  virtual ~ObjModelMedia()
  {
    glDeleteBuffers(1, &vertices_);
    glDeleteBuffers(1, &uvs_);
  }

  unsigned int				getVerticesNumber() const
  {
    return verticesNumber_;
  }

  GLuint				getVertexBuffer() const
  {
    return vertices_;
  }

  GLuint				getUvBuffer() const
  {
    return uvs_;
  }
private:
  GLuint			vertices_;
  GLuint			uvs_;
  unsigned int			verticesNumber_;
};

typedef					SmartPtr<ObjModelMedia, InternalRef> ObjModelMediaPtr;

#endif					// __OBJ_MODEL_MEDIA_HH__

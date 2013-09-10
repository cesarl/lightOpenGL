#ifndef					__OBJ_MODEL_MEDIA_HH__
# define				__OBJ_MODEL_MEDIA_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				<GL/glu.h>
#include				<glm/glm.hpp>
#include				"ResourceManager.hpp"
#include				"Resource.hh"
#include				"SmartPointer.hpp"
#include				"SmartPointerPolicies.hpp"
#include				"Vector3d.hh"
#include				"Shader.hh"

class					ObjModelMedia : public Resource
{
public:
  ObjModelMedia(GLuint vertices,
		GLuint uvs,
		GLuint normals,
		unsigned int verticesNumber,
		std::string const & name, bool force) :
    Resource(name, force),
    vertices_(vertices),
    uvs_(uvs),
    normals_(normals),
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
    glDeleteBuffers(1, &normals_);
  }

  void					render(GLuint shaderId)
  {
    glEnableVertexAttribArray(glGetAttribLocation(shaderId, "vertices"));
    glBindBuffer(GL_ARRAY_BUFFER, vertices_);
    glVertexAttribPointer(glGetAttribLocation(shaderId, "vertices"), 3, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(glGetAttribLocation(shaderId, "texcoord"));
    glBindBuffer(GL_ARRAY_BUFFER, uvs_);
    glVertexAttribPointer(glGetAttribLocation(shaderId, "texcoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);

    glEnableVertexAttribArray(glGetAttribLocation(shaderId, "normals"));
    glBindBuffer(GL_ARRAY_BUFFER, normals_);
    glVertexAttribPointer(glGetAttribLocation(shaderId, "normals"), 3, GL_FLOAT, GL_FALSE, 0, 0);

    glDrawArrays(GL_TRIANGLES, 0, verticesNumber_);
    glDisableVertexAttribArray(glGetAttribLocation(shaderId, "vertices"));
    glDisableVertexAttribArray(glGetAttribLocation(shaderId, "texcoord"));
    glDisableVertexAttribArray(glGetAttribLocation(shaderId, "normals"));
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
  GLuint			normals_;
  unsigned int			verticesNumber_;
};

typedef					SmartPtr<ObjModelMedia, InternalRef> ObjModelMediaPtr;

#endif					// __OBJ_MODEL_MEDIA_HH__

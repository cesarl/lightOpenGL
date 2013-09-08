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
    normals_(0),
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
    // glDeleteBuffers(1, &uvs_);
  }

  void					render(ShaderProgramMediaPtr &s, GLint textureId)
  {

    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, textureId);
    glUniform1i(glGetAttribLocation(s->getId(), "myTexture"), /*GL_TEXTURE*/0);

    glEnableVertexAttribArray(glGetAttribLocation(s->getId(), "vertices"));
    glBindBuffer(GL_ARRAY_BUFFER, vertices_);
    glVertexAttribPointer(glGetAttribLocation(s->getId(), "vertices"), 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(glGetAttribLocation(s->getId(), "texcoord"));
    glBindBuffer(GL_ARRAY_BUFFER, uvs_);
    glVertexAttribPointer(glGetAttribLocation(s->getId(), "texcoord"), 2, GL_FLOAT, GL_FALSE, 0, 0);
    glDrawArrays(GL_TRIANGLES, 0, verticesNumber_);
    glDisableVertexAttribArray(glGetAttribLocation(s->getId(), "vertices"));
    glDisableVertexAttribArray(glGetAttribLocation(s->getId(), "texcoord"));

    // glEnableVertexAttribArray(10);
    // // glBindBuffer(GL_ARRAY_BUFFER, vertices_);
    // GLfloat triangle_vertices[] = {
    //   -10.0,  10, 0,
    //   -10, -10, 0,
    //   10, -10, 0
    // };
    // // glVertexAttribPointer(10, 3, GL_FLOAT, GL_FALSE, 0, (void*)(0));

    // glVertexAttribPointer(glGetAttribLocation(s->getId(), "vertices"), 3, GL_FLOAT, GL_FALSE, 0, triangle_vertices);


    // glDrawArrays(GL_TRIANGLES, 0, 3);
    // // glBindBuffer(GL_ARRAY_BUFFER, 0);
    // glDisableVertexAttribArray(10);
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

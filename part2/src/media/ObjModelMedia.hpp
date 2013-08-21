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
#include				"Light.hpp"

class					ObjModelMedia : public Resource
{
public:
  struct				Face
  {
    glm::vec3				vertexIndex;
    glm::vec2				texCoordIndex;
    glm::vec3				normalIndex;
    glm::vec3				color;
  };

  ObjModelMedia(std::vector<glm::vec3> & vertex,
		std::vector<glm::vec2> & texCoords,
		std::vector<glm::vec3> & normals,
		std::vector<Face> & faces,
		std::string const & name, bool force) :
    Resource(name, force),
    vertex_(vertex),
    texCoords_(texCoords),
    normals_(normals),
    faces_(faces)
  {
  }

  virtual void				operator=(ObjModelMedia & o)
  {
    vertex_ = o.vertex_;
    texCoords_ = o.texCoords_;
    normals_ = o.normals_;
    faces_ = o.faces_;
  }

  void					preRender()
  {
    glPushMatrix();
    glScalef(100.0f,100.0f,100.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    for(unsigned int i = 0;i < faces_.size(); i++)
      {
	// glTexCoord2f(texCoords_[i].x, texCoords_[i].y);
	glVertex3f(vertex_[i].x, vertex_[i].y, vertex_[i].z);
      }
    glEnd();
    glPopMatrix();
  }


  void				addLight(Light & l)
  {
    glPushMatrix();
    glScalef(100.0f,100.0f,100.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(l.color.x, l.color.y, l.color.z);
    for(unsigned int i = 0;i < faces_.size(); i++)
      {
	glm::vec3 ltex= l.computeLightning(vertex_[i]);
	glMultiTexCoord2f(GL_TEXTURE0, ltex.x, ltex.y);
	glMultiTexCoord2f(GL_TEXTURE1, ltex.z, 0.5f);
	glVertex3f(vertex_[i].x, vertex_[i].y, vertex_[i].z);
      }
    glEnd();
    glPopMatrix();
  }

  void					render()
  {
    glPushMatrix();
    glScalef(100.0f,100.0f,100.0f);
    glBegin(GL_TRIANGLES);
    glColor3f(1,1,1);
    for(unsigned int i = 0;i < faces_.size(); i++)
      {
	glTexCoord2f(texCoords_[i].x, texCoords_[i].y);
	glVertex3f(vertex_[i].x, vertex_[i].y, vertex_[i].z);
      }
    glEnd();
    glPopMatrix();
  }


  virtual ~ObjModelMedia()
  {
    // glDeleteBuffers(1, &vertices_);
    // glDeleteBuffers(1, &uvs_);
  }

private:
  std::vector<glm::vec3>		vertex_;
  std::vector<glm::vec2>		texCoords_;
  std::vector<glm::vec3>		normals_;
  std::vector<Face>			faces_;
};

typedef					SmartPtr<ObjModelMedia, InternalRef> ObjModelMediaPtr;

#endif					// __OBJ_MODEL_MEDIA_HH__

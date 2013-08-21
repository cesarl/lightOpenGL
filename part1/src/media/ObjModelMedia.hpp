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

  void					render()
  {
    glPushMatrix();
    glScalef(100.0f,100.0f,100.0f);
    glBegin(GL_TRIANGLES);
    for(unsigned int i = 0;i < faces_.size(); i++)
      {
	glColor3f(faces_[i].color.x, faces_[i].color.y, faces_[i].color.z);
	glTexCoord2f(texCoords_[i].x, texCoords_[i].y);
	glVertex3f(vertex_[i].x, vertex_[i].y, vertex_[i].z);
faces_[i].color = glm::vec3(0);
      }
    glEnd();
    glPopMatrix();
  }

    void				addLight(Light & l)
    {
    for(unsigned int i = 0;i < faces_.size(); i++)
      {
faces_[i].color += l.computeLightning(vertex_[i], normals_[i]);
      }
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

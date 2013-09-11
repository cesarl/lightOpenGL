#ifndef					__LIGHT_POINT_HPP__
# define				__LIGHT_POINT_HPP__

#include				"Mesh.hh"

class					LightPoint : public Mesh
{
private:
  glm::vec3				color_;
public:
  LightPoint() : Mesh()
  {}

  virtual ~LightPoint()
  {}

  void					init(const std::string &fileName = "sphere.obj")
  {
    model_ = ResourceManager::getInstance().get<ObjModelMedia>(fileName);
  }

  void					setColor(const glm::vec3 & color)
  {
    color_ = color;
  }

  virtual void				operator=(LightPoint & o)
  {
    color_ = o.color_;
    Mesh::operator=(o);
  }

  // virtual void				render(GLuint shaderId)
  // {
  //   GBufferManager::getInstance().bindForWriting();
  //   model_->render(shaderId);
  //   glBindFramebuffer(GL_FRAMEBUFFER, 0);
  // }


};

#endif					// __MESH_HPP__

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

  virtual void				render(GLuint shaderId)
  {
    glEnable(GL_BLEND);
    glBlendEquation(GL_FUNC_ADD);
    glBlendFunc(GL_ONE, GL_ONE);

    GBufferManager::getInstance().bindForReading();
    glClear(GL_COLOR_BUFFER_BIT);
    
    model_->render(shaderId);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);
  }


};

#endif					// __MESH_HPP__

#ifndef					__LIGHT_POINT_HPP__
# define				__LIGHT_POINT_HPP__

#include				"AObject.hpp"
#include				"ObjModelMedia.hpp"
// #include				"Shader.hpp"

class					LightPoint : public AObject
{
private:
  // Shader				shader_;
  ObjModelMediaPtr			model_;
  glm::vec3				color_;
public:
  LightPoint()
  {}
  virtual ~LightPoint()
  {}
  void					init()
  {
    model_ = ResourceManager::getInstance().get<ObjModelMedia>("sphere.obj");
  }
  void					setColor(const glm::vec3 & color)
  {
    color_ = color;
  }
  void					operator=(LightPoint & o)
  {
    // shader = o.shader_;
    model_ = o.model_;
  }
};

#endif					// __MESH_HPP__

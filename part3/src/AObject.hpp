#ifndef					__AOBJECT_HPP__
# define				__AOBJECT_HPP__

#include				<glm/glm.hpp>
#include				<glm/gtc/type_ptr.hpp>
#include				<glm/gtc/matrix_transform.hpp>

class					AObject
{
public:
  AObject()
  {}

  virtual ~AObject()
  {}

  glm::mat4				&getTransform()
  {
    return transform_;
  }
  
protected:
  glm::mat4				transform_;

};

#endif				//__AOBJECT_HPP__

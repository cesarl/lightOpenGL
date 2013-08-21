#ifndef			__LIGHT_HPP__
# define		__LIGHT_HPP__

#include		<glm/glm.hpp>

struct			Light
{
  float			radius;
  glm::vec3		position;
  glm::vec3		color;
  glm::vec3		computeLightning(const glm::vec3 & _position)
  {
    glm::vec3 res = res;

    res = _position - position;
    res /= radius;
    res += 0.5f;
    return res;
  }
};

#endif			// __LIGHT_HPP__

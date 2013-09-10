#ifndef			__LIGHT_HPP__
# define		__LIGHT_HPP__

#include		<glm/glm.hpp>

struct			Light
{
  float			radius;
  glm::vec3		color;
  glm::vec3		position;
  glm::vec3		computeLightning(const glm::vec3 & _position, const glm::vec3 & normal)
  {
    glm::vec3 dist = position - _position;
    glm::vec3 res = color;
    dist = glm::normalize(dist);
    float attenuation = std::max<float>(0.0f, 1.0f - (glm::length(dist) / radius));

    dist *= normal;
    attenuation = attenuation * dist.x + attenuation * dist.y + attenuation * dist.z;
    attenuation = std::max<float>(0.0f, attenuation);

    res *= attenuation;
    return res;


    // glm::vec3 dist = position - _position;
    // glm::vec3 res = color;
    // float attenuation = 1.0f - (glm::length(dist) / radius);

    // dist = glm::normalize(dist);

    // attenuation = glm::dot(normal, dist);

    // res *= attenuation;
    // return res;
  }
};

#endif			// __LIGHT_HPP__

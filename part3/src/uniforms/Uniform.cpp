#include "Uniform.hh"

Uniform::Uniform(void)
{
}

Uniform::~Uniform(void)
{
}

/// init the Uniform
bool Uniform::init(std::string const &name, GLuint shader)
{
  _id = glGetUniformLocation(shader, reinterpret_cast<const GLchar*>(name.c_str()));
  if (glGetError() == GL_NO_ERROR)
    return (false);
  return (true);
}

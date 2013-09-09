#include "UniformMatrix4f.hh"

UniformMatrix4f::UniformMatrix4f(float *value)
{
  for (int i = 0; i < 16; ++i)
    _value[i] = value[i];
}

UniformMatrix4f::~UniformMatrix4f(void)
{
}

void UniformMatrix4f::update(void)
{
  glUniformMatrix4fv(_id, 1, GL_FALSE, _value);
}

/// setter for matrix uniform
void UniformMatrix4f::set(UniformMatrix4f const &setter)
{
  for (size_t index = 0; index < 16; ++index)
    _value[index] = setter._value[index];
  update();
}

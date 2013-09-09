#include "Uniform3f.hh"

Uniform3f::Uniform3f(float x, float y, float z)
 : _value({x, y, z})
{}

Uniform3f::~Uniform3f(void)
{
}

/// update the Uniform3f
void Uniform3f::update(void)
{
  glUniform3f(_id, _value[0], _value[1], _value[2]);
}

/// set the uniform
void Uniform3f::set(Uniform3f const &setter)
{
  _value[0] = setter._value[0];
  _value[1] = setter._value[1];
  _value[2] = setter._value[2];
  update();
}

#include "Uniform1f.hh"

Uniform1f::Uniform1f(float value)
  : _value(value)
{
}

Uniform1f::~Uniform1f(void)
{
}

/// update the Uniform1f
void Uniform1f::update(void)
{
  glUniform1f(_id, _value);
}

/// setter for Uniform 1 float
void Uniform1f::set(Uniform1f const &setter)
{
  _value = setter._value;
  update();
}

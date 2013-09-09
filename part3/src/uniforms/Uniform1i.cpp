#include "Uniform1i.hh"

Uniform1i::Uniform1i(GLuint value)
  : _value(value)
{
}

Uniform1i::~Uniform1i(void)
{
}

/// update the Uniform1i
void Uniform1i::update(void)
{
  glUniform1i(_id, _value);
}

/// setter for Uniform
void Uniform1i::set(Uniform1i const &setter)
{
  _value = setter._value;
  update();
}

#include "Uniform1ui.hh"

Uniform1ui::Uniform1ui(GLuint value)
  : _value(value)
{
}

Uniform1ui::~Uniform1ui(void)
{
}

/// Update the Uniform1ui
void Uniform1ui::update(void)
{
  glUniform1ui(_id, _value);
}

/// setter for the Uniform
void Uniform1ui::set(Uniform1ui const &setter)
{
  _value = setter._value;
  update();
}

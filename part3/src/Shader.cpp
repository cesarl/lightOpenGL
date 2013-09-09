#include				"ResourceManager.hpp"
#include				"Shader.hh"
#include				"ShaderManager.hpp"
#include				"Mesh.hh"

Shader::Shader()
{
  ShaderManager::getInstance().addShader(this);
}

Shader::~Shader()
{
  ShaderManager::getInstance().removeShader(this);
    if (id_ != 0)
      glDeleteProgram(id_);
}

void					Shader::init(const std::string &vertex,
						     const std::string &fragment)
{
  GLint					linkStatus = GL_TRUE;
  ShaderMediaPtr			shader1;
  ShaderMediaPtr			shader2;

  id_ = glCreateProgram();
  if (id_ == 0)
    throw LoadingFailed(vertex + " " + fragment, "Shader Program failed to create program.");

  std::cout << "prgm " << id_ << std::endl;

  if (vertex.size() > 0)
    {
      shader1 = ResourceManager::getInstance().get<ShaderMedia>(vertex);
      glAttachShader(id_, shader1->getId());
      std::cout << "vertex " << shader1->getId() << std::endl;
    }
  if (fragment.size() > 0)
    {
      shader2 = ResourceManager::getInstance().get<ShaderMedia>(fragment);
      glAttachShader(id_, shader2->getId());
      std::cout << "fragment " << shader2->getId() << std::endl;
    }

  glLinkProgram(id_);

  if (linkStatus != GL_TRUE)
    {
      GLint				l;
      glGetProgramiv(id_, GL_INFO_LOG_LENGTH, &l);
      std::string log(l + 1, '\0');
      glGetProgramInfoLog(id_, l, &l, &log[0]);
      std::cout << std::endl << log;
      throw LoadingFailed(vertex + " " + fragment, "ShaderProgramLoader failed to link program.\n");
    }
}

void					Shader::operator=(Shader & o)
{
  id_ = o.id_;
  shaders_[0] = o.shaders_[0];
  shaders_[1] = o.shaders_[1];
}

GLuint					Shader::getId() const
{
  return id_;
}

void					Shader::setUniform(std::string const &name, Uniform &uniform)
{
  uniform.init(name, getId());
  uniform.update();
}

void					Shader::setTexture(std::string const &name, GLuint index, GLuint texture)
{
  textures_.push_back(s_texture(texture, index, name));
}

void					Shader::use()
{
  glUseProgram(id_);
}

void					Shader::unuse()
{
  glUseProgram(0);
}

void					Shader::attach(Mesh *mesh)
{
  mesh_.push_back(mesh);
}

void					Shader::detach(Mesh *mesh)
{
  mesh_.remove(mesh);
}

void					Shader::render()
{
  for (std::list<s_texture>::iterator i = textures_.begin();
       i != textures_.end();
       ++i)
    {
      glActiveTexture(GL_TEXTURE0 + i->index);
      glBindTexture(GL_TEXTURE_2D, i->texture);
      glUniform1i(getUniformId(i->name), i->index);
    }

  for (std::list<Mesh*>::iterator i = mesh_.begin();
       i != mesh_.end();
       ++i)
    {
      (*i)->render(getId());
    }
}

int					Shader::getUniformId(const std::string &name)
{
  int					res;

  return glGetUniformLocation(id_, name.c_str());
  if (res < 0)
    {
      throw UniformLocationUnknown(name, gluErrorString(glGetError()));
    }
  return res;
}

int					Shader::getAttribId(const std::string &name)
{
  int					res;

  return glGetAttribLocation(id_, name.c_str());
  if (res < 0)
    {
      throw AttribLocationUnknown(name, gluErrorString(glGetError()));
    }
  return res;
}

#include				"Shader.hh"
#include				"ResourceManager.hpp"
#include				"ShaderManager.hpp"

Shader::Shader()
{
  ShaderManager::getInstance().addShader(this);
}

Shader::~Shader()
{
  std::map<std::string, Uniform*>::iterator it;

  it = uniforms_.begin();
  while (it != uniforms_.end())
    {
      delete it->second;
      ++it;
    }
  uniforms_.clear();
  ShaderManager::getInstance().removeShader(this);
}

void					Shader::init(const std::string &fileName)
{
  prgm_ = ResourceManager::getInstance().get<ShaderProgramMedia>(fileName);
}

void					Shader::operator=(Shader & o)
{
  prgm_ = o.prgm_;
}

ShaderProgramMediaPtr			&Shader::getProgram()
{
  return prgm_;
}

GLuint					Shader::getId()
{
  if (prgm_.hasDataSet())
    return prgm_->getId();
  return 0;
}

void					Shader::setUniform(std::string const &name, Uniform *uniform)
{
  if (uniforms_[name])
    delete uniforms_[name];
  uniforms_[name] = uniform;
  uniform->init(name, getId());
  uniform->update();
}

void					Shader::use()
{
  prgm_->use();
}

void					Shader::unuse()
{
  prgm_->unuse();
}

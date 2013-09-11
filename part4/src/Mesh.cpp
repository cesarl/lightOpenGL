#include				"ResourceManager.hpp"
#include				"Mesh.hh"
#include				"Shader.hh"

Mesh::Mesh() :
  shader_(NULL)
{}

Mesh::~Mesh()
{
  if (shader_)
    shader_->detach(this);
}

void					Mesh::init(const std::string &fileName)
{
  model_ = ResourceManager::getInstance().get<ObjModelMedia>(fileName);
}

void					Mesh::operator=(Mesh & o)
{
  model_ = o.model_;
  shader_ = o.shader_;
}

void					Mesh::attachShader(Shader &shader)
{
  if (shader_)
    shader_->detach(this);
  shader_ = &shader;
  shader.attach(this);
}

void					Mesh::render(GLuint shaderId)
{

  GBufferManager::getInstance().bindForWriting();
  model_->render(shaderId);
  glBindFramebuffer(GL_FRAMEBUFFER, 0);
}

#ifndef				__SHADER_NANAGER_HPP__
# define			__SHADER_NANAGER_HPP__

#include			<map>
#include			<algorithm>
#include			"Singleton.hpp"
#include			"Shader.hh"
#include			"LightPoint.hpp"
#include			"Camera.hpp"

// pour donner l acces a la camera
// crado, provisoire
#include			"EventManager.hpp"

class				ShaderManager : public Singleton<ShaderManager>
{
private:
  std::multimap<unsigned int, Shader*>	shaders_;
public:
  friend class Singleton<ShaderManager>;

  virtual ~ShaderManager()
  {}

  void				addShader(Shader *shader, unsigned int pass)
  {
    shaders_.insert(std::pair<unsigned int, Shader*>(pass, shader));
  }

  void				removeShader(Shader *shader)
  {
    shaders_.erase(shader->getPass());
  }

  void				render()
  {
    std::multimap<unsigned int, Shader*>::iterator it;
    UniformMatrix4f		matrix(glm::value_ptr(camera.getVp()));

    // I clear GBuffer before drawing on it
    GBufferManager::getInstance().bindForWriting();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    it = shaders_.begin();
    while (it != shaders_.end())
      {
	it->second->use();
	it->second->setUniform("matrix", matrix);
	it->second->render();
	it->second->unuse();
	++it;
      }
  }
};

#endif				//__SHADER_NANAGER_HPP__

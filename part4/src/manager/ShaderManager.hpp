#ifndef				__SHADER_NANAGER_HPP__
# define			__SHADER_NANAGER_HPP__

#include			<list>
#include			<algorithm>
#include			"Singleton.hpp"
#include			"Shader.hh"
#include			"LightPoint.hpp"
#include			"Camera.hpp"
#include			"GBufferManager.hpp"

// pour donner l acces a la camera
// crado, provisoire
#include			"EventManager.hpp"

class				ShaderManager : public Singleton<ShaderManager>
{
private:
  std::list<Shader*>		shaders_;
  std::list<LightPoint*>	lightPoints_;
public:
  friend class Singleton<ShaderManager>;

  virtual ~ShaderManager()
  {}

  void				addShader(Shader *shader)
  {
    shaders_.push_back(shader);
  }

  void				removeShader(Shader *shader)
  {
    shaders_.remove(shader);
  }

  void				addLightPoint(LightPoint *lightPoint)
  {
    lightPoints_.push_back(lightPoint);
  }

  void				removeLightPoint(LightPoint *lightPoint)
  {
    lightPoints_.remove(lightPoint);
  }

  void				render()
  {
    std::list<Shader*>::iterator it;
    UniformMatrix4f		matrix(glm::value_ptr(camera.getVp()));

    // I clear GBuffer before drawing on it
    GBufferManager::getInstance().bindForWriting();
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glBindFramebuffer(GL_FRAMEBUFFER, 0);

    it = shaders_.begin();
    while (it != shaders_.end())
      {
	GBufferManager::getInstance().bindForWriting();
	(*it)->use();
	(*it)->setUniform("matrix", matrix);
	(*it)->render();
	glBindFramebuffer(GL_FRAMEBUFFER, 0);
	(*it)->unuse();
	++it;
      }
  }
};

#endif				//__SHADER_NANAGER_HPP__

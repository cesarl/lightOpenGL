#ifndef				__SHADER_NANAGER_HPP__
# define			__SHADER_NANAGER_HPP__

#include			<list>
#include			<algorithm>
#include			"Singleton.hpp"
#include			"Shader.hh"
#include			"Camera.hpp"

// pour donner l acces a la camera
// crado, provisoire
#include			"EventManager.hpp"

class				ShaderManager : public Singleton<ShaderManager>
{
private:
  std::list<Shader*>		list_;
public:
  friend class Singleton<ShaderManager>;

  virtual ~ShaderManager()
  {}

  void				addShader(Shader *shader)
  {
    list_.push_back(shader);
  }

  void				removeShader(Shader *shader)
  {
    list_.remove(shader);
  }

  void				render()
  {
    std::list<Shader*>::iterator it;
    // glm::mat4			&matrix = camera.getMvp();

    it = list_.begin();
    while (it != list_.end())
      {
	(*it)->use();
	// (*it)->setUniform("matrix", UniformMatrix4f(glm::value_ptr(matrix)));
	(*it)->render();
	(*it)->unuse();
	++it;
      }
  }
};

#endif				//__SHADER_NANAGER_HPP__

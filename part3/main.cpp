#include				<glm/glm.hpp>
#include				<glm/gtc/matrix_transform.hpp>

#include				"Logger.hpp"

#include				"ImageLoader.hpp"
#include				"ShaderLoader.hpp"
#include				"ShaderProgramLoader.hpp"
#include				"ObjLoader.hpp"

#include				"MediaManager.hpp"
#include				"ResourceManager.hpp"
#include				"MainManager.hpp"
#include				"ShaderManager.hpp"
#include				"Camera.hpp"

#include				"Light.hpp"
#include				"Shader.hh"
#include				"Mesh.hh"
#include				"GBufferManager.hpp"

#include				<exception>
Mesh					goose;
Mesh					cat;
Mesh					eagle;

Shader					gooseShader;
Shader					catShader;
Shader					eagleShader;

void					update(float time, const ALLEGRO_EVENT &ev)
{
  camera.update(time, ev);
}

void					draw(float time, const ALLEGRO_EVENT &ev)
{
  ShaderManager::getInstance().render();
  (void)ev;
  (void)time;
}

int					main()
{
  ////////////////////
  // initialisation //
  ////////////////////

  if (!MainManager::getInstance().init())
    return 0;
  if (!MainManager::getInstance().launch(1344, 704))
    return 0;

  //////////
  // main //
  //////////

  MediaManager::getInstance().registerLoader(new ImageLoader, ".jpg,.png,.jpeg,.tga,.tif");
  MediaManager::getInstance().registerLoader(new ShaderLoader, ".vert,.pix");
  MediaManager::getInstance().registerLoader(new ShaderProgramLoader, ".prgm");
  MediaManager::getInstance().registerLoader(new ObjLoader, ".obj");
  MediaManager::getInstance().addSearchPath("./assets/imgs/");
  MediaManager::getInstance().addSearchPath("./assets/shaders/");
  MediaManager::getInstance().addSearchPath("./assets/models/");

  EventManager::getInstance().setDrawLoop(draw);
  EventManager::getInstance().setUpdateLoop(update);

  // GBufferManager::getInstance().init(1344, 704);

  try
    {

      goose.init("goose.obj");
      cat.init("cat.obj");
      eagle.init("eagle.obj");

      gooseShader.init("deferred.prgm");
      gooseShader.use();
      gooseShader.setUniform("matrix", new UniformMatrix4f(glm::value_ptr(camera.getMvp())));
      gooseShader.setUniform("myTexture", new Uniform1ui(ResourceManager::getInstance().get<ImageMedia>("goose.jpg")->getTexture()));
      gooseShader.unuse();

      catShader.init("deferred.prgm");
      catShader.use();
      catShader.setUniform("matrix", new UniformMatrix4f(glm::value_ptr(camera.getMvp())));
      catShader.setUniform("myTexture", new Uniform1ui(ResourceManager::getInstance().get<ImageMedia>("cat.tga")->getTexture()));
      catShader.unuse();

      eagleShader.init("deferred.prgm");
      eagleShader.use();
      eagleShader.setUniform("matrix", new UniformMatrix4f(glm::value_ptr(camera.getMvp())));
      eagleShader.setUniform("myTexture", new Uniform1ui(ResourceManager::getInstance().get<ImageMedia>("eagle.jpg")->getTexture()));
      eagleShader.unuse();

      goose.attachShader(gooseShader);
      cat.attachShader(catShader);
      eagle.attachShader(eagleShader);
// ResourceManager::getInstance().get<ImageMedia>("eagle.jpg")->getTexture()

      EventManager::getInstance().play();
    }
  catch (const std::exception &e)
    {
      ILogger::log(e.what());
    }
  EventManager::getInstance().uninit();
  // GBufferManager::getInstance().uninit();
  return 0;
}

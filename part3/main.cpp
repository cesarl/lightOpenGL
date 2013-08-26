#include				<glm/glm.hpp>

#include				"Logger.hpp"

#include				"ImageLoader.hpp"
#include				"ShaderLoader.hpp"
#include				"ShaderProgramLoader.hpp"
#include				"ObjLoader.hpp"

#include				"MediaManager.hpp"
#include				"ResourceManager.hpp"
#include				"MainManager.hpp"
#include				"Camera.hpp"

#include				"Light.hpp"
#include				"GBufferManager.hpp"

#include				<exception>
ObjModelMediaPtr			model;
ObjModelMediaPtr			cat;

void					update(float time, const ALLEGRO_EVENT &ev)
{
  camera.input(time, ev);

}

void					draw(float time, const ALLEGRO_EVENT &ev)
{
  camera.update(time, ev);

  // ShaderProgramMediaPtr s = ResourceManager::getInstance().get<ShaderProgramMedia>("DirectionalLight.prgm");
  // glUseProgram(s->getId());

  glBindTexture(GL_TEXTURE_2D, ResourceManager::getInstance().get<ImageMedia>("goose.jpg")->getTexture());
  model->render();
  glBindTexture(GL_TEXTURE_2D, ResourceManager::getInstance().get<ImageMedia>("cat.tga")->getTexture());
  glPushMatrix();
  glTranslatef(50, 0, -50);
  cat->render();
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);
  // glUseProgram(0);
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

  MediaManager::getInstance().registerLoader(new ImageLoader, ".jpg,.png,.jpeg,.tga");
  MediaManager::getInstance().registerLoader(new ShaderLoader, ".vert,.pix");
  MediaManager::getInstance().registerLoader(new ShaderProgramLoader, ".prgm");
  MediaManager::getInstance().registerLoader(new ObjLoader, ".obj");
  MediaManager::getInstance().addSearchPath("./assets/imgs/");
  MediaManager::getInstance().addSearchPath("./assets/shaders/");
  MediaManager::getInstance().addSearchPath("./assets/models/");

  EventManager::getInstance().setDrawLoop(draw);
  EventManager::getInstance().setUpdateLoop(update);

  GBufferManager::getInstance().init(1344, 704);

  try
    {
      model = ResourceManager::getInstance().get<ObjModelMedia>("goose.obj");
      cat = ResourceManager::getInstance().get<ObjModelMedia>("cat.obj");
      EventManager::getInstance().play();
    }
  catch (const std::exception &e)
    {
      ILogger::log(e.what());
    }
  return 0;
}

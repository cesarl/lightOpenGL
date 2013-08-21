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

#include				<exception>

ObjModelMediaPtr			model;
ObjModelMediaPtr			cat;

Light					light1;
Light					light2;
Light					light3;

void					update(float time, const ALLEGRO_EVENT &ev)
{
  camera.input(time, ev);

}

void					draw(float time, const ALLEGRO_EVENT &ev)
{
  camera.update(time, ev);

  ShaderProgramMediaPtr s = ResourceManager::getInstance().get<ShaderProgramMedia>("basic.prgm");
  // glUseProgram(s->getId());

  glBindTexture(GL_TEXTURE_2D, ResourceManager::getInstance().get<ImageMedia>("goose.jpg")->getTexture());
  model->addLight(light1);
  model->addLight(light2);
  model->addLight(light3);
  model->render();
  glBindTexture(GL_TEXTURE_2D, ResourceManager::getInstance().get<ImageMedia>("cat.tga")->getTexture());
  cat->addLight(light1);
  cat->addLight(light2);
  cat->addLight(light3);
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

  light1.radius = 100;
  light1.color = glm::vec3(0.7, 0.5, 0);
  light1.position = glm::vec3(5, 5, 0);
  light2.radius = 100;
  light2.color = glm::vec3(0.1, 0.3, 0.8);
  light2.position = glm::vec3(-5, -5, 0);
  light3.radius = 50;
  light3.color = glm::vec3(1, 1, 1);
  light3.position = glm::vec3(0, -10, 2);

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

#include				"Logger.hpp"

#include				"ImageLoader.hpp"
#include				"ShaderLoader.hpp"
#include				"ObjLoader.hpp"

#include				"MediaManager.hpp"
#include				"ResourceManager.hpp"
#include				"MainManager.hpp"
#include				"ShaderManager.hpp"
#include				"Camera.hpp"

#include				"Light.hpp"
#include				"Shader.hh"
#include				"Mesh.hh"
// #include				"GBufferManager.hpp"

#include				<exception>


Mesh					goose;
Mesh					cat;
Mesh					barrel;

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
  MediaManager::getInstance().registerLoader(new ObjLoader, ".obj");
  MediaManager::getInstance().addSearchPath("./assets/imgs/");
  MediaManager::getInstance().addSearchPath("./assets/shaders/");
  MediaManager::getInstance().addSearchPath("./assets/models/");

  EventManager::getInstance().setDrawLoop(draw);
  EventManager::getInstance().setUpdateLoop(update);

  // GBufferManager::getInstance().init(1344, 704);

      Shader					gooseShader;
      Shader					catShader;
      Shader					barrelShader;

      {
	goose.init("goose.obj");
	cat.init("cat.obj");
	barrel.init("barrel.obj");

	gooseShader.init("phong.vert", "phong.pix");
	gooseShader.setTexture("myTexture",
			       1,
			       ResourceManager::getInstance().get<ImageMedia>("goose.jpg")->getTexture());


	catShader.init("bump.vert", "bump.pix");
	catShader.setTexture("myTexture",
			       0,
			       ResourceManager::getInstance().get<ImageMedia>("cat.tga")->getTexture());
	catShader.setTexture("normalTexture",
			       1,
			       ResourceManager::getInstance().get<ImageMedia>("cat_norm.tga")->getTexture());

	barrelShader.init("bump.vert", "bump.pix");
	barrelShader.setTexture("myTexture",
			       0,
			       ResourceManager::getInstance().get<ImageMedia>("barrel.jpg")->getTexture());
	barrelShader.setTexture("normalTexture",
			       1,
			       ResourceManager::getInstance().get<ImageMedia>("barrelNormal.jpg")->getTexture());

	goose.attachShader(gooseShader);
	cat.attachShader(catShader);
	barrel.attachShader(barrelShader);

	goose.getTransform() = glm::translate(goose.getTransform(), glm::vec3(1, 0, 0));	
	cat.getTransform() = glm::translate(cat.getTransform(), glm::vec3(-1, 0, 0));	
	barrel.getTransform() = glm::translate(barrel.getTransform(), glm::vec3(0, 0, 1));
	barrel.getTransform() = glm::scale(0.4, 0.4, 0.4);
      }

  try
    {

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

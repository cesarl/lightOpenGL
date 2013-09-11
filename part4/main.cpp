#include				"Logger.hpp"

#include				"ImageLoader.hpp"
#include				"ShaderLoader.hpp"
#include				"ObjLoader.hpp"

#include				"MediaManager.hpp"
#include				"ResourceManager.hpp"
#include				"MainManager.hpp"
#include				"ShaderManager.hpp"
#include				"Camera.hpp"

#include				"Shader.hh"
#include				"Mesh.hh"
#include				"GBufferManager.hpp"
#include				"LightPoint.hpp"

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

  GBufferManager::getInstance().bindForReading();

  GLint HalfWidth = (GLint)(1334 / 2.0f);
  GLint HalfHeight = (GLint)(704 / 2.0f);
  GLint w = 1334;
  GLint h = 704;
        
  GBufferManager::getInstance().setReadBuffer(GBufferManager::GB_TEXTURE_TYPE_POSITION);
  glBlitFramebuffer(0, 0, 1334, 704, 0, 0, HalfWidth, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

  GBufferManager::getInstance().setReadBuffer(GBufferManager::GB_TEXTURE_TYPE_DIFFUSE);
  glBlitFramebuffer(0, 0, 1334, 704, 0, HalfHeight, HalfWidth, h, GL_COLOR_BUFFER_BIT, GL_LINEAR);

  GBufferManager::getInstance().setReadBuffer(GBufferManager::GB_TEXTURE_TYPE_NORMAL);
  glBlitFramebuffer(0, 0, 1334, 704, HalfWidth, HalfHeight, w, h, GL_COLOR_BUFFER_BIT, GL_LINEAR);

  GBufferManager::getInstance().setReadBuffer(GBufferManager::GB_TEXTURE_TYPE_TEXCOORD);
  glBlitFramebuffer(0, 0, 1334, 704, HalfWidth, 0, w, HalfHeight, GL_COLOR_BUFFER_BIT, GL_LINEAR);

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

  GBufferManager::getInstance().init(1344, 704);

      Shader					gooseShader;
      Shader					catShader;
      Shader					barrelShader;

      {
	goose.init("goose.obj");
	cat.init("cat.obj");
	barrel.init("barrel.obj");

	gooseShader.init("deferred.vert", "deferred.pix");
	gooseShader.setTexture("myTexture",
			       1,
			       ResourceManager::getInstance().get<ImageMedia>("goose.jpg")->getTexture());

	catShader.init("deferred.vert", "deferred.pix");
	catShader.setTexture("myTexture",
			       0,
			       ResourceManager::getInstance().get<ImageMedia>("cat.tga")->getTexture());

	barrelShader.init("deferred.vert", "deferred.pix");
	barrelShader.setTexture("myTexture",
			       0,
			       ResourceManager::getInstance().get<ImageMedia>("barrel.jpg")->getTexture());

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
      EventManager::getInstance().play();
    }
  catch (const std::exception &e)
    {
      ILogger::log(e.what());
    }
  EventManager::getInstance().uninit();
  GBufferManager::getInstance().uninit();
  return 0;
}

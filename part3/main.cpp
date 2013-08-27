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

  ShaderProgramMediaPtr s = ResourceManager::getInstance().get<ShaderProgramMedia>("deferred.prgm");
  glUseProgram(s->getId());

  GBufferManager::getInstance().bindForWriting();

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);  

  glBindTexture(GL_TEXTURE_2D, ResourceManager::getInstance().get<ImageMedia>("goose.jpg")->getTexture());

  model->render();
  glBindTexture(GL_TEXTURE_2D, ResourceManager::getInstance().get<ImageMedia>("cat.tga")->getTexture());
  glPushMatrix();
  glTranslatef(50, 0, -50);

  cat->render();
  glPopMatrix();
  glBindTexture(GL_TEXTURE_2D, 0);

  glBindFramebuffer(GL_FRAMEBUFFER, 0);

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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

  glUseProgram(0);
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
  EventManager::getInstance().uninit();
  GBufferManager::getInstance().uninit();
  return 0;
}

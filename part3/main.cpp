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
#include				"Camera.hpp"

#include				"Light.hpp"
#include				"Shader.hh"
#include				"GBufferManager.hpp"

#include				<exception>
ObjModelMediaPtr			model;
ObjModelMediaPtr			cat;
ObjModelMediaPtr			eagle;
GLuint					vbo;
Shader					modelShader;

void					update(float time, const ALLEGRO_EVENT &ev)
{
  camera.update(time, ev);
}

void					draw(float time, const ALLEGRO_EVENT &ev)
{
  ShaderManager::getInstance().render();
  // modelShader.use();

  // model->render(modelShader);
  // eagle->render(modelShader);

  // modelShader.unuse();
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

  GLfloat triangle_vertices[] = {
    -10.0,  10, 4,
    -10, -10, 4,
    10, -10, 4
  };

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);

  try
    {
      ResourceManager::getInstance().get<ShaderProgramMedia>("deferred.prgm");
      model = ResourceManager::getInstance().get<ObjModelMedia>("goose.obj");
      cat = ResourceManager::getInstance().get<ObjModelMedia>("cat.obj");
      eagle = ResourceManager::getInstance().get<ObjModelMedia>("eagle.obj");

      modelShader.init("deferred.prgm");
      modelShader.use();
      modelShader.setUniform("matrix", new UniformMatrix4f(glm::value_ptr(camera.getMvp())));
      modelShader.setUniform("myTexture", new Uniform1ui(ResourceManager::getInstance().get<ImageMedia>("goose.jpg")->getTexture()));
      modelShader.unuse();
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

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
GLuint					vbo;

void					update(float time, const ALLEGRO_EVENT &ev)
{
  camera.input(time, ev);
}

void					draw(float time, const ALLEGRO_EVENT &ev)
{
  camera.update(time, ev);
  ShaderProgramMediaPtr s = ResourceManager::getInstance().get<ShaderProgramMedia>("basic.prgm");

  // glUseProgram(s->getId());

  glUniformMatrix4fv(glGetAttribLocation(s->getId(), "matrix"), 1, GL_FALSE, glm::value_ptr(camera.getMvp()));
  // std::cout << camera.getMvp()[0].x << " " <<  std::endl;


  glBegin(GL_QUADS);
  glColor3d(1,0,0);
  glVertex3f(-10,-10,1);
  glColor3d(1,1,0);
  glVertex3f(10,-10,1);
  glColor3d(0,1,0);
  glVertex3f(10,10,1);
  glColor3d(0,1,1);
  glVertex3f(-10,10,1);
  glEnd();

  glBegin(GL_QUADS);
  glColor3d(1,0,0);
  glVertex3f(-1,-1,1);
  glColor3d(1,1,0);
  glVertex3f(1,-1,-1);
  glColor3d(0,1,0);
  glVertex3f(1,1,1);
  glColor3d(0,1,1);
  glVertex3f(-1,1,1);
  glEnd();


  // glEnableVertexAttribArray(glGetAttribLocation(s->getId(), "vertices"));
  // glBindBuffer(GL_ARRAY_BUFFER, vbo);
  // glVertexAttribPointer(glGetAttribLocation(s->getId(), "vertices"), 3, GL_FLOAT, GL_FALSE, 0, 0);
  // glDrawArrays(GL_TRIANGLES, 0, 3);
  // glDisableVertexAttribArray(glGetAttribLocation(s->getId(), "vertices"));
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

  // GBufferManager::getInstance().init(1344, 704);

  GLfloat triangle_vertices[] = {
    -10.0,  10, 4,
    -10, -10, 4,
    10, -10, 4
  };

  glGenBuffers(1, &vbo);
  glBindBuffer(GL_ARRAY_BUFFER, vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(triangle_vertices), triangle_vertices, GL_STATIC_DRAW);
  glBindBuffer(GL_ARRAY_BUFFER, 0);

  try
    {
      ResourceManager::getInstance().get<ShaderProgramMedia>("deferred.prgm");
      model = ResourceManager::getInstance().get<ObjModelMedia>("goose.obj");
      // cat = ResourceManager::getInstance().get<ObjModelMedia>("cat.obj");
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

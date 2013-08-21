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
#include				<exception>

GLfloat cubeVertices[] =
  {
    1,1,1,
    -1,1,1,
    -1,-1,1,
    1,-1,1,
    1, 1, -1,
    -1, 1, -1,
    -1, -1, -1,
    1, -1, -1,
  };

GLfloat cubeColours[] =
  {
    1, 0, 0,
    0, 1, 0,
    0, 1, 0,
    1, 0, 0,
    0, 0, 1,
    1, 1, 0,
    1, 1, 0,
    0, 0, 1,
  };

GLubyte cubeIndices[] =
  {
    0, 1, 2, 3,
    0, 4, 7, 3,
    4, 5, 6, 7,
    1, 2, 6, 5,
    2, 3, 7, 6,
    0, 1, 5, 4
  };

glm::vec3 rotation;

void					update(float time, const ALLEGRO_EVENT &ev)
{
  camera.input(time, ev);
  rotation += glm::vec3(10.0f, 15.0f, 5.0f) / 100.0f;
}

void					draw(float time, const ALLEGRO_EVENT &ev)
{
  camera.update(time, ev);

  ShaderProgramMediaPtr s = ResourceManager::getInstance().get<ShaderProgramMedia>("basic.prgm");
  glUseProgram(s->getId());

  ////////////////////////////
  // myBlueTintUniform code //
  ////////////////////////////

  // static float blue = 0.0f;
  // glUniform1f(s->getUniformId("myBlueTint"), blue);
  // blue += 0.001f;
  // if (blue > 1.0f)
  //   blue = 0.0f;

  glPushMatrix();
  glTranslatef(0.0f, 0.0f, 0.0f);
  glScalef(30.0f, 30.0f, 30.0f);
  glRotatef(rotation.x, 1.0f, 0.0f, 0.0f);
  glRotatef(rotation.y, 0.0f, 1.0f, 0.0f);
  glRotatef(rotation.z, 0.0f, 0.0f, 1.0f);

  glEnableVertexAttribArray(s->getAttribId("myColor"));
  glVertexAttribPointer(s->getAttribId("myColor"),
		      3,
		      GL_FLOAT,
		      GL_TRUE,
		      0,
		      cubeColours);

  glDrawElements(GL_QUADS, 24, GL_UNSIGNED_BYTE, cubeIndices);

  glDisableVertexAttribArray(s->getAttribId("myColor"));

  glPopMatrix();
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

  MediaManager::getInstance().registerLoader(new ImageLoader, ".jpg,.png,.jpeg");
  MediaManager::getInstance().registerLoader(new ShaderLoader, ".vert,.pix");
  MediaManager::getInstance().registerLoader(new ShaderProgramLoader, ".prgm");
  MediaManager::getInstance().registerLoader(new ObjLoader, ".obj");
  MediaManager::getInstance().addSearchPath("./assets/imgs/");
  MediaManager::getInstance().addSearchPath("./assets/shaders/");
  MediaManager::getInstance().addSearchPath("./assets/models/");

  EventManager::getInstance().setDrawLoop(draw);
  EventManager::getInstance().setUpdateLoop(update);

  try
    {

      //////////////////////////////////////////////////////////////////////////////////
      // uncomment that 3 lines if you dont want to pass color as attribute to shader //
      //////////////////////////////////////////////////////////////////////////////////

      glEnableClientState(GL_VERTEX_ARRAY);
      // glEnableClientState(GL_COLOR_ARRAY);

      glVertexPointer(3, GL_FLOAT, 0, cubeVertices);
      // glColorPointer(3, GL_FLOAT, 0, cubeColours);

      EventManager::getInstance().play();

      // glDisableClientState(GL_COLOR_ARRAY);
      glDisableClientState(GL_VERTEX_ARRAY);
    }
  catch (const std::exception &e)
    {
      ILogger::log(e.what());
    }
  return 0;
}

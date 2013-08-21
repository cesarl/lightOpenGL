#ifndef					__SHADER_LOADER_HH__
# define				__SHADER_LOADER_HH__

#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				"Loader.hpp"
#include				"ResourceManager.hpp"
#include				"ShaderMedia.hpp"

class					ShaderLoader : public Loader<ShaderMedia>
{
public:
  ShaderLoader() : Loader<ShaderMedia>()
  {}

  virtual ~ShaderLoader()
  {}

  virtual ShaderMedia			*load(const File &file, bool force = false)
  {
    GLuint				id = 0;
    GLint				compileStatus = GL_TRUE;

    if (file.getExtension() == "vert")
      id = glCreateShader(GL_VERTEX_SHADER);
    else if (file.getExtension() == "pix")
      id = glCreateShader(GL_FRAGMENT_SHADER);
    if (id == 0 || !glIsShader(id))
      throw LoadingFailed(file.getFullName(), "ShaderLoader failed to create shader.");

    const std::string			source = file.getFileContent();
    const char				*sourceChar = source.c_str();

    glShaderSource(id, 1, &sourceChar, NULL);
    glCompileShader(id);

    glGetShaderiv(id, GL_COMPILE_STATUS, &compileStatus);

    if (compileStatus != GL_TRUE)
      {
	GLint				l;
	glGetShaderiv(id, GL_INFO_LOG_LENGTH, &l);
	std::string log(l + 1, '\0');
	glGetShaderInfoLog(id, l, &l, &log[0]);
	std::cout << std::endl << log;
	throw LoadingFailed(file.getFullName(), "ShaderLoader failed to compile shader.\n");
      }

    return new ShaderMedia(id, file.getFileName(), force);
  }
  virtual void				save(const ShaderMedia *, const std::string &name)
  {
    throw LoadingFailed(name, "ShaderLoader doesn't support SAVE.");
  }
};

#endif					// __SHADER_LOADER_HH__

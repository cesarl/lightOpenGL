#ifndef					__SHADER_PROGRAM_LOADER_HH__
# define				__SHADER_PROGRAM_LOADER_HH__

#include				<iostream>
#include				<fstream>
#include				<string>
#include				<vector>
#include				<map>
#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>
#include				"Loader.hpp"
#include				"ShaderMedia.hpp"
#include				"ShaderProgramMedia.hpp"

class					ShaderProgramLoader : public Loader<ShaderProgramMedia>
{
public:
  ShaderProgramLoader() : Loader<ShaderProgramMedia>()
  {}

  virtual ~ShaderProgramLoader()
  {}

  virtual ShaderProgramMedia		*load(const File &file, bool force = false)
  {
    GLuint				id;
    std::string				line;
    std::ifstream			myfile(file.getFullName().c_str());
    std::vector<std::string>		list;
std::map<std::string, std::string>	textures;
    ShaderMediaPtr shader;
    ShaderProgramMedia			*program;
    GLint				linkStatus = GL_TRUE;

    if (!myfile.is_open())
      {
	throw LoadingFailed(file.getFullName(), "ShaderProgramLoader failed to load shader.");
      }

    id = glCreateProgram();
    if (id == 0)
      throw LoadingFailed(file.getFullName(), "ShaderProgramLoader failed to create shader.");

    program = new ShaderProgramMedia(id, file.getFileName(), force);

    while (myfile.good())
      {
	std::getline(myfile, line);
	split(line, list, " ");
	if (list.size() != 2)
	  continue;
	if (list[0] == "VERTEX" || list[0] == "PIXEL")
	  {
	    shader = ResourceManager::getInstance().get<ShaderMedia>(list[1]);
	    glAttachShader(id, shader->getId());
	    program->add(shader->getId());
	  }
	else if (list[0] == "TEXTURES" && list.size() == 2)
	  {
	    std::vector<std::string>	sub;

	    split(list[1], sub, ",");
	    for (unsigned int i = 0; i < sub.size(); ++i)
	      {
		std::vector<std::string>	val;
		split(sub[i], val, ":");
		if (val.size() <= 1)
		  continue;
		textures.insert(std::pair<std::string, std::string>(val[0], val[1]));
	      }
	  }
      }    

    program->setTextures(textures);

    glLinkProgram(id);

    if (linkStatus != GL_TRUE)
      {
	GLint				l;
	glGetProgramiv(id, GL_INFO_LOG_LENGTH, &l);
	std::string log(l + 1, '\0');
	glGetProgramInfoLog(id, l, &l, &log[0]);
	std::cout << std::endl << log;
	throw LoadingFailed(file.getFullName(), "ShaderProgramLoader failed to link program.\n");
      }
    return program;
  }
  virtual void				save(const ShaderProgramMedia *, const std::string &name)
  {
    throw LoadingFailed(name, "ShaderProgramLoader doesn't support SAVE.");
  }
};

#endif					// __SHADER_PROGRAM_LOADER_HH__

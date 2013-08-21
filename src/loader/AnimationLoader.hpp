#ifndef					__ANIMATION_LOADER_HPP__
# define				__ANIMATION_LOADER_HPP__

#include				<iostream>
#include				<fstream>
#include				<string>
#include				"AnimationMedia.hpp"
#include				"strUtil.hpp"
#include				"Loader.hpp"
#include				"ResourceManager.hpp"

class					AnimationLoader : public Loader<AnimationMedia>
{
public:
  AnimationLoader() : Loader<AnimationMedia>()
  {}

  virtual ~AnimationLoader()
  {}

  virtual AnimationMedia		*load(const File &file, bool force = false)
  {
    std::string				line;
    std::ifstream			myfile(file.getFullName().c_str());

    if (!myfile.is_open())
      {
	throw LoadingFailed(file.getFullName(), "AnimationLoader failed to load animation.");
      }

    std::string				imgFile;
    int					stepNumber = 0;
    double				*timeSteps = NULL;
    bool				reverse = false;
    int					cycleNumber = 0;
    AnimationMedia::Coords		*coords = NULL;
    ImageMediaPtr			image;
    unsigned int			it = 0;
    std::vector<std::string>		list;

    while (myfile.good())
      {
	list.clear();
	std::getline(myfile, line);
	split(line, list, " ");
	if (list.size() < 2)
	  continue;
	else if (list[0] == "IMG")
	  {
	    imgFile = list[1];
	    image = ResourceManager::getInstance().get<ImageMedia>(imgFile);
	  }
	else if (list[0] == "STEPNB")
	  {
	    stepNumber = std::atoi(list[1].c_str());
	  }
	else if (list[0] == "REVERSE")
	  {
	    reverse = list[1] == "true" ? true : false;
	  }
	else if (list[0] == "CYCLENB")
	  {
	    cycleNumber = std::atoi(list[1].c_str());
	  }
	else if (list[0] == "TIMESTEP")
	  {
	    std::string s = list[1];
	    split(s, list,",");
	    timeSteps = new double[list.size()];
	    it = 0;
	    while (it < list.size())
	      {
		timeSteps[it] = std::atof(list[it].c_str());
		++it;
	      }
	  }
	else if (list[0] == "COORDS")
	  {
	    std::string s = list[1];
	    split(s, list,";,");
	    coords = new AnimationMedia::Coords[list.size() / 4];
	    it = 0;
	    while (it < list.size())
	      {
		coords[it / 4].pos.x = std::atof(list[it].c_str());
		coords[it / 4].pos.y = std::atof(list[it + 1].c_str());
		coords[it / 4].dim.x = std::atof(list[it + 2].c_str());
		coords[it / 4].dim.y = std::atof(list[it + 3].c_str());
		std::cout << coords[it / 4].pos.x << " "
			  << coords[it / 4].pos.y << " "
			  << coords[it / 4].dim.x << " "
			  << coords[it / 4].dim.y << std::endl;
		it += 4;
	      }
	  }
	(void)coords;
	(void)timeSteps;
	(void)force;
      }
    std::cout << file.getFileName() << " " << imgFile << " " << stepNumber << " " << reverse << " " << cycleNumber << std::endl;	myfile.close();
    return new AnimationMedia(image, timeSteps, stepNumber, reverse, cycleNumber, coords, file.getFileName(), force);
  }

  virtual void				save(const AnimationMedia *, const std::string &name)
  {
    throw LoadingFailed(name, "AnimationLoader doesn't support SAVE.");
  }

};

#endif					// __ANIMATION_LOADER_HPP__

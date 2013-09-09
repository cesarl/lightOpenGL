#ifndef UNIFORM_HH_
# define UNIFORM_HH_

# include <iostream>
#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>



class Uniform
{
public:
  Uniform(void);
  virtual ~Uniform();
    
  bool init(std::string const &name, GLuint shader);
       
  virtual void update(void) = 0;
protected:
  GLuint _id;
};

#endif /*!UNIFORM_HH_*/

#ifndef UNIFORM_HH_
# define UNIFORM_HH_

# include <iostream>
#include				<allegro5/allegro.h>
#include				<allegro5/allegro_opengl.h>



class Uniform
{
protected:
  Uniform(void);

  GLuint _id;
public:
  virtual ~Uniform();
    
  bool init(std::string const &name, GLuint shader);
       
  virtual void update(void) = 0;
};

#endif /*!UNIFORM_HH_*/

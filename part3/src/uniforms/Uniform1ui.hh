#ifndef UNIFORM1UI_HH_
# define UNIFORM1UI_HH_

# include "Uniform.hh"

class Uniform1ui : public Uniform
{
private:
  GLuint _value;

public:

  Uniform1ui(GLuint value);
  void set(Uniform1ui const &setter);
  virtual ~Uniform1ui(void);
  virtual void update(void);
};


#endif /*!UNIFORM1UI_HH_*/

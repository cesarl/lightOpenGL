#ifndef UNIFORM1I_HH_
# define UNIFORM1I_HH_

# include "Uniform.hh"

class Uniform1i : public Uniform
{
private:
  GLuint _value;

public:
  void set(Uniform1i const &setter);
  Uniform1i(GLuint value);
  virtual ~Uniform1i(void);    
  virtual void update(void);
};


#endif /*!UNIFORM1I_HH_*/

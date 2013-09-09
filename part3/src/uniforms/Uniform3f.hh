#ifndef UNIFORM3F_HH_
# define UNIFORM3F_HH_

# include "Uniform.hh"

class Uniform3f : public Uniform
{
private:
  float _value[3];

public:
  Uniform3f(float x, float y, float z);
  virtual ~Uniform3f(void);    
  virtual void update(void);
  void set(Uniform3f const &setter);
};


#endif /*!UNIFORM3F_HH_*/

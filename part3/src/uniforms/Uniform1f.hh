#ifndef UNIFORM1F_HH_
# define UNIFORM1F_HH_

# include "Uniform.hh"

class Uniform1f : public Uniform
{
private:
  float _value;

public:
  void set(Uniform1f const &setter);
  Uniform1f(float value);
  virtual ~Uniform1f(void);    
  virtual void update(void);
};

#endif /*!UNIFORM1F_HH_*/

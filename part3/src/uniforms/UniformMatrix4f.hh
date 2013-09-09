#ifndef UNIFORMMATRIX4F
# define UNIFORMMATRIX4F

# include "Uniform.hh"

struct UniformMatrix4f : public Uniform
{
  float _value[16];

  void set(UniformMatrix4f const &setter);
  UniformMatrix4f(float *value);
  virtual ~UniformMatrix4f(void);
  virtual void update(void);
};


#endif /*!UNIFORMMATRIX4F*/

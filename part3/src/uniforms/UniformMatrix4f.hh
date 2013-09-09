#ifndef UNIFORMMATRIX4F
# define UNIFORMMATRIX4F

# include "Uniform.hh"

class UniformMatrix4f : public Uniform
{
private:
  float _value[16];

public:
  void set(UniformMatrix4f const &setter);
  UniformMatrix4f(float *value);
  virtual ~UniformMatrix4f(void);
  virtual void update(void);
};


#endif /*!UNIFORMMATRIX4F*/

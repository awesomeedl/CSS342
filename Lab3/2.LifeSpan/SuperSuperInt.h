#include "SuperInt.h"

class SuperSuperInt : public SuperInt 
{
 public:
  SuperSuperInt(int init, const char *name);

  ~SuperSuperInt();

  const int& theValue(void);

 private:
  SuperSuperInt();

};




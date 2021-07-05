#include <iostream>
#include "SuperSuperInt.h"

using namespace std;

SuperSuperInt::SuperSuperInt(int init, const char *name) : SuperInt(init, name)
{
  cout << "Created a SuperSuperInt" << endl;
}

SuperSuperInt::~SuperSuperInt()
{
  cout << "Destroyed a SuperSuperInt" << endl;
}

const int& SuperSuperInt::theValue()
{
  cout << "Returning the myValue of SuperInt" << endl;
  return SuperInt::theValue();
}




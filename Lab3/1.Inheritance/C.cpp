/*
 *  C.cpp
 *  Inheritance Example
 *
 *  Created by Prof. Michael Stiber
 *  Modified by Yang Peng on 01/12/2018
 *
 */

#include "C.h"
#include <iostream>

using namespace std;

C::C()
{
  testDataC = 3.14;
  setN("unnamed C");
  cout << "Inside C::C() for object " << getN() << endl;
  cout << "testDataC: " << testDataC << endl;
}

C::C(string name, int data1, int data2, int dataB, double dataC) : 
  B(name, data1, data2, dataB) , 
  testDataC(dataC)
{
  cout << "Inside C::C(string) for object " << getN() << endl;
  cout << "testDataC: " << testDataC << endl;
}


C::~C()
{
  cout << "Inside C::~C() for object " << getN() << endl;
}



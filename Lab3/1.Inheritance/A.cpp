/*
 *  A.cpp
 *  Inheritance Example
 *
 *  Created by Prof. Michael Stiber
 *  Modified by Yang Peng on 01/12/2018
 *
 */

#include "A.h"
#include <iostream>

using namespace std;

A::A()
{
    n = "unnamed A";
    testData1 = 1;
    testData2 = 2;
    cout << "Inside A::A() for object " << n << endl;
    cout << "testData1: " << testData1 << " testData2: " << testData2 << endl;
}

A::A(string name, int testData1, int testData2) : n(name), testData1(testData1), testData2(testData2)
{
    cout << "Inside A::A(string) for object " << n << endl;
    cout << "testData1: " << testData1 << " testData2: " << testData2 << endl;
}


A::~A()
{
    cout << "Inside A::~A() for object " << n << endl;
}


void A::setN(const char* s)
{
  n = s;
}

string A::getN(void) const
{
  return n;
}



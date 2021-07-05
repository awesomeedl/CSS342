#pragma once

#include <string>
#include "MyClass.h"

using namespace std;

class MySubClass : public MyClass
{
public:
	// default constructor
    MySubClass();

    // copy constructor
    MySubClass(const MySubClass& orig);

	// destructor
    ~MySubClass();

    // assignment operator
    MySubClass& operator=(const MySubClass& rhs);

    void setData(int data);
    int getData() const;

private:
    int subClassData;
};


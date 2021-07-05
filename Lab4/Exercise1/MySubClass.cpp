#include "MySubClass.h"
#include <cassert>

using namespace std;

MySubClass::MySubClass()
{
    subClassData = 0;
}

MySubClass::MySubClass(const MySubClass& orig) : MyClass(orig)
{
    this->subClassData = orig.subClassData;
}

MySubClass& MySubClass::operator=(const MySubClass& rhs)
{
    if (this != &rhs) {
        MyClass::copy(rhs);
    }
    this->subClassData = rhs.subClassData;
    
    return *this;
}

MySubClass::~MySubClass()
{
}

void MySubClass::setData(int data) {
    subClassData = data;
}

int MySubClass::getData() const {
    return subClassData;
}


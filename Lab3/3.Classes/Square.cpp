/*
 *  Square.cpp
 *  Class-example
 *
 */

#include "Square.h"

void Square::setSize(int newSize)
{
   theSize = newSize;
}


int Square::getSize(void) const
{
   return theSize;
}

Square& Square::operator = (const Square& other)
{
	theSize = other.getSize();
	return *this;
   /* the square class needs this operator overload
   without a copy constructor, this is the function
   we use to copy squares
   Square a;
   Square b;
   a.setSize(3)
   b = a;
   */
}

bool Square::operator < (const Square& other)
{
   return (theSize < other.getSize());
}

ostream& operator<<(ostream &Out, const Square &sq) {
  Out << "Size: " << sq.theSize;
  return Out;
}
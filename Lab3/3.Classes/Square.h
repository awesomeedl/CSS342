/*
 *  Square.h
 *  Class-example
 *
 */

#ifndef SQUARE_H
#define SQUARE_H

#include <iostream>

using namespace std;

class Square {
   friend ostream &operator<<(ostream &Out, const Square &sq);
public:
   void setSize(int newSize);
   int getSize(void) const;
   Square& operator = (const Square&);
   /* the square class needs this operator overload
   without a copy constructor, this is the function
   we use to copy squares
   Square a;
   Square b;
   a.setSize(3)
   b = a;
   */
   bool operator < (const Square&);

private:
   int theSize;
   
};

#endif

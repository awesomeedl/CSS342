#include <iostream>
#include "Square.h"
#include "SquareContainer.h"

using namespace std;

int main (int argc, char * const argv[]) {
   SquareContainer c;
   
   for (int i = 0; i < 20; i++) {
      Square s;
      s.setSize(i);
      c.insertNext(s);
   }
   SquareContainer d(c); // copy
   SquareContainer e = c; // assignment

   try {
      for (int i = 0; i < 21; i++) {
         cout << "Square " << i << " size is " 
         << c.deleteLast().getSize() << endl;
      }
   }
   catch (SquareContainerException sqe) {
      cerr << sqe.what();
   }

   // Testing overloaded operators
   cout << endl;
   cout << "Testing the overloaded assignment operator..." << endl;
   SquareContainer x;
   SquareContainer y;

   for (int i = 0; i < 10; i++) {
      Square s;
      s.setSize(i);
      x.insertNext(s);
   }

   y = x;

   for (int i = 0; i < 10; i++) {
      cout << "x: " << x.deleteLast().getSize() << " y: " << y.deleteLast().getSize() << endl;
   }

   cout << "Done." << endl;
   
   // Testing Square stream operator
   cout << endl;
   cout << "Testing Square stream operator..." << endl;
   Square sq;
   sq.setSize(3);
   cout << sq << endl;
   cout << "Done." << endl;

   // Testing SquareContainer stream operator
   cout << endl;
   cout << "Testing SquareContainer stream operator..." << endl;
   SquareContainer z;

   for (int i = 0; i < 10; i++) {
      Square s;
      s.setSize(i);
      z.insertNext(s);
   }

   cout << z;
   cout << "Done." << endl;
    return 0;
}

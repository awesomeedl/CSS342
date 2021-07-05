#include "library.h"

#include <cassert>
#include <iostream>


using namespace std;

void test1() {
  Library Libs("UWB");
  Libs.addBook("Don Quixote");
  Libs.addBook("In Search of Lost Time");
  Libs.addBook("Ulysses");
  Libs.addBook("The Odyssey");
  Libs.listAllBooks();
  //added to test the overloaded operator
  cout << Libs;
  // should generate already in library message and return true
  bool Result = Libs.isInLibrary("The Odyssey");
  assert(Result);

  // cannot add book twice, result should be false
  Result = Libs.addBook("The Odyssey");
  assert(!Result);

  // test remove, result should be true
  Result = Libs.removeBook("The Odyssey");
  assert(Result);

  // not in library, result should be false
  Result = Libs.isInLibrary("The Odyssey");
  assert(!Result);

  // cannot remove twice, result should be false
  Result = Libs.removeBook("The Odyssey");
  assert(!Result);

  // additional test to test the << operator overload and listAllBooks
  cout << Libs;
  Libs.listAllBooks();
}

void test2() {
  Library L1("abc");
  L1.addBook("123");
  Library L2("def");
  L2.addBook("456");

  L1 += L2;
  cout << L2;
  cout << L1;
}

void testAll() {
  test1();
  test2();
  cout << "Successfully completed all tests." << endl;
}

int main() {
  testAll();
  return 0;
}
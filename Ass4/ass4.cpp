#include <cassert>
#include <iostream>

#include "skiplist.h"

using namespace std;

void test1() {
  // setting seed for easy testing
  srand(10000);
  SkipList Skp(5, 80);
  cout << boolalpha;
  Skp.add(3);
  Skp.add(5);
  Skp.add(vector<int>{1, 7, 9});
  // cannot add existing
  assert(!Skp.add(vector<int>{1, 7}));
  cout << Skp << endl;
  cout << "7 ? " << Skp.contains(7) << endl;
  cout << "3 ? " << Skp.contains(3) << endl;
  cout << "-100 ? " << Skp.contains(-100) << endl;
  cout << "100 ? " << Skp.contains(100) << endl;
  bool Result = Skp.remove(5);
  assert(Result);
  Result = Skp.remove(5);
  assert(!Result);
  cout << Skp << endl;
}

void test2() {
  SkipList Skp(1, 50);
  // Should be empty, not containing anything
  bool Result;
  Result = Skp.contains(20);
  assert(!Result);
  // Should be able to add 20, which does not exist already
  Result = Skp.add(20);
  assert(Result);
  // Should contain 20 after adding
  Result = Skp.contains(20);
  assert(Result);
  // Should not be able to add duplicate
  Result = Skp.add(20);
  assert(!Result);
  // Shuold be able to remove 20
  Result = Skp.remove(20);
  assert(Result);
  // Should not contain 20 after removing
  Result = Skp.contains(20);
  assert(!Result);
  // Should not be able to delete something twice
  Result = Skp.remove(20);
  assert(!Result);
  // Should be able to add if at least one does not have duplicate
  Result = Skp.add(vector<int>{1, 2, 3, 4, 20});
  assert(Result);
  // Should not be able to add if all are duplicate
  Result = Skp.add(vector<int>{1, 2, 3});
  assert(!Result);
  cout << "Test 2 finished." << endl;
}

int main() {

  test1();
  test2();
  cout << "Done." << endl;
  return 0;
}
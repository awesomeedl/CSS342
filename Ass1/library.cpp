//
// Created by XXXX on MM/DD/YYYY.
//
// Library class demonstrating partially filled arrays
// Can add/remove books from library
// findbooks in library


#include "library.h"
#include <iostream>

static const int MAX = 100;
string library[MAX];
int numberOfBooks;

// constructor with default name
Library::Library(const string &Name) {
  library[0] = Name;
  numberOfBooks = 1;
}

// destructor
// nothing on heap
Library::~Library() {
  // destructor
}

// true if book found in library
// uses a for loop to iterate through all the books
bool Library::isInLibrary(const string &BookName) const {
  for (int i = 0; i < numberOfBooks; i++)
  {
    if (library[i] == BookName) return true;
  }
  return false;
}

// add a new book
// return true if successful, false if
// book already in library
bool Library::addBook(const string &BookName) {
  // first uses isInLibrary to check if book is present
  if (isInLibrary(BookName)) return false;
  // setting the next available space as the new book
  library[numberOfBooks] = BookName;
  numberOfBooks++;
  return true;
}

// remove a book
// return true if successfully removed
// false if book not in library
bool Library::removeBook(const string &BookName) {
  for(int i = 0; i < numberOfBooks; i++)
  {
    if(library[i] == BookName)
    {
      // replacing the target book with the last book in the library
      library[i] = library[numberOfBooks - 1];
      numberOfBooks--;
      return true;
    }
  }
  return false;
}

// list all books
void Library::listAllBooks() const {
  // calls the overloaded << operator
  cout << *this;
}

// Overloading the << operator
ostream &operator<<(ostream &Out, const Library &Lib) {
  // for loop to iterate through all the items
  for(int i = 0; i < Lib.numberOfBooks; i++) {
    // sending each book to the Out stream
    Out << Lib.library[i] << " ";
  }
  Out << endl;
  return Out;
}

// Overloading the += operator
Library &operator+=(Library &Lib, const Library &OtherLib) {
  for(int i = 0; i < OtherLib.numberOfBooks; i++) {
    Lib.addBook(OtherLib.library[i]);
  }
  return Lib;
}
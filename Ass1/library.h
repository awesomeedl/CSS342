//
// Created by Yusuf Pisan on 3/26/18.
//

#ifndef ASS1_LIBRARY_H
#define ASS1_LIBRARY_H

#include <string>

// Only for class code, OK to use namespace
using namespace std;

// Library holds books - can add, remove and list books
class Library {
  // display all books in library
  friend ostream &operator<<(ostream &Out, const Library &Lib);
  friend Library &operator+=(Library &Lib, const Library &OtherLib);


public:
  // constructor with default name
  explicit Library(const string &Name);

  // destructor
  virtual ~Library();

  // add a new book
  // return true if successful, false if
  // book already in library
  bool addBook(const string &BookName);

  // remove a book
  // return true if successfully removed
  // false if book not in library
  bool removeBook(const string &BookName);

  // list all books
  void listAllBooks() const;

  // true if book found in library
  bool isInLibrary(const string &BookName) const;

private:
  // maximum number of books in the library
  static const int MAX = 100;
  // library with a maximum capacity of MAX
  string library[MAX];
  // the number of books that the library currently holds
  int numberOfBooks;


};

#endif  // ASS1_LIBRARY_H

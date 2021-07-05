/*
 *  Square.h
 *  Class-example
 *
 */

#ifndef SQUARE_H
#define SQUARE_H

template<class ItemType>
class Square {
	template<class T>
	friend std::ostream& operator<< (std::ostream&, const Square<T>&);
public:
	Square<ItemType> & operator=(const Square&);
	bool operator<(const Square<ItemType>&);
	void setSize(ItemType newSize);
	ItemType getSize(void) const;

private:
	ItemType theSize;
};
#include "Square.cpp"
#endif

//
// Created by Yusuf Pisan on 4/2/18.
//

#ifndef ASS2_TIMESPAN_H
#define ASS2_TIMESPAN_H

#include <cmath>
#include <iostream>

using namespace std;

class TimeSpan {
  friend ostream &operator<<(ostream &out, const TimeSpan &ts);

public:
  // constructor, this takes care of anything from 0 to 3 parameters, since
  // defaults are provided 
  explicit TimeSpan(double hour = 0, double minute = 0, double second = 0);

  // add
  TimeSpan operator+(const TimeSpan &ts) const;

  // subtract
  TimeSpan operator-(const TimeSpan &ts) const;

  // check equality
  bool operator==(const TimeSpan &ts) const;

  // check if not equal
  bool operator!=(const TimeSpan &ts) const;

  // multiply timespan by an unsigned number
  TimeSpan operator*(unsigned int number) const;

  // shorthand add
  void operator+=(const TimeSpan &ts);
  
  // shorthand subtract
  void operator-=(const TimeSpan &ts);

  // shorthand multiply
  void operator*=(unsigned int number);

  // check smaller than
  bool operator<(const TimeSpan &ts) const;

  // check larger than
  bool operator>(const TimeSpan &ts) const;

  // check smaller than and equal to
  bool operator<=(const TimeSpan &ts) const;

  // check larger than and equal to
  bool operator>=(const TimeSpan &ts) const;

  // hour component of timespan
  int getHour() const;

  // minute component of timespan
  int getMinute() const;

  // second component of timespan
  int getSecond() const;

  // true if timespan is 0 or larger
  bool isPositive() const;

private:
  // a temporary time that represents the whole timespan in seconds
  // only when calling the get functions and using << operator 
  // will then perform calculations to obtain the hours and 
  // minutes representation. It makes implementing arithmatic 
  // and comparison operators much easier since there is only one value
  int rawTime;
};

#endif // ASS2_TIMESPAN_H

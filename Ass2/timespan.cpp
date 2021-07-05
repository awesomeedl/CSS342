//
// Created by Yusuf Pisan on 4/2/18.
//

#include "timespan.h"

// Feeding a TimeSpan object to ostream, format should be H:MM:SS (0:00:00)
ostream &operator<<(ostream &out, const TimeSpan &ts) {
  // Temporary storing the components
  // Since we will check for a negative duration and add negative sign
  // before the hour component, all the components will be translated
  // to their absolute values to fit the formatting
  int hr = abs(ts.getHour());
  int min = abs(ts.getMinute());
  int sec = abs(ts.getSecond()); 
  // If the timeSpan is negative, append a negative sign before it
  if (!ts.isPositive()) { out << "-"; }
  out << hr << ":";
  // For formatting: If the minute is single digit, append "0" before it
  if (min < 10) { out << "0"; }
  out << min << ":";
  // For formatting: If the second is single digit, append "0" before it
  if (sec < 10) { out << "0"; }
  out << sec;
  return out; 
}

// constructor
TimeSpan::TimeSpan(double hour, double minute, double second) {
  // Instead of storing them separately, translate hour and minute into
  // seconds and store them into a single variable
  // decimals are rounded using cmath round to the nearest integer
  rawTime = static_cast<int>(round(hour * 3600 + minute * 60 + second));
}

// hour component
// since there is 3600 seconds in an hour, rawTime/3600 gives the hour component
int TimeSpan::getHour() const { return rawTime / 3600; }

// minute component
// (rawTime % 3600) gets the remainder after dividing out the hour component,
// further dividing it by 60 gives the minute component
int TimeSpan::getMinute() const { return (rawTime % 3600) / 60; }

// second component
// The remainder of first dividing by hour then by minute is the second component
int TimeSpan::getSecond() const { return (rawTime % 3600) % 60; }

// true if timespan is 0 or larger
bool TimeSpan::isPositive() const { return rawTime >= 0; }

// add
TimeSpan TimeSpan::operator+(const TimeSpan &ts) const {
  TimeSpan tsSum;
  // simply adds up the rawTime in both of the TimeSpan
  tsSum.rawTime = this->rawTime + ts.rawTime;
  return tsSum;
}

// subtract
TimeSpan TimeSpan::operator-(const TimeSpan &ts) const {
  TimeSpan tsSub;
  // similar to add, simply subtract the rawTime
  tsSub.rawTime = this->rawTime - ts.rawTime;
  return tsSub;
}

// multiply with an integer
TimeSpan TimeSpan::operator*(unsigned int number) const {
  TimeSpan tsLarge;
  // since rawTime is integer, we can just multiply it by number
  tsLarge.rawTime = this->rawTime * number;
  return tsLarge;
}

// equality ==
bool TimeSpan::operator==(const TimeSpan &ts) const { 
  // Two TimeSpan are equal same if the values of rawTime are equal
  return (this->rawTime == ts.rawTime); 
}

// inequality !=
bool TimeSpan::operator!=(const TimeSpan &ts) const { 
  // Reverse of equality
  return !(*this == ts); 
}

// The following overloads are added by the student
// shorthand add
void TimeSpan::operator+=(const TimeSpan &ts) {
  this->rawTime += ts.rawTime;
}

// shorthand subtract
void TimeSpan::operator-=(const TimeSpan &ts) {
  this->rawTime -= ts.rawTime;
}

// shorthand multiply
void TimeSpan::operator*=(unsigned int number) {
  this->rawTime *= number;
}

// check smaller than
bool TimeSpan::operator<(const TimeSpan &ts) const {
  return this->rawTime < ts.rawTime;
}

// check larger than
bool TimeSpan::operator>(const TimeSpan &ts) const {
  return this->rawTime > ts.rawTime;
}

// check smaller than and equal to
bool TimeSpan::operator<=(const TimeSpan &ts) const {
  return this->rawTime <= ts.rawTime;
}

// check larger than and equal to
bool TimeSpan::operator>=(const TimeSpan &ts) const {
  return this->rawTime >= ts.rawTime;
}
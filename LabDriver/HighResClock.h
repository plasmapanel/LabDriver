#ifndef CUST_CLOCK
#define CUST_CLOCK
#include "stdafx.h"
struct HighResClock
{
  typedef long long                               rep;
  //what is was before
  // typedef std::nano                               period;
  typedef std::micro                               period;
  typedef std::chrono::duration<rep, period>      duration;
  typedef std::chrono::time_point<HighResClock>   time_point;
  static const bool is_steady = true;

  static time_point now();
};
#endif
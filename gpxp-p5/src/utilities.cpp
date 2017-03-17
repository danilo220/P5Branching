/*
 * Created  by rbh, 21/01/11
 * Modified by nas, 18/12/16
 */

#include <algorithm>
#include <cmath>

#include "utilities.h"

namespace GPXP
{
  radians degToRad(degrees d)
  {
      const double pi = 3.141592653589793;
      return d * pi / 180;
  }

  double sinSqr(double x)
  {
      const double sx = std::sin(x);
      return sx * sx;
  }

  bool containsValidChars(const string & toCheck, const string & allowedChars)
  {
      return toCheck.find_first_not_of(allowedChars) == string::npos;
  }

  bool noAdjacentDuplicateChars(const string & str)
  {
      return std::adjacent_find(str.begin(), str.end()) == str.end();
  }

  string removeDigitsFrom(string str)
  {
      str.erase(remove_if(str.begin(), str.end(), isdigit), str.end());
      return str;
  }

  string removeRepeatingCharsFrom(string str)
  {
      str.erase(unique(str.begin(), str.end()), str.end());
      return str;
  }

  string timeAsString(seconds time)
  {
      return std::to_string(time);
  }

  seconds timeFromString(const string & timeStr)
  {
      return std::stoul(timeStr);
  }
}

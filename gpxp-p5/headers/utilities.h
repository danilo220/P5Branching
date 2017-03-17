/*
 * Created  by rbh, 21/01/11
 * Modified by nas, 18/12/16
 */

#ifndef UTILITIES_H_RBH210111
#define UTILITIES_H_RBH210111

#include <string>

#include "gpxp.h"

using std::string;

namespace GPXP
{
  // Convert from degrees to radians.
  radians degToRad(degrees);

  // Sine squared function: sin^2(x)
  double sinSqr(double);

  bool containsValidChars(const string & toCheck, const string & allowedChars);

  bool noAdjacentDuplicateChars(const string &);

  string removeDigitsFrom(string);

  string removeRepeatingCharsFrom(string);

  string timeAsString(seconds);

  seconds timeFromString (const string &);
}

#endif

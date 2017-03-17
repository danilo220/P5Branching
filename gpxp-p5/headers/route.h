/*
 * Created  by rbh, 27/02/15
 * Modified by nas, 18/12/16
 */

#ifndef ROUTE_H_RBH270215
#define ROUTE_H_RBH270215

#include <vector>

#include "gpxp.h"
#include "position.h"

namespace GPXP
{
  using std::string;
  using std::vector;

  class Route
  {
    public:
      Route(string source, bool isFileName = false);

      bool builtOk() const;
      string buildReport() const;

      string name() const;
      metres totalLength() const;
      metres netLength() const;
      metres totalHeightGain() const;
      metres netHeightGain() const;
      degrees maxUphillGradient() const;
      degrees maxDownhillGradient() const;
      degrees minLat() const;
      degrees maxLat() const;
      degrees minLon() const;
      degrees maxLon() const;
      metres minEle() const;
      metres maxEle() const;
      unsigned int timesVisited(const Position &) const;
      unsigned int timesVisited(const string & nameTag) const;
      unsigned int numPositions() const;
      string nameOf(const Position &) const;
      Position positionOf(const string & nameTag) const;

      const Position & operator[](unsigned int) const;

    protected:
      Route() {} // Only called by Track constructor.

      metres routeLength;
      string routeName;
      vector<Position> positions;
      vector<string> positionNames;

      bool constructorSucceeded;
      string constructorReport;

      /* Two Positions are considered to be the same location is they are less than
       * "granularity" metres apart (horizontally).
       */
      bool areSameLocation(const Position &, const Position &) const;

      /*  Append the position to the end of the "positions" vector, unless
       *  it is close enough to the last Position to be considered the same
       *  location (see "areSameLocation()").  The routeLength is updated
       *  accordingly.
       */
      bool append(const Position & pos, const string & name = "");

      /* Simplify the Route by reducing the number of points: any point in the Route
       * that differs in distance from its predecessor by less than the parameter is
       * discarded.
       * The default value "granularity" is also used by the Route constructor to
       * limit the number of points originally, so a call of "simplify()" with the
       * default argument should have no effect.
       */
      void simplify(unsigned int overridingGranularity = granularity);

    private:
      // "granularity" is the minimum separation between Positions for GPX routes.
      static const metres granularity;

      // The North Pole Position is returned as a default value by some member functions.
      static const Position northPole;
  };
}

#endif

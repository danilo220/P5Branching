/*
 * Created  by rbh, 07/01/11
 * Modified by nas, 18/12/16
 */

#ifndef GRIDWORLD_H_RBH070111
#define GRIDWORLD_H_RBH070111

#include <string>
#include <map>
#include <vector>

#include "gpxp.h"
#include "utilities.h"
#include "position.h"

namespace GPXP
{
  /* GridWorld consists of a grid of points, where each point is named by a single character A-Y.
   *
   *  A B C D E
   *  F G H I J
   *  K L M N O
   *  P Q R S T
   *  U V W X Y
   *
   *  In the following classes, the central point M is used as the main reference point.
   */

  using Point = char;
  using std::string;

  /*
   * GridWorldRoutes are produced from a string of Points, from which a GPX or
   * NMEA log file can be generated.
   */
  class GridWorldRoute
  {
    public:
      /* The second parameter is a string of Points, e.g. "ABCD".
       */
      GridWorldRoute(string routeName, string routeStr);

      bool validRoute() const;

      /* The parameter is the Position of the central point 'M'.
       */
      string toGPX(const Position & posM = Position(0,0,1200)) const;
      string toNMEA(const Position & posM = Position(0,0,1200)) const; // unimplemented
      string toString() const; // unimplemented

    protected:
      string name;
      string routeString;
      bool isValid;
      mutable std::map<Point, Position> grid;

      Position positionOf(Point) const;

      /* The parameter is the Position of the central Point M.
       */
      void buildGrid(const Position &) const;

      /* The second parameter is the elevation of Point M.
       */
      metres calcElevationFor(Point point, metres eleM) const;

      static const string validRouteChars;
      static bool isValidRouteString(const string &);
  };


  class GridWorldTrack : public GridWorldRoute
  {
    public:
      /*  The second parameter is a string containing Points and time units.
       *  e.g. "A1B3C" means it takes 1 time unit to travel from Point A to Point B,
       *  then 3 time units to travel from Point B to Point C.
       *  The third parameter is the duration (in seconds) of a time unit.
       *  The fourth parameter is the absolute start time of the Track.
       */
      GridWorldTrack(string trackName,
                     string trackStr,
                     seconds timeUnitDuration,
                     seconds absoluteStartTime = 0);

      /* The first parameter is the time interval between generated tracking points.
       * The second parameter is the Position of the central point 'M'.
       */
      string toGPX(seconds logInterval, const Position & posM = Position(0,0,1200)) const;
      string toNMEA(seconds logInterval, const Position & posM = Position(0,0,1200)) const; // unimplemented
      string toString() const; // unimplemented

    protected:
      string trackString;
      seconds timeUnitSize;
      seconds startTime;

      std::vector<Point> waypoints;
      std::vector<unsigned int> timeUnitsToNextWaypoint;

      void constructWaypoints();

      static const string validTrackChars;
      static bool isValidTrackString(const string &);
      static string routeStringFromTrackString(const string &);
  };
}

#endif

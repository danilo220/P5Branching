/*
 * Created  by rbh, 07/01/11
 * Modified by nas, 22/12/16
 */

#include <iostream>

#include <sstream>
#include <cassert>
#include <cmath>
#include <algorithm>

#include "xmlgenerator.h"
#include "gridworld.h"

namespace GPXP
{
  GridWorldRoute::GridWorldRoute(string routeName, string routeStr)
  /* The second parameter contains a sequence of points that represent a Route.
   * To be valid, all chars must be in the range 'A'..'Y', and there must be no adjacent duplicates.
   */
  {
      name = routeName;
      routeString = routeStr;
      isValid = (! routeName.empty()) && isValidRouteString(routeStr);

      // The grid is not needed until toGPX() is called, so constructing the grid is deferred until then.
  }

  bool GridWorldRoute::validRoute() const
  {
      return isValid;
  }

  void GridWorldRoute::buildGrid(const Position & posM) const
  {
      /* A B C D E
       * F G H I J
       * K L M N O
       * P Q R S T
       * U V W X Y
       *
       * posM is the Position of the central Point M.
       */
      const degrees angleSubtendedBy1kmAtEquator = 0.00899072;

      degrees eleM = posM.getElevation();

      degrees latM = posM.getLatitude();
      latM = std::min(latM, 89.0);  // Maximum latitude is 89
      latM = std::max(latM, -89.0); // Minimum latitude is -89

      degrees longtitudeSubtendedBy1kmAtCurrentLatitude = angleSubtendedBy1kmAtEquator / std::cos(degToRad(latM));
      degrees maxLonAbs = 180.0 - 2 * longtitudeSubtendedBy1kmAtCurrentLatitude; // So it doesn't span Greenwich anti-meridian (180' W/E)
      degrees lonM = posM.getLongitude();
      lonM = std::min(lonM, maxLonAbs);
      lonM = std::max(lonM, -maxLonAbs);

      grid.clear();

      Point point = 'A';
      degrees latA = latM + 2 * angleSubtendedBy1kmAtEquator;
      degrees lonA = lonM - 2 * longtitudeSubtendedBy1kmAtCurrentLatitude;

      degrees lat = latA;
      for (int i = 0; i < 5; ++i)
      {
          degrees lon = lonA;
          for (int j = 0; j < 5; ++j)
          {
              // calcElevationFor() is a virtual function, so overridden by derived classes.
              metres ele = calcElevationFor(point, eleM);
              grid.insert(std::make_pair(point, Position(lat, lon, ele)));
              lon += longtitudeSubtendedBy1kmAtCurrentLatitude;
              ++point;
	  }
          lat -= angleSubtendedBy1kmAtEquator;
      }
  }

  string GridWorldRoute::toGPX(const Position & posM) const
  {
      using namespace XML_Generator;

      const bool noElevation = false;

      string result = basicGPXHeader();
      if (! isValid) // return empty route
      {
          result += "</gpx>";
          return result;
      }
      std::stack<string> yetToClose;
      yetToClose.push("</gpx>");

      buildGrid(posM);
      openTag(result, "rte", "", "", yetToClose);
      openCloseTagAndValue(result, "name", "", name);
      for (Point point : routeString)
      {
          Position pos = positionOf(point);
          openTag(result, "rtept", pos.toString(noElevation), "", yetToClose);
          openCloseTagAndValue(result, "name", "", string(1,point));
          openCloseTagAndValue(result, "ele", "", pos.getElevationString());
          result += yetToClose.top(); // </rtept>
          yetToClose.pop();
      }

      string closingTag;
      while (! yetToClose.empty())
      {
          closingTag = yetToClose.top();
          yetToClose.pop();
          result += closingTag;
      }
      return result;
  }

  Position GridWorldRoute::positionOf(Point point) const
  {
      return grid.at(point);
  }

  const string GridWorldRoute::validRouteChars = "ABCDEFGHIJKLMNOPQRSTUVWXY";

  bool GridWorldRoute::isValidRouteString(const string & routeStr)
  {
      return (! routeStr.empty())
          && containsValidChars(routeStr,validRouteChars)
          && noAdjacentDuplicateChars(routeStr);
  }

  metres GridWorldRoute::calcElevationFor(Point point, metres eleM) const
  {
      /* "eleM" is the elevation of Point M.
       * Neighbours of M are 100m lower than M.
       * All other Points are 200m lower than M.
       */
      metres ele;
      switch (point)
      {
          case 'M':
              ele = eleM;
              break;
	  case 'G': case 'H': case 'I':	case 'L': case 'N': case 'Q': case 'R':	case 'S':
              ele = eleM - 100;
              break;
	  default:
              ele = eleM - 200;
      }
      return ele;
  }


  GridWorldTrack::GridWorldTrack(string trackName, string trackStr, seconds timeUnitDuration, seconds start)
      : GridWorldRoute(trackName, routeStringFromTrackString(trackStr))
      {
          trackString = trackStr;
          timeUnitSize = timeUnitDuration;
          startTime = start;
          isValid = isValid && isValidTrackString(trackStr);
          constructWaypoints();
      }

  const string GridWorldTrack::validTrackChars = "ABCDEFGHIJKLMNOPQRSTUVWXY0123456789";

  bool GridWorldTrack::isValidTrackString(const string & trackStr)
  {
      return containsValidChars(trackStr, validTrackChars)
          && (! removeDigitsFrom(trackStr).empty());
  }

  string GridWorldTrack::routeStringFromTrackString(const string & trackStr)
  {
      return removeRepeatingCharsFrom(removeDigitsFrom(trackStr));
  }

  void GridWorldTrack::constructWaypoints()
  {
      if (! (isValid))
      {
          waypoints.push_back('M');
          waypoints.push_back('M');
          timeUnitsToNextWaypoint.push_back(0);
          return;
      }

      // Ignore any time before first waypoint.
      unsigned int startIndex  = trackString.find_first_of(validRouteChars);
      std::istringstream tss(trackString.substr(startIndex));

      Point point;
      unsigned int timeUnits;
      while (tss >> point)
      {
          waypoints.push_back(point);
          tss >> timeUnits;
          timeUnitsToNextWaypoint.push_back(timeUnits);
      }
      timeUnitsToNextWaypoint.pop_back(); // Discard any time units after the final waypoint.

      assert(waypoints.size() == (timeUnitsToNextWaypoint.size() + 1));
  }

  string GridWorldTrack::toGPX(seconds logInterval, const Position & posM) const
  {
      using namespace XML_Generator;

      const bool noElevation = false;

      string result = basicGPXHeader();
      if (! isValid)
      {
          result += "</gpx>";
          return result;
      }
      std::stack<string> yetToClose;
      yetToClose.push("</gpx>");

      buildGrid(posM);
      openTag(result, "trk", "", "", yetToClose);
      openCloseTagAndValue(result, "name", "", name);

      std::vector<unsigned int>::const_iterator timeUnitsIt = timeUnitsToNextWaypoint.begin();
      std::vector<Point>::const_iterator pointsIt = waypoints.begin();

      seconds segmentStartTime = startTime;

      Point currentPoint = *pointsIt;
      ++pointsIt;
      for (; pointsIt != waypoints.end(); ++pointsIt, ++timeUnitsIt)
      {
          Point nextPoint = *pointsIt;
          openTag(result, "trkseg", "", "", yetToClose);
          string segmentName = string(1,currentPoint) + "-" + string(1,nextPoint);
	  openCloseTagAndValue(result, "name", "", segmentName);

          seconds timeThisSegment = (*timeUnitsIt) * timeUnitSize;
          seconds segmentEndTime = segmentStartTime + timeThisSegment;
          double stepsThisSegment = timeThisSegment / logInterval;

          Position currentPos = positionOf(currentPoint);
          Position nextPos = positionOf(nextPoint);
          degrees deltaLat = (nextPos.getLatitude() - currentPos.getLatitude()) / stepsThisSegment;
          degrees deltaLon = (nextPos.getLongitude() - currentPos.getLongitude()) / stepsThisSegment;
          metres deltaEle = (nextPos.getElevation() - currentPos.getElevation()) / stepsThisSegment;

          degrees lat = currentPos.getLatitude();
          degrees lon = currentPos.getLongitude();
          metres ele = currentPos.getElevation();
          for (seconds currentTime = segmentStartTime; currentTime <= segmentEndTime; currentTime += logInterval)
          {
              Position pos(lat, lon, ele);
              openTag(result, "trkpt", pos.toString(noElevation), "", yetToClose);
              openCloseTagAndValue(result, "ele", "", pos.getElevationString());
              openCloseTagAndValue(result, "time", "", timeAsString(currentTime));

              result += yetToClose.top(); // </trkpt>
              yetToClose.pop();

              lat += deltaLat;
              lon += deltaLon;
              ele += deltaEle;
          }

          segmentStartTime = segmentEndTime;
          result += yetToClose.top(); // </trkseg>
          yetToClose.pop();

          currentPoint = nextPoint;
          segmentStartTime = segmentEndTime;
      }

      string closingTag;
      while (! yetToClose.empty())
      {
          closingTag = yetToClose.top();
          yetToClose.pop();
          result += closingTag;
      }
      return result;
  }
}

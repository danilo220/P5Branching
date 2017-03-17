/*
 * Created  by rbh, 30/01/11
 * Modified by nas, 21/12/16
 */

#include <sstream>
#include <fstream>
#include <iostream>
#include <cassert>
#include <cmath>

#include "utilities.h"
#include "xmlparser.h"
#include "track.h"

namespace GPXP
{
  Track::Track(string source, bool isFileName)
  {
      using namespace XML_Parser;
      using std::endl;

      std::ostringstream oss;
      if (isFileName)
      {
          string fileName = source;
          string content, line;
          std::ifstream file(fileName);
          if (! file)
          {
              oss << endl << "error opening constructor source file " << fileName;
              constructorReport = oss.str();
              constructorSucceeded = false;
              return;
          }
          oss << endl << "source file " << fileName << " opened okay";
          while (file.good())
          {
              getline(file, line);
              content += '\n';
              content += line;
          }
          oss << endl << "source file " << fileName << " read okay";
          source = content;
      }
      if (! elementExists(source,"gpx"))
      {
          oss << endl << "no gpx tag";
          constructorReport = oss.str();
          constructorSucceeded = false;
          return;
      }
      if (! elementExists(source,"trk"))
      {
          oss << endl << "no trk tag";
          constructorReport = oss.str();
          constructorSucceeded = false;
          return;
      }
      string temp = getElement(source, "trk");
      source = getElementContent(temp);
      if (elementExists(source, "name"))
      {
          temp = getAndEraseElement(source, "name");
          routeName = getElementContent(temp);
          oss << endl << "track name is " << routeName;
      }
      string mergedTrkSegs;
      while (elementExists(source, "trkseg"))
      {
          temp = getAndEraseElement(source, "trkseg");
          string trkseg = getElementContent(temp);
          string segname = getAndEraseElement(trkseg, "name");
          mergedTrkSegs += trkseg;
      }
      if (! mergedTrkSegs.empty())
      {
          source = mergedTrkSegs;
      }
      if (! elementExists(source, "trkpt"))
      {
          oss << endl << "no trkpt tag";
          constructorReport = oss.str();
          constructorSucceeded = false;
          return;
      }
      temp = getAndEraseElement(source, "trkpt");
      string lat = getElementAttribute(temp, "lat");
      string lon = getElementAttribute(temp, "lon");
      temp = getElementContent(temp);
      string temp2 = getElement(temp, "ele");
      string ele = getElementContent(temp2);
      temp2 = getElement(temp, "time");
      string time = getElementContent(temp2);
      string name;
      if (elementExists(temp,"name"))
      {
          temp2 = getElement(temp,"name");
          name = getElementContent(temp2);
      }
      Position currentPos(lat, lon, ele);
      positions.push_back(currentPos);
      positionNames.push_back(name);
      seconds startTime = timeFromString(time);
      arrived.push_back(0);
      departed.push_back(0);
      oss << endl << "start position added: " << currentPos.toString();
      while (elementExists(source, "trkpt"))
      {
          temp = getAndEraseElement(source, "trkpt");
          lat = getElementAttribute(temp, "lat");
          lon = getElementAttribute(temp, "lon");
          temp = getElementContent(temp);
          temp2 = getElement(temp, "ele");
          ele = getElementContent(temp2);
          temp2 = getElement(temp, "time");
          time = getElementContent(temp2);
          Position nextPos(lat, lon, ele);
          if (areSameLocation(currentPos, nextPos))
          {
              // If we're still at the same location, then we haven't departed yet.
              departed.back() = timeFromString(time) - startTime;
              oss << endl << "position ignored: " << nextPos.toString();
          }
          else
          {
              if (elementExists(temp,"name"))
              {
                  temp2 = getElement(temp,"name");
                  name = getElementContent(temp2);
              }
              else
              {
                  name = "";
              }
              positions.push_back(nextPos);
              positionNames.push_back(name);
              seconds timeElapsed = timeFromString(time) - startTime;
              arrived.push_back(timeElapsed);
              departed.push_back(timeElapsed);
              oss << endl << "position added: " << nextPos.toString();
              oss << " at time " << timeAsString(departed.back());
              currentPos = nextPos;
          }
      }
      oss << endl << positions.size() << " positions added";
      routeLength = 0;
      vector<Position>::const_iterator pci1, pci2;
      pci1 = pci2 = positions.begin();
      ++pci2;
      for ( ; pci2 != positions.end(); ++pci1, ++pci2 )
      {
          metres deltaH = distanceBetween(*pci1,*pci2);
          metres deltaV = pci1->getElevation() - pci2->getElevation();
          routeLength += std::sqrt(std::pow(deltaH,2) + std::pow(deltaV,2));
      }
      constructorReport = oss.str();
      constructorSucceeded = true;
      return;
  }

  seconds Track::totalTime() const
  {
      /* Computes total elapsed time between start and finish of the Track.
       * One of the 3 functions should exploit:
       * totalTime() == restingTime() + travellingTime()
       */
      bool implemented = false;
      assert(implemented);
      return (0);
  }

  seconds Track::restingTime() const
  {
      /* Computes total elapsed time between start and finish of the Track
       * that is spent not moving.
       * One of the 3 functions should exploit:
       * totalTime() == restingTime() + travellingTime()
       */
      bool implemented = false;
      assert(implemented);
      return (0);
  }

  seconds Track::travellingTime() const
  {
      /* Total elapsed time between start and finish of the Track that is
       * spent moving.
       * One of the 3 functions should exploit:
       * totalTime() == restingTime() + travellingTime()
       */
      bool implemented = false;
      assert(implemented);
      return (0);
  }

  speed Track::maxSpeed() const
  {
      /* Computes the greatest speed between any 2 Positions in the Track.
       */
      bool implemented = false;
      assert(implemented);
      return (0.0);
  }

  speed Track::averageSpeed(bool includeRests) const
  {
      /* Computes the average speed over the track.
       * The parameter determines whether the divisor is the totalTime()
       * or the travellingTime().
       */
      bool implemented = false;
      assert(implemented);
      return (0.0);
  }

  speed Track::maxRateOfClimb() const
  {
      /* Computes the greatest rate of climb between any 2 Positions.
       */
      bool implemented = false;
      assert(implemented);
      return (0.0);
  }

  speed Track::maxRateOfDescent() const
  {
      /* Computes the greatest rate of descent between any 2 Positions.
       */
      bool implemented = false;
      assert(implemented);
      return (0.0);
  }
}

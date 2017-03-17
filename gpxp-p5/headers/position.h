/*
 * Created  by rbh, 01/11/14
 * Modified by nas, 09/11/16
 * Modified by nas, 19/12/16
 */

#ifndef POSITION_H_RBH011114
#define POSITION_H_RBH011114

#include <string>

#include "gpxp.h"

namespace GPXP
{
    using std::string;

    class Position
    {
      public:

        /* Construct a Position from degrees latitude, degrees longitude, and
         * (optionally) elevation in metres.
         */
        Position(degrees lat, degrees lon, metres ele = 0.0);

        /* Construct a Position from strings containing a decimal degrees
         * representation of latitude and longitude, and (optionally) elevation in
         * metres.
         */
        Position(const string & latSt,
                 const string & lonSt,
                 const string & eleSt = "0");

        /* Construct a Position from strings containing a positive DDM (degrees and
         * decimal minutes) representation of latitude and longitude, along with
         * 'N'/'S' and 'E'/'W' characters to indicate positive or negative angles,
         * and (optionally) elevation in metres.
         */
        Position(const string & ddmLatStr, char northing,
                 const string & ddmLonStr, char easting,
                 const string & eleSt = "0");

        degrees getLatitude() const;
        degrees getLongitude() const;
        metres  getElevation() const;

        string toString(bool includeElevation = true) const;
        string getElevationString() const;

        metres distanceTo(const Position &) const;

      private:

        degrees latitude;
        degrees longitude;
        metres  elevation;

        degrees ddmTodd(const string &);
    };

    metres distanceBetween(const Position &, const Position &);
}

#endif

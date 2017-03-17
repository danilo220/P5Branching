/*
 * Created by nas, 03/01/17
 */

#ifndef BOOST_TEST_MODULE
  #define BOOST_TEST_DYN_LINK
  #define BOOST_TEST_MODULE N0123456_RouteLength
  #include <boost/test/unit_test.hpp>
#endif

#include <string>
#include "route.h"

/*  Check that the totalLength() and netLength() functions are consistent
 *  and correct for a variety of test routes.
 */
BOOST_AUTO_TEST_SUITE( N0123456_RouteLength )

std::string GPXRoutesDir = "../logs/GPX/routes/";

/* Test reported length of a straight route.
 * Total length and net length should be equal and positive.
 */
BOOST_AUTO_TEST_CASE( RouteLength_Straight )
{
    const bool isFileName = true;
    GPXP::Route routeABCD(GPXRoutesDir + "ABCD.gpx", isFileName);

    BOOST_REQUIRE(routeABCD.builtOk());

    BOOST_CHECK_GE(routeABCD.totalLength(), 0);

    BOOST_CHECK_GE(routeABCD.netLength(), 0);

    BOOST_CHECK_GE(routeABCD.totalLength(), routeABCD.netLength());

    BOOST_CHECK_CLOSE(routeABCD.totalLength(), 3000, 1);

    /* For this route the total and net lengths are equal, but we use CHECK_CLOSE to account for
     * floating-point rounding errors.
     */
    BOOST_CHECK_CLOSE(routeABCD.totalLength(), routeABCD.netLength(), 1);
}

/* Test report length of a wiggly route.
 * Total length should exceed net length; both should be positive.
 */
BOOST_AUTO_TEST_CASE( RouteLength_Wiggly )
{
    const bool isFileName = true;
    GPXP::Route routeABCD(GPXRoutesDir + "NorthYorkMoors.gpx", isFileName);

    BOOST_REQUIRE(routeABCD.builtOk());

    BOOST_CHECK_GE(routeABCD.totalLength(), 0);
    BOOST_CHECK_GE(routeABCD.netLength(), 0);
    BOOST_CHECK_GE(routeABCD.totalLength(), routeABCD.netLength());

    BOOST_CHECK_CLOSE(routeABCD.totalLength(), 26600, 10);
    BOOST_CHECK_CLOSE(routeABCD.netLength(), 9700, 10);
}

BOOST_AUTO_TEST_SUITE_END()

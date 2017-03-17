/*
 * Created  by rbh, 21/02/16
 * Modified by nas, 03/01/17
 */

#ifndef BOOST_TEST_MODULE
  #define BOOST_TEST_DYN_LINK
  #define BOOST_TEST_MODULE N0123456_NonexistantFile
  #include <boost/test/unit_test.hpp>
#endif

#include <string>
#include <fstream>
#include "route.h"

/*  Check that the constructors correctly handles the case when the input file is missing.
 */
BOOST_AUTO_TEST_SUITE( N0123456_NonexistantFile )

using std::string;

/* Check that the Route constructor fails when called with an non-existant file.
 */
BOOST_AUTO_TEST_CASE( nonexistantRouteFile )
{
    const bool isFileName = true;

    string filename("NonexistantFile.gpx");
    std::ifstream nullHandle(filename);

    // Ensure the file really doesn't exist, otherwise the test won't be valid.
    BOOST_REQUIRE(! nullHandle.good());

    GPXP::Route failedRoute(filename, isFileName);
    BOOST_CHECK(! failedRoute.builtOk());
    BOOST_CHECK(failedRoute.buildReport().find("error opening constructor source file") != string::npos);
    BOOST_CHECK(failedRoute.buildReport().find("source file " + filename + " opened okay") == string::npos);
}

/* Check that the Track constructor fails when called with an non-existant file.
 */
BOOST_AUTO_TEST_CASE( nonexistantTrackFile )
{
    const bool isFileName = true;

    string filename("NonexistantFile.gpx");
    std::ifstream nullHandle(filename);

    // Ensure the file really doesn't exist, otherwise the test won't be valid.
    BOOST_REQUIRE(! nullHandle.good());

    GPXP::Route failedRoute(filename, isFileName);
    BOOST_CHECK(! failedRoute.builtOk());
    BOOST_CHECK(failedRoute.buildReport().find("error opening constructor source file") != string::npos);
    BOOST_CHECK(failedRoute.buildReport().find("source file " + filename + " opened okay") == string::npos);
}


/*  Check that a file is not read when the 'isFileName' argument of the Route constructor is false.
 */
BOOST_AUTO_TEST_CASE( fileNotReadWhenRouteSourceIsGPXString )
{
    const string source = "<gpx><rte><rtept lat=\"0\" lon=\"0\"><ele>1</ele></rtept></rte></gpx>";

    const bool isFileName = false;

    std::ifstream nullHandle(source);

    // Ensure the file really doesn't exist, otherwise the test won't be valid.
    BOOST_REQUIRE(! nullHandle.good());

    GPXP::Route route(source, isFileName);
    BOOST_CHECK(route.builtOk());

    BOOST_CHECK(route.buildReport().find("error opening constructor source file") == string::npos);
    BOOST_CHECK(route.buildReport().find("source file " + source + " opened okay") == string::npos);
}

/*  Check that a file is not read when the 'isFileName' argument of the Track constructor is false.
 */
BOOST_AUTO_TEST_CASE( fileNotReadWhenTrackSourceIsGPXString )
{
    const string source = "<gpx><rte><rtept lat=\"0\" lon=\"0\"><ele>1</ele></rtept></rte></gpx>";

    const bool isFileName = false;

    std::ifstream nullHandle(source);

    // Ensure the file really doesn't exist, otherwise the test won't be valid.
    BOOST_REQUIRE(! nullHandle.good());

    GPXP::Route track(source, isFileName);
    BOOST_CHECK(track.builtOk());

    BOOST_CHECK(track.buildReport().find("error opening constructor source file") == string::npos);
    BOOST_CHECK(track.buildReport().find("source file " + source + " opened okay") == string::npos);
}


BOOST_AUTO_TEST_SUITE_END()

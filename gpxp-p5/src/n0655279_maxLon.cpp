#ifndef BOOST_TEST_MODULE
    #define BOOST_TEST_DYN_LINK
    #define BOOST_TEST_MODULE N0655279_maxLon
    #include <boost/test/unit_test.hpp>
#endif

//Include files and dependencies

#include "route.h"
#include <fstream>
#include <string>


BOOST_AUTO_TEST_SUITE(N0655279_maxLonTestSuite)

std::string GPXRoutesDir = "../logs/GPX/routes/";

//In this route all longitude positions were positive and 0.00899072 was the max longitude
BOOST_AUTO_TEST_CASE(ABCDmaxLon)
{
	const bool isFileName = true;
	GPXP::Route routeABCDMaxLon(GPXRoutesDir + "ABCD.gpx", isFileName);

	BOOST_REQUIRE(routeABCDMaxLon.builtOk());

	//comparing if it's equal to the value given
	BOOST_CHECK_CLOSE(routeABCDMaxLon.maxLon(), 0.00899072, 0.0001); 

	//in case if the test fail then these messages will tell me if the value is higher or lower than the value expected
	BOOST_CHECK_MESSAGE(!(routeABCDMaxLon.maxLon() > 0.00899072),"Higher");
    BOOST_CHECK_MESSAGE(!(routeABCDMaxLon.maxLon() < 0.00899072),"Lower");
}

//In this route all longitude positions were positive and 0.0179814 was the max longitude
BOOST_AUTO_TEST_CASE(EJ0TmaxLon)
{
	const bool isFileName = true;
    GPXP::Route routeEJOTMaxLon(GPXRoutesDir + "EJOT.gpx", isFileName);

	BOOST_REQUIRE(routeEJOTMaxLon.builtOk());

	//comparing if it's equal to the value given
	BOOST_CHECK_CLOSE(routeEJOTMaxLon.maxLon(), 0.0179814, 0.0001); 

	//in case if the test fail then these messages will tell me if the value is higher or lower than the value expected
	BOOST_CHECK_MESSAGE(!(routeEJOTMaxLon.maxLon() > 0.0179814),"Higher");
    BOOST_CHECK_MESSAGE(!(routeEJOTMaxLon.maxLon() < 0.0179814),"Lower");
}

//In this route all longitude positions were negative and -0.00899072 was the max longitude
BOOST_AUTO_TEST_CASE(KQUVmaxLon)
{
	const bool isFileName = true;
	GPXP::Route routeKQUVMaxLon(GPXRoutesDir + "KQUV.gpx", isFileName);

	BOOST_REQUIRE(routeKQUVMaxLon.builtOk());

	//comparing if it's equal to the value given
	BOOST_CHECK_CLOSE(routeKQUVMaxLon.maxLon(), -0.00899072, 0.0001); 

	//in case if the test fail then these messages will tell me if the value is higher or lower than the value expected
	BOOST_CHECK_MESSAGE(!(routeKQUVMaxLon.maxLon() >-0.00899072),"Higher");
    BOOST_CHECK_MESSAGE(!(routeKQUVMaxLon.maxLon() <-0.00899072),"Lower");
}

//In this route all longitude positions were the same value -0.0179814 which means the max longitude was this value
BOOST_AUTO_TEST_CASE(KUAPmaxLon)
{
	const bool isFileName = true;
	GPXP::Route routeKUAPMaxLon(GPXRoutesDir + "KUAP.gpx", isFileName);

	BOOST_REQUIRE(routeKUAPMaxLon.builtOk());

	//comparing if it's equal to the value given
	BOOST_CHECK_CLOSE(routeKUAPMaxLon.maxLon(), -0.0179814, 0.0001); 

	//in case if the test fail then these messages will tell me if the value is higher or lower than the value expected
	BOOST_CHECK_MESSAGE(!(routeKUAPMaxLon.maxLon() >-0.0179814),"Higher");
    BOOST_CHECK_MESSAGE(!(routeKUAPMaxLon.maxLon() <-0.0179814),"Lower");
}
BOOST_AUTO_TEST_SUITE_END()

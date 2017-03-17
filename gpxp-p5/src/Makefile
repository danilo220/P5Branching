#
# Created  by rbh
# Modified by nas, 18/12/16
# Modified by nas, 26/01/17
#

INCLUDEDIR = ../headers
TESTSDIR   = ../tests_accepted

vpath %.h   $(INCLUDEDIR)
vpath %.cpp $(TESTSDIR)

CXXFLAGS = -std=c++11 -g -I $(INCLUDEDIR) -Wall -Wfatal-errors

TESTOBJECTS = position.o route.o track.o utilities.o xmlparser.o
# All except gridworld.o and xmlgenerator.o

LOGOBJECTS = gridworld.o position.o utilities.o xmlgenerator.o

################################################################################

all-tests : all-tests.cpp $(TESTOBJECTS) $(TESTSDIR)/*
	g++ $(CXXFLAGS) -I $(TESTSDIR) all-tests.cpp $(TESTOBJECTS) -o all-tests -lboost_unit_test_framework

################################################################################
#Creating log/LogTesting
n0655279: n0655279.cpp $(LOGOBJECTS)
	g++ $(CXXFLAGS) n0655279.cpp $(LOGOBJECTS) -o n0655279


################################################################################

# Use this for building individual tests in isolation.

# Example filepath, replace the filepath with your own test file.
# SINGLETESTFILE = ../tests_accepted/N0123456_RouteLength.cpp

#Testing my checking
SINGLETESTFILE = ../src/n0655279_maxLon.cpp

single-test : $(SINGLETESTFILE) $(TESTOBJECTS)
	g++ $(CXXFLAGS) $(SINGLETESTFILE) $(TESTOBJECTS) -o single-test -lboost_unit_test_framework

################################################################################

gridworld.o : gridworld.cpp gridworld.h gpxp.h position.h utilities.h xmlgenerator.h
	g++ $(CXXFLAGS) -c gridworld.cpp -o gridworld.o

position.o : position.cpp position.h gpxp.h utilities.h
	g++ $(CXXFLAGS) -c position.cpp -o position.o

route.o : route.cpp route.h gpxp.h position.h xmlparser.h
	g++ $(CXXFLAGS) -c route.cpp -o route.o

track.o : track.cpp track.h gpxp.h position.h route.h utilities.h xmlparser.h
	g++ $(CXXFLAGS) -c track.cpp -o track.o

utilities.o : utilities.cpp utilities.h gpxp.h
	g++ $(CXXFLAGS) -c utilities.cpp -o utilities.o

xmlgenerator.o : xmlgenerator.cpp xmlgenerator.h
	g++ $(CXXFLAGS) -c xmlgenerator.cpp -o xmlgenerator.o

xmlparser.o : xmlparser.cpp xmlparser.h
	g++ $(CXXFLAGS) -c xmlparser.cpp -o xmlparser.o

# n0655279.o : n0655279.cpp
# 	g++ $(CXXFLAGS) -c n0655279.cpp -o n0655279.o

# n0655279: n0655279.cpp $(gridworld.o, position.o, utilities.o, xmlgenerator.o)
# 	g++$(CXXFLAGS) n0655279.cpp(gridworld.o, position.o, utilities.o, xmlgenerator.o) -o n0655279

################################################################################

clean:
	rm -f *.o all-tests single-test n0655279 

################################################################################

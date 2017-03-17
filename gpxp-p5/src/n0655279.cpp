#include "gridworld.h"
#include <fstream>

int main()
{
    GPXP::GridWorldRoute myroute("MyRouteName", "KUAP");
    std::ofstream mylogfile("KUAP.gpx");
    mylogfile << myroute.toGPX();

    return 0;
}


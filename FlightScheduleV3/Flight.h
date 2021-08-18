#pragma once
#include <string>
#include "Pilot.h"
#include "Aircraft.h"

class Flight
{
private:
	Pilot pilot;
	Aircraft plane;
	int takeoff;

public:
	Flight();

	// SETTERS
	void setPilot(Pilot captain);
	void setPlane(Aircraft aircraft);
	void setTime(int time);
	
	// GETTERS
	string getPilot();
	string getPlaneModel();
	
	// CLASS FUNC
	string printFlight();
};


#include <iostream>
#include <string>
#include "Flight.h"

/* ****************************************
* Private Functions
**************************************** */



/* ****************************************
* Public Functions
**************************************** */

Flight::Flight() { }

// SETTERS
void Flight::setPilot(Pilot captain)
{
	pilot = captain;
}
void Flight::setPlane(Aircraft aircraft)
{
	plane = aircraft;
}
void Flight::setTime(int time)
{
	takeoff = time; 
}

// GETTERS
string Flight::getPilot()
{
	return pilot.getName();
}
string Flight::getPlaneModel()
{
	return plane.getModel();
}

// CLASS FUNC
string Flight::printFlight()
{
	string output = pilot.getName()	+ ", aka " + pilot.getCallSign()
			+ ", will be flying the " + plane.getModel() + ". "
			+ "There are " + to_string(plane.getPaxNum()) + " passengers on board. "
			+ "Takeoff is at " + to_string(takeoff) + ".\n";
	return output;
}


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
	string output = "\n\t\t"+ pilot.getName() + ", aka " + pilot.getCallSign()
			+ ", will be flying the " + plane.getModel() + ". "
			+ "\n\t\tThere are " + to_string(plane.getPaxNum()) + " passengers on board. "
			+ "\n\t\tTakeoff is at " + to_string(takeoff) + ".\n";
	return output;
}


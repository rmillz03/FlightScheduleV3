#include "Pilot.h"
#include <iostream>
#include <string>
#include <iomanip>

using namespace std;

Pilot::Pilot()
{
	pilotID = 0;
	fullName = "";
	callSign = "";
}

Pilot::Pilot(int ID, string person, string codeName)
{
	pilotID = ID;
	fullName = person;
	callSign = codeName;
}
// SETTERS
void Pilot::setID(int ID)
{
	pilotID = ID;
}
void Pilot::setName(string name)
{
	fullName = name;
}
void Pilot::setCallSign(string name)
{
	callSign = name;
}
// GETTERS
int Pilot::getID()
{
	return pilotID;
}
string Pilot::getName()
{
	return fullName;
}
string Pilot::getCallSign()
{
	return callSign;
}
// CLASS FUNCS
void Pilot::printData()
{
	cout << setw(20)<< fullName << setw(10)<< pilotID <<callSign << endl;
}

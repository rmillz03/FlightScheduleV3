#include "Aircraft.h"
#include <iostream>
#include <string>
using namespace std;

Aircraft::Aircraft() { }
Aircraft::Aircraft(string model, int pax)
{
	modelName = model;
	passengers = pax;
}

// SETTERS
void Aircraft::setModel(string model)
{
	modelName = model;
}
void Aircraft::setPax(int pax)
{
	passengers = pax;
}

// GETTERS
string Aircraft::getModel() { return modelName; }
int Aircraft::getPaxNum() { return passengers; }

// CLASS FUNC
void Aircraft::printData()
{
	cout << modelName << "        " << passengers << endl;
}

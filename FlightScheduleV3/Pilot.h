#pragma once
#include <string>
using namespace std;

class Pilot
{
private:
	int pilotID;
	string fullName;
	string callSign;
public:
	Pilot();
	Pilot(int ID, string person, string codeName);
	
	// SETTERS
	void setID(int ID);
	void setName(string name);
	void setCallSign(string name);
	
	// GETTERS
	int getID();
	string getName();
	string getCallSign();
	
	// CLASS FUNCS
	void printData();
};


#pragma once
#include <string>
using namespace std;

class Aircraft
{
private:
	string modelName;
	int passengers;
public:
	Aircraft();
	Aircraft(string model, int pax);
	
	// SETTERS
	void setModel(string model);
	void setPax(int pax);

	// GETTERS
	string getModel();
	int getPaxNum();

	// CLASS FUNC
	void printData();
};


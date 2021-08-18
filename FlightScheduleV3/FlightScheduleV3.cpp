#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>


#include "Pilot.h"
#include "Aircraft.h"
#include "Flight.h"
using namespace std;

const int MAX_SIZE = 100;

/* ****************************************
* Main.cpp Funcitons
**************************************** */

int validateSelection(const char* prompt, int min, int max)
{
	//thanks to Dan McElroy, Youtube, for this function setup
	int inputValue;
	bool keepTrying;
	do
	{
		keepTrying = false;
		cout << "\n\n\t\t " << prompt;
		cin >> inputValue;
		if (!cin) //check for type mismatch
		{
			cout << "\n\t\tPlease enter a numeric value.";
			cin.clear(); //clear the cin error flag
			cin.ignore(10000, '\n'); //flush the input buffer
			keepTrying = true;
		}
		else if ((inputValue < min) || (inputValue > max)) //check input within range
		{
			cout << "\n\t\tValue is out of range.";
			keepTrying = true;
		}
	} while (keepTrying);

	return inputValue;
}


int mainMenu()
{
	system("CLS");
	cout << "\n\t\t========== Main Menu ==========\n\n";
	cout << "\n\t\t1 - Add new pilot";
	cout << "\n\t\t2 - Add new aircraft";
	cout << "\n\t\t3 - Create a flight";
	cout << "\n\t\t4 - Show all flights";
	cout << "\n\t\t5 - Delete records";
	cout << "\n\t\t0 - Exit";
	return validateSelection("Please select a number: ", 0, 5);
}

int recordMenu()
{
	system("CLS");
	cout << "\n\t\t========== Delete Records Menu ==========\n\n";
	cout << "\n\t\t1 - Delete a pilot record";
	cout << "\n\t\t2 - Delete an aircraft record";
	cout << "\n\t\t3 - Delete a flight record";
	cout << "\n\t\t0 - Return to the main menu";
	cout << "\n\nPlease select a number: ";
	return validateSelection("Please select a number: ", 0, 5);
}

/* ****************************************
*  MAIN
**************************************** */
int main()
{

	/* ****************************************
	*  START Database Initialization 
	**************************************** */	
	FILE* filePilots, *fileAircraft, *fileFlights, *fileTemp;
	long int recSize;
	
	filePilots = fopen("pilotrecords.txt", "a+");

	if (filePilots == NULL)
	{
		filePilots = fopen("pilotrecords.txt", "w+");
		
		if (filePilots == NULL)
		{
			cout << ("Cannot open file: pilotrecords.txt");
		}
	}

	fileAircraft = fopen("aircraftrecords.txt", "a+");

	fileFlights = fopen("flightrecords.txt", "a+");


	/* ****************************************
	*  END Database Initialization
	**************************************** */

	int menuSelection;
	int ID, pax, indexNum, indexCount;
	string name, codeName, model;
	const char* prompt;

	Pilot pilotRec;
	Aircraft airRec;
	Flight flightRec;

	Pilot aryPilots[MAX_SIZE];
	Aircraft aryAircraft[MAX_SIZE];

	do
	{
		//mainMenu();
		//cin >> menuSelection;
		//menuSelection = mainMenu();

		system("CLS");
		switch (mainMenu())
		{
		case 1:
			//create new pilot
			cout << "\n\t\t========== Creating New Pilot Record ==========\n\n";
			cout << "\n\t\tEnter pilot ID number: ";
			cin >> ID;
			cout << "\n\t\tEnter pilot's full name: ";
			cin.ignore();
			getline(cin, name);
			cout << "\n\t\tEnter pilot's callsign: ";
			//cin.ignore();
			getline(cin, codeName);

			recSize = sizeof(pilotRec);

			pilotRec.setID(ID);
			pilotRec.setName(name);
			pilotRec.setCallSign(codeName);

			try
			{
				fseek(filePilots, 0, SEEK_END);
				fwrite(&pilotRec, recSize, 1, filePilots);

				cout << "\n\n\t\tPilot added successfully. ";
			}
			catch (exception& e)
			{
				cout << e.what() << "\n";
			}
			
			system("PAUSE");

			break;
		case 2:
			//create new aircraft
			cout << "\n\t\t========== Creating New Pilot Record ==========\n\n";
			cout << "\n\t\tEnter the aircraft model: ";
			cin.ignore();
			getline(cin, model);
			cout << "\n\t\tEnter the number of passengers: ";
			cin >> pax;

			airRec.setModel(model);
			airRec.setPax(pax);

			recSize = sizeof(airRec);

			try
			{
				fseek(fileAircraft, 0, SEEK_END);
				fwrite(&airRec, recSize, 1, fileAircraft);

				cout << "\n\n\t\tAircraft added successfully. ";
			}
			catch (exception& e)
			{
				cout << e.what() << "\n";
			}

			system("PAUSE");

			break;
		case 3:
			//assign flight
			//
			//print out pilot roster
			cout << "\n\t\t========== Pilot Roster ==========\n\n";
			cout << "\n\t\tIndex    Name   ID   Call Sign";

			recSize = sizeof(pilotRec);
			rewind(filePilots);
			indexCount = 0;
			while (fread(&pilotRec, recSize, 1, filePilots) == 1)
			{
				cout << "\n\t\t" << to_string(indexCount)<< "     " << pilotRec.getID() 
					<< setw(10) << pilotRec.getName()
					<< pilotRec.getCallSign() << "\n";
				aryPilots[indexCount] = pilotRec;
				indexCount++;
			}

			indexNum = validateSelection("Please enter the index number: ", 0, indexCount - 1);
			flightRec.setPilot(aryPilots[indexNum]);

			//print aircraft list
			system("CLS");
			cout << "\n\t\t========== Aircraft Manifest ==========\n\n";
			cout << "\n\t\tIndex     Model    Passngers";
			
			recSize = sizeof(airRec);
			rewind(fileAircraft);
			indexCount = 0; 
			while (fread(&airRec, recSize, 1, fileAircraft) == 1)
			{
				cout << "\n\t\t"<<to_string(indexCount)<<"  " << airRec.getModel() 
					<< setw(10) << airRec.getPaxNum() << "\n";
				aryAircraft[indexCount] = airRec;
				indexCount++;
			}

			indexNum = validateSelection("Please enter the index number: ", 0, indexCount - 1);
			flightRec.setPlane(aryAircraft[indexNum]);

			cout << endl;

			//flightRec.setTime();
			prompt = "Please set times using a 24-hour time format. Please do not include a colon."
				"\n\t\tExample, 10:30AM should be written as 1030 and 10:30PM will be written as 2230."
				"\n\n\t\tWhen is the flight scheduled to take off? ";
			flightRec.setTime(validateSelection(prompt, 0, 2400));

			recSize = sizeof(flightRec);

			try
			{
				fseek(fileFlights, 0, SEEK_END);
				fwrite(&flightRec, recSize, 1, fileFlights);

				cout << "\n\n\t\tFlight added successfully. ";
			}
			catch (exception& e)
			{
				cout << e.what() << "\n";
			}
			cout << "\n\nPlease choose Option-4 at the main menu to see the flight schedule.\n";
			system("PAUSE");
			break;
		case 4:
			//print schedule
			recSize = sizeof(flightRec);
			rewind(fileFlights);
			while (fread(&flightRec, recSize, 1, fileFlights) == 1)
			{
				cout << flightRec.printFlight() << endl;
			}
			
			system("PAUSE");
			break;
		case 5:
			//delete records
			menuSelection = recordMenu();

			switch (menuSelection)
			{
			case 1:
				//print out pilot roster
				cout << "\n\t\t========== Pilot Roster ==========\n\n";
				cout << "\n\t\tIndex    Name   ID   Call Sign";

				recSize = sizeof(pilotRec);
				rewind(filePilots);
				indexCount = 0;
				while (fread(&pilotRec, recSize, 1, filePilots) == 1)
				{
					cout << "\n\t\t" << to_string(indexCount) << "     " << pilotRec.getID()
						<< setw(10) << pilotRec.getName()
						<< pilotRec.getCallSign() << "\n";
					aryPilots[indexCount] = pilotRec;
					indexCount++;
				}
				cout << "\n\nPlease enter the index number: ";
				cin >> indexNum;

				/*
				* add pilot array records to a temp file,
				* skipping the record to be deleted.
				* delete original record.
				* rename temp file as orignal name.
				*/
				fileTemp = fopen("temp.txt", "w+");
				recSize = sizeof(pilotRec);

				for (int x = 0; x < indexCount; x++)
				{
					if (x != indexNum)
					{
						try
						{
							fseek(fileTemp, 0, SEEK_END);
							fwrite(&aryPilots[x], recSize, 1, fileTemp);
						}
						catch (exception& e)
						{
							cout << e.what() << "\n";
						}
					}
				}

				fclose(fileTemp);
				fclose(filePilots);
				remove("pilotrecords.txt");
				rename("temp.txt", "pilotrecords.txt");
				filePilots = fopen("pilotrecords.txt", "a+"); //reopen the file for use

				break;
			case 2:
				break;
			case 3:
				break;
			default:
				menuSelection = 1; //make a non-zero num to continue to main
			}

			cout << "\n\nRecord removed from file. ";
			system("PAUSE");
			break;
		default:
			;
		}
	} while (menuSelection != 0);

	//close all files
	fclose(filePilots);
	fclose(fileAircraft);
	fclose(fileFlights);
	
	return 0;
}
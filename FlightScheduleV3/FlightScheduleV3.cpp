#include <iostream>
#include <string>
#include <iomanip>
#include <stdio.h>
#include <cstdlib>

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

char validateYesNo(const char* prompt)
{
	char inputValue;
	bool keepTrying;
	do
	{
		keepTrying = false;
		cout << "\n\n\t\t " << prompt;
		cin >> inputValue;
		if (!cin) //check for type mismatch
		{
			cout << "\n\t\tPlease enter 'Y' or 'N'.";
			cin.clear(); //clear the cin error flag
			cin.ignore(10000, '\n'); //flush the input buffer
			keepTrying = true;
		}
		else if ( (inputValue !='y') && 
			(inputValue !='Y') && 
			(inputValue != 'n') && 
			(inputValue != 'N') )//check input within range
		{
			cout << "\n\t\tPlease enter 'Y' or 'N'.";
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
	return validateSelection("Please select a number: ", 0, 5);
}

void systemPause()
{
	cout << "\n\n\t\tPress any key to continue...";
	cin.ignore();
	cin.get();
	return;
}

/* ****************************************
*  MAIN
**************************************** */
int main()
{

	/* ****************************************
	*  START File Initialization 
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
	if (fileAircraft == NULL)
	{
		fileAircraft = fopen("aircraftrecords.txt", "w+");

		if (fileAircraft == NULL)
		{
			cout << ("Cannot open file: aircraftrecords.txt");
		}
	}

	fileFlights = fopen("flightrecords.txt", "a+");
	if (fileFlights == NULL)
	{
		fileFlights = fopen("flightrecords.txt", "w+");

		if (fileFlights == NULL)
		{
			cout << ("Cannot open file: flightrecords.txt");
		}
	}

	/* ****************************************
	*  END File Initialization
	**************************************** */

	int menuSelection;
	int ID, pax, indexNum, indexCount;
	string name, codeName, model;
	const char* prompt;
	char confirm;

	Pilot pilotRec;
	Aircraft airRec;
	Flight flightRec;

	Pilot aryPilots[MAX_SIZE];
	Aircraft aryAircraft[MAX_SIZE];
	Flight aryFlights[MAX_SIZE];

	do
	{
		menuSelection = mainMenu();

		switch (menuSelection)
		{
		case 0: 
			break;
		case 1:
			system("CLS");
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
			
			systemPause();

			break;
		case 2:
			system("CLS");
			//create new aircraft
			cout << "\n\t\t========== Creating New Aircraft Record ==========\n\n";
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

			systemPause();

			break;
		case 3:
			//assign flight
			//
			system("CLS");
			//print out pilot roster
			cout << "\n\t\t========== Pilot Roster ==========\n\n";
			cout << "\n\t\t" << setw(5) << "Index"
				<< setw(10) << "Name" 
				<< setw(20) << "ID"  
				<< setw(20) << "Call Sign";

			recSize = sizeof(pilotRec);
			rewind(filePilots);
			indexCount = 0;
			while (fread(&pilotRec, recSize, 1, filePilots) == 1)
			{
				cout << "\n\t\t" << setw(5) << to_string(indexCount)
					<< setw(10) << pilotRec.getID()
					<< setw(20) << pilotRec.getName()
					<< setw(20) << pilotRec.getCallSign();
				aryPilots[indexCount] = pilotRec;
				indexCount++;
			}

			indexNum = validateSelection("Please enter the index number: ", 0, indexCount - 1);
			flightRec.setPilot(aryPilots[indexNum]);

			//print aircraft list
			system("CLS");
			cout << "\n\t\t========== Aircraft Manifest ==========\n\n";
			cout << "\n\t\t" << setw(5) << "Index"
				<< setw(15) << "Model"
				<< setw(10) << "# PAX";
			
			
			recSize = sizeof(airRec);
			rewind(fileAircraft);
			indexCount = 0; 
			while (fread(&airRec, recSize, 1, fileAircraft) == 1)
			{
				cout << "\n\t\t"<< setw(5) << to_string(indexCount)
					<<setw(15) << airRec.getModel() 
					<< setw(10) << airRec.getPaxNum();
				aryAircraft[indexCount] = airRec;
				indexCount++;
			}

			indexNum = validateSelection("Please enter the index number: ", 0, indexCount - 1);
			flightRec.setPlane(aryAircraft[indexNum]);

			cout << endl;

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
			
			systemPause();
			break;
		case 4:
			//print schedule
			system("CLS");
			recSize = sizeof(flightRec);
			rewind(fileFlights);
			while (fread(&flightRec, recSize, 1, fileFlights) == 1)
			{
				cout << flightRec.printFlight() << endl;
			}
			
			systemPause();
			break;
		case 5:
			do
			{
				//delete records
				system("CLS");
				menuSelection = recordMenu();

				switch (menuSelection)
				{
				case 0:
					break;
				case 1:
					//print out pilot roster
					cout << "\n\t\t========== Pilot Roster ==========\n\n";
					cout << "\n\t\t" << setw(5) << "Index"
						<< setw(10) << "Name"
						<< setw(20) << "ID"
						<< setw(20) << "Call Sign";

					recSize = sizeof(pilotRec);
					rewind(filePilots);
					indexCount = 0;
					while (fread(&pilotRec, recSize, 1, filePilots) == 1)
					{
						cout << "\n\t\t" << setw(5) << to_string(indexCount)
							<< setw(10) << pilotRec.getID()
							<< setw(20) << pilotRec.getName()
							<< setw(20) << pilotRec.getCallSign();
						aryPilots[indexCount] = pilotRec;
						indexCount++;
					}
					indexNum = validateSelection("Please enter the index number: ", 0, indexCount - 1);

					prompt = "\n\t\tAre you sure you want to delete this index? ";
					confirm = validateYesNo(prompt);

					if ((confirm == 'y') || (confirm == 'Y'))
					{
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

						cout << "\n\nRecord removed from file. ";
					}
					else
					{
						cout << "\n\t\tRecord was NOT deleted. ";
					}
					break;
				case 2:
					//print aircraft list
					system("CLS");
					cout << "\n\t\t========== Aircraft Manifest ==========\n\n";
					cout << "\n\t\t" << setw(5) << "Index"
						<< setw(15) << "Model"
						<< setw(10) << "# PAX";

					recSize = sizeof(airRec);
					rewind(fileAircraft);
					indexCount = 0;
					while (fread(&airRec, recSize, 1, fileAircraft) == 1)
					{
						cout << "\n\t\t" << setw(5) << to_string(indexCount)
							<< setw(15) << airRec.getModel()
							<< setw(10) << airRec.getPaxNum();
						aryAircraft[indexCount] = airRec;
						indexCount++;
					}

					indexNum = validateSelection("Please enter the index number: ", 0, indexCount - 1);

					prompt = "\n\t\tAre you sure you want to delete this index? ";
					confirm = validateYesNo(prompt);

					if ((confirm == 'y') || (confirm == 'Y'))
					{
						/*
						* add array records to a temp file,
						* skipping the record to be deleted.
						* delete original record.
						* rename temp file as orignal name.
						*/
						fileTemp = fopen("temp.txt", "w+");
						recSize = sizeof(airRec);

						for (int x = 0; x < indexCount; x++)
						{
							if (x != indexNum)
							{
								try
								{
									fseek(fileTemp, 0, SEEK_END);
									fwrite(&aryAircraft[x], recSize, 1, fileTemp);
								}
								catch (exception& e)
								{
									cout << e.what() << "\n";
								}
							}
						}

						fclose(fileTemp);
						fclose(fileAircraft);
						remove("aircraftrecords.txt");
						rename("temp.txt", "aircraftrecords.txt");
						filePilots = fopen("aircraftrecords.txt", "a+"); //reopen the file for use

						cout << "\n\n\t\tRecord removed from file. ";
					}
					else
					{
						cout << "\n\t\tRecord was NOT deleted. ";
					}
					break;
				case 3:
					//delete flight
					system("CLS");
					recSize = sizeof(flightRec);
					rewind(fileFlights);
					indexCount = 0;
					while (fread(&flightRec, recSize, 1, fileFlights) == 1)
					{
						cout << "\n\t\tIndex #" << indexCount;
						cout << flightRec.printFlight() << endl;
						aryFlights[indexCount] = flightRec;
						indexCount++;
					}

					indexNum = validateSelection("Please enter the index number: ", 0, indexCount - 1);

					prompt = "\n\t\tAre you sure you want to delete this index? ";
					confirm = validateYesNo(prompt);

					if ((confirm == 'y') || (confirm == 'Y'))
					{
						/*
						* add array records to a temp file,
						* skipping the record to be deleted.
						* delete original record.
						* rename temp file as orignal name.
						*/
						fileTemp = fopen("temp.txt", "w+");
						recSize = sizeof(flightRec);

						for (int x = 0; x < indexCount; x++)
						{
							if (x != indexNum)
							{
								try
								{
									fseek(fileTemp, 0, SEEK_END);
									fwrite(&aryFlights[x], recSize, 1, fileTemp);
								}
								catch (exception& e)
								{
									cout << e.what() << "\n";
								}
							}
						}

						fclose(fileTemp);
						fclose(fileFlights);
						remove("flightrecords.txt");
						rename("temp.txt", "flightrecords.txt");
						filePilots = fopen("flightrecords.txt", "a+"); //reopen the file for use

						cout << "\n\n\t\tRecord removed from file. ";
					}
					else
					{
						cout << "\n\t\tRecord was NOT deleted. ";
					}
					systemPause();
					break;
				default:
					;
				}
				systemPause();
			} while (menuSelection != 0);
			menuSelection = 1; //make a non-zero num so main does not exit
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
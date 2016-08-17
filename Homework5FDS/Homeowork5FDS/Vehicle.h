#pragma once
#ifndef VEHICLE_H
#define VEHICLE_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
using namespace std;

class Vehicle//class for the vehicles
{
public:
	Vehicle()//constructors
		: Producer("No Producer"), Model("No Model"), Year(0) {};

	string getProducer() { return Producer; }
	string getModel() { return Model; }

	//function initialization
	void addVehicle();
	bool checkVehicle();
	void printVehicle();

protected://data slots
	string Producer;
	string Model;
	int Year;
};

vector <Vehicle*> vehicleList;

void Vehicle::addVehicle() {
	cout << "Enter the producer you want to add:";//add vehicle
	cin >> Producer;
	cout << "Enter the model you want to add:";//add model
	cin >> Model;
	cout << "Enter the year of the vehicle:";//set the year of vehicle
	cin >> Year;
	while (Year < 1950 || Year > 2016)//a check the user inputs the correct year
	{
		cout << "Year has to be between 1950 and 2016, try again:";
		cin >> Year;
	}
}

bool Vehicle::checkVehicle()//check vehicle in vector
{
	cout << "Enter the vehicle you want to search parts for: ";
	string vehicle;
	cin >> vehicle;
	for (int i = 0; i < (int)vehicleList.size(); i++)
	{
		if (vehicleList.at(i)->getProducer() == vehicle)//check vehicle producer
		{
			cout << "Yes, we have parts for this vehicle, enter a model to check if we have parts for the specific model:";
			string model;
			cin >> model;
			for (int j = 0; j < (int)vehicleList.size(); j++)//check vehicle model
			{
				if (vehicleList.at(j)->getModel() == model) {
					return true;
				}
			}
			return false;
		}
	}
	return false;
}

void Vehicle::printVehicle() {//simple function to print vehicles in vector
	cout << "Producer:   Model:   Year:" << endl;
	for (int i = 0; i < (int)vehicleList.size(); i++)
	{
		cout << vehicleList.at(i)->Producer << setw(10) << vehicleList.at(i)->Model << setw(10) << vehicleList.at(i)->Year << endl;
	}
}
#endif // !VEHICLE_H
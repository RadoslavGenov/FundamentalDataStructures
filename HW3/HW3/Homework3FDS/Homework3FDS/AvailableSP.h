#pragma once
#ifndef AVAILABLESP_H
#define AVAILABLESP_H

#include <iostream>
#include <vector>
#include <string>
#include "Vehicle.h"
#include "SparePart.h"
using namespace std;

class Vehicle;
class SparePart;

class AvailableSP : public SparePart//Available Spare Part class
{
public:
	AvailableSP()
		: Location("no location") {}
	void addSparePart();
	void printAvailablePart();
	string getLocation() { return Location; }
protected:
	string Location;
};

void AvailableSP::addSparePart() {//add location with call to base function
	SparePart::addSparePart();
	cout << "Enter location:";
	cin >> Location;              //set location
}

void AvailableSP::printAvailablePart() {//simple function to print available parts list
	cout << "ID:  Name:  Quantity:  Price:  Status:  Location:  Producer:  Model:" << endl;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		cout << i << "    "
			<< partsList.at(i)->getName() << "    "
			<< partsList.at(i)->getQuantity() << "     "
			<< partsList.at(i)->getPrice() << "        "
			<< partsList.at(i)->getStatus() << "       "
			<< partsList.at(i)->getLocation() << "      "
			<< partsList.at(i)->getProducer() << "       "
			<< partsList.at(i)->getModel() << endl;
	}
}

#endif
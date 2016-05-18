#pragma once
#ifndef AVAILABLESP_H
#define AVAILABLESP_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
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
	void quickSort(vector<SparePart*>& partsList, int low, int high);
	void insertionSort(vector<SparePart*>& AvailableSP, int low, int high);
	void swap(SparePart* a, SparePart* b);
	vector<int> KMP(string text, string target);
	void checkDescription();
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
	cout << "ID:   Name:   Quantity:   Price:   Status:   Location:   Producer:   Model:   Description:" << endl;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		cout << i << setw(10)
			<< partsList.at(i)->getName() << setw(10)
			<< partsList.at(i)->getQuantity() << setw(10)
			<< partsList.at(i)->getPrice() << setw(10)
			<< partsList.at(i)->getStatus() << setw(10)
			<< partsList.at(i)->getLocation() << setw(10)
			<< partsList.at(i)->getProducer() << setw(10)
			<< partsList.at(i)->getModel() << setw(18)
			<< partsList.at(i)->getDescription() << endl;
	}
}

#endif
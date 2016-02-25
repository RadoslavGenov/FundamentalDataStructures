#pragma once
#ifndef CONTRACTEDSP_H
#define CONTRACTEDSP_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Vehicle.h"
#include "SparePart.h"
#include "AvailableSP.h"

using namespace std;

class Vehicle;
class SparePart;
class AvailableSP;

class ContractedSP : public AvailableSP {//class of Contracted Spare Parts 
public:
	ContractedSP()
		: vendor("no vendor"), time(0), delivery(0.0) {}
	string getVendor() { return vendor; }
	int getTime() { return time; }
	double getDelivery() { return delivery; }
	void contract();
	void calculateTotal(const vector <ContractedSP*> contractedList);
	void printContractedPart(const vector <ContractedSP*> contractedList);
private://data slots
	string vendor;
	int time;
	double delivery;
};

vector <ContractedSP*> contractedList;

void ContractedSP::calculateTotal(const vector <ContractedSP*> contractedList) {//calculating total cost of delivery and part
	cout << "Enter contracted part you want to check total of: ";
	string part;
	cin >> part;
	for (int i = 0; i < (int)contractedList.size(); i++)
	{
		if (contractedList.at(i)->getName() == part)
		{
			cout << "The total cost is: " << contractedList.at(i)->getPrice() + (contractedList.at(i)->addReplacement() * 20) + contractedList.at(i)->getDelivery();
			return;
		}
	}
	cout << "Oops, we do not have this part." << endl;//default
}

void ContractedSP::contract() {//setting values for data slots
	cout << "Enter the part you want to contract: ";
	string part;
	cin >> part;
	for (int i = 0; i < (int)partsList.size(); i++)//take current values of available parts and turn them into contracted parts
	{
		if (partsList.at(i)->getName() == part)
		{
			contractedList.back()->Name = partsList.at(i)->getName();
			contractedList.back()->Quantity = partsList.at(i)->getQuantity();
			contractedList.back()->Price = partsList.at(i)->getPrice();
			contractedList.back()->Status = partsList.at(i)->getStatus();
			contractedList.back()->Location = partsList.at(i)->getLocation();
			contractedList.back()->Model = partsList.at(i)->getModel();
			contractedList.back()->Producer = partsList.at(i)->getProducer();
			partsList.erase(partsList.begin() + i);
		}
	}
	cout << "Enter vendor: ";
	cin >> contractedList.back()->vendor;
	cout << "Enter the amount of time for delivery: ";
	cin >> contractedList.back()->time;
	cout << "Enter the delivery cost: ";
	cin >> contractedList.back()->delivery;
}

void ContractedSP::printContractedPart(const vector <ContractedSP*> contractedList) {//simple function to print contracted parts list
	cout << "ID:   Name:   Quantity:   Price:   Status:   Location:   Time:   Vendor:   Delivery Price:" << endl;
	for (int i = 0; i < (int)contractedList.size(); i++)
	{
		cout << i << setw(10)
			<< contractedList.at(i)->getName() << setw(10)
			<< contractedList.at(i)->getQuantity() << setw(10)
			<< contractedList.at(i)->getPrice() << setw(10)
			<< contractedList.at(i)->getStatus() << setw(10)
			<< contractedList.at(i)->getLocation() << setw(10)
			<< contractedList.at(i)->getTime() << setw(10)
			<< contractedList.at(i)->getVendor() << setw(10)
			<< contractedList.at(i)->getDelivery() << endl;
	}
}
#endif
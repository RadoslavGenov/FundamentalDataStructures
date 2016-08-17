#pragma once
#ifndef VENDOR_H
#define VENDOR_H

#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Vehicle.h"
#include "SparePart.h"
#include "AvailableSP.h"
#include "ContractedSP.h"
#include "Vendor.h"
#include "FilterSearch.h"

using namespace std;

class Vehicle;
class SparePart;
class AvailableSP;
class ContractedSP;

class Vendor//class for vendor
{
public:
	Vendor()
		: Name("no name"), Address("no address"), Phone("no phone") {};

	void addVendor();
	bool checkVendor(const vector<Vendor*>& vendorList);
private:
	string Name;
	string Address;
	string Phone;
	vector<string> deliveryList;
};

void Vendor::addVendor() {//function to add a new vendor
	cout << "Enter Name of Vendor: ";
	cin >> Name;
	cout << "Enter Address of Vendor: ";
	cin >> Address;
	cout << "Enter Phone of Vendor : ";
	cin >> Phone;
	cout << "Enter list of certified producers for the vendor: (type end to quit)";
	string read;
	cin >> read;
	while (read != "end") { deliveryList.push_back(read); cin >> read; }//fill producers
}

bool Vendor::checkVendor(const vector<Vendor*>& vendorList) {//check to see if there is a vendor 
	cout << "Enter the name of the vendor you want to check for: ";
	string name;
	cin >> name;
	for (size_t i = 0; i < (int)vendorList.size(); i++)
	{
		if (vendorList.at(i)->Name == name)//check name of vendor
		{
			return true;
		}
	}
	return false;
}

vector<Vendor*> vendorList;

#endif
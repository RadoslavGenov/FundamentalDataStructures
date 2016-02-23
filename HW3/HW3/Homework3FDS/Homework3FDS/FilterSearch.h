#pragma once
#ifndef FILTERSEARCH_H
#define FILTERSEARCH_H

#include <iostream>
#include <vector>
#include <string>
#include "Vehicle.h"
#include "SparePart.h"
#include "AvailableSP.h"
#include "Vendor.h"

using namespace std;

class Vehicle;
class SparePart;
class AvailableSP;
class ContractedSP;
class Vendor;

vector<SparePart*> searchWarrantyAndCondition() {//search by status
	vector <SparePart*> searchW;
	cout << "Do you want to search for 3 year warranties(New parts) or 3 month warranties(Used parts)? (3 year - 1 / 3 month - 0)";
	bool read;
	cin >> read;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		if (read) {
			if (partsList.at(i)->getStatus()) { searchW.push_back(partsList.at(i)); }//simple logic
		}
		if (!read) {
			if (!(partsList.at(i)->getStatus())) { searchW.push_back(partsList.at(i)); }
		}
	}
	return searchW;
};

vector<SparePart*> searchPrice() {//search by Price
	vector <SparePart*> searchPri;
	cout << "Enter the price filters, Minimum Price: ";
	double min;
	cin >> min;
	cout << "Enter Maximum Price: ";
	double max;
	cin >> max;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		if (partsList.at(i)->getPrice() <= max && partsList.at(i)->getPrice() >= min)//some logic
		{
			searchPri.push_back(partsList.at(i));
		}
	}
	return searchPri;
};

vector<SparePart*> searchProducer() {//search by Producer
	vector<SparePart*> searchProd;
	cout << "Enter the producer you want to filter parts for: ";
	string producer;
	cin >> producer;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		if (partsList.at(i)->getProducer() == producer)//some logic
		{
			searchProd.push_back(partsList.at(i));
		}
	}
	return searchProd;
}

vector<SparePart*> searchReplacementTime() {//search by Replacement Time
	vector<SparePart*> searchRT;
	cout << "Enter the replacement time you want to filter parts for, Minimum Time: ";
	int min;
	cin >> min;
	cout << "Maximum Time: ";
	int max;
	cin >> max;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		if (partsList.at(i)->getReplacement() <= max && partsList.at(i)->getReplacement() >= min)//some logic
		{
			searchRT.push_back(partsList.at(i));
		}
	}
	return searchRT;
};

void printResult(vector<SparePart*> results) {//print the result
	cout << "ID:  Name:  Quantity:  Price:  Status:  Location:  Producer:  Model:  Replacement Time:" << endl;
	for (int i = 0; i < (int)results.size(); i++)
	{
		cout << i << "    "
			<< results.at(i)->getName() << "    "
			<< results.at(i)->getQuantity() << "     "
			<< results.at(i)->getPrice() << "        "
			<< results.at(i)->getStatus() << "       "
			<< results.at(i)->getLocation() << "      "
			<< results.at(i)->getProducer() << "       "
			<< results.at(i)->getModel() << "       "
			<< results.at(i)->getReplacement() << endl;
	}
	cout << endl;
}

vector <SparePart*> searchMenu() {//search menu main function
	vector <SparePart*> results;
	int read;
	do
	{
		cout << "1. Search By Producer" << endl;
		cout << "2. Search By Price" << endl;
		cout << "3. Search By Warranty" << endl;
		cout << "4. Search By Replacement Time" << endl;
		cout << "0. Return to Main Menu" << endl;
		cout << "Choose an option: " << endl;
		cin >> read;
		switch (read) {
		case 1:
			results = searchProducer();
			printResult(results);
			break;
		case 2:
			results = searchPrice();
			printResult(results);
			break;
		case 3:
			results = searchWarrantyAndCondition();
			printResult(results);
			break;
		case 4:
			results = searchReplacementTime();
			printResult(results);
			break;
		case 0:
			break;
		default:
			cout << "Sorry we do not have that option!" << endl;
		}
	} while (read != 0);
	return results;//returns a vector 
}
#endif
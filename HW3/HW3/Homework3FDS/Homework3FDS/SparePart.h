#pragma once
#ifndef SPAREPART_H
#define SPAREPART_H

#include <iostream>
#include <vector>
#include <string>
#include "Vehicle.h"

using namespace std;

class Vehicle;

class SparePart : public Vehicle //class for the spare parts
{
public:
	SparePart()//constructor
		: Name(""), Price(0.0), Status(true), Replacement(0), Quantity(0) {};

	virtual string getName() { return Name; }
	virtual double getPrice() { return Price; }
	virtual bool getStatus() { return Status; }
	virtual int getQuantity() { return Quantity; }
	string getProducer() { return this->Producer; }
	string getModel() { return this->Model; }
	int getReplacement() { return Replacement; }

	void PriceToReplace(); //function initialization
	bool Warranty();
	int addReplacement();
	bool checkPart();
	void changeQuantity();
	void changeProducer();

	virtual void addSparePart();//virtual add part function used in bottom classes also
	virtual int getTime() { return 0; };
	virtual string getVendor() { return 0; };
	virtual double getDelivery() { return 0; };
	virtual string getLocation() { return 0; }
protected:   //data slots
	Vehicle car;
	string Name;
	double Price;
	bool Status;
	int Replacement;
	int Quantity;
};

vector <SparePart*> partsList;

void SparePart::changeProducer() {//change producer of Available Spare Part
	cout << "Enter the Name of the Available Part that you want to change Producer and Model of: ";
	string name;
	cin >> name;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		if (partsList.at(i)->Name == name)//logic  
		{
			cout << "Enter new Producer: ";//change of Producer and Model
			string newProducer;
			cin >> newProducer;
			partsList.back()->Producer = newProducer;
			cout << "Enter new Model: ";
			string newModel;
			cin >> newModel;
			partsList.back()->Model = newModel;
			return;
		}
	}
	cout << "Oops, we do not have this Available Part!" << endl;//default
}

void SparePart::changeQuantity() {//change quantity of a given part
	cout << "Enter the part that you want to change Quantity of: ";
	string name;
	cin >> name;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		if (partsList.at(i)->Name == name)//check for part
		{
			cout << "Enter the new quantity: ";
			int newQuantity;                    //change quantity
			cin >> newQuantity;
			partsList.at(i)->Quantity = newQuantity;
			return;
		}
	}
	cout << "We do not have this part in stock." << endl;//default
}

bool SparePart::checkPart()//check if part is in list 
{
	cout << "Enter the part you want to search for: ";
	string part;
	cin >> part;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		if (partsList.at(i)->Name == part)//some logic 
		{
			return true;
		}
	}
	return false;
}

int SparePart::addReplacement() {//add replaement
	cout << "Enter the replacement labour time required: ";
	cin >> Replacement;
	return Replacement;
}

void SparePart::PriceToReplace() {//price to replace part function
	cout << "Enter the part you want to find the cost of: ";
	string part;
	cin >> part;
	for (int i = 0; i < (int)partsList.size(); i++) {
		if (partsList.at(i)->Name == part)//check if part is in stock 
		{
			cout << "The price to replace is: " << partsList.at(i)->Price + (partsList.at(i)->addReplacement() * 20) << endl;
			return;
		}
	}
	cout << "Oops, we do not have this part!" << endl;//default
}

void SparePart::addSparePart() {//add spare part 
	cout << "Enter a Spare Part to add:";
	cin >> partsList.back()->Name;
	cout << "Enter a Quantity of Spare Part:";
	cin >> partsList.back()->Quantity;
	cout << "Enter price of part: ";
	cin >> partsList.back()->Price;
	cout << "Enter status of part, 1 for new, 0 for old: ";
	cin >> partsList.back()->Status;
	cout << "Enter what Producer this part is for: ";
	cin >> partsList.back()->Producer;
	cout << "Enter what Model this part is for: ";
	cin >> partsList.back()->Model;
	addReplacement();
}


bool SparePart::Warranty() {//calculate warranty
	cout << "Enter the part you want to check warranty for: ";
	string part;
	cin >> part;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		if (partsList.at(i)->getName() == part) //check for part
		{
			if (partsList.at(i)->Status)//check status
			{
				return true;
			}
			else {
				return false;
			}
		}
	}
	cout << "We do not have this part in stock." << endl;//default
	return false;
}
#endif // !SPAREPART_H

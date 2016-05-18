#include <iostream>
#include <vector>
#include <string>
//Author:Radoslav Genov
//FDS COS 221
using namespace std;

class Vehicle//class for the vehicles
{
public:
	Vehicle()//constructors
		: Producer("No Producer"), Model("No Model"), Year(0) {};

	string getProducer() { return Producer; }
	string getModel() { return Model; }

	virtual void addModel();//function initialization
	virtual void addVehicle();
	virtual int setYear();
	virtual bool checkVehicle(vector<Vehicle*>& vehicleList);
	virtual void printVehicle(vector<Vehicle*>& vehicleList);
private://data slots
	string Producer;
	string Model;
	int Year;
};

int Vehicle::setYear() {//set the year of vehicle
	cout << "Enter the year of the vehicle:";
	cin >> Year;
	while (Year < 1950 || Year > 2016)//a check the user inputs the correct year
	{
		cout << "Year has to be between 1950 and 2016, try again:";
		cin >> Year;
	}
	return Year;
}

void Vehicle::addModel() {//add model
	cout << "Enter the model you want to add:";
	cin >> Model;
}

void Vehicle::addVehicle() {//add vehicle
	cout << "Enter the producer you want to add:";
	cin >> Producer;
}

bool Vehicle::checkVehicle(vector<Vehicle*>& vehicleList)//check vehicle in vector
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

void Vehicle::printVehicle(vector<Vehicle*>& vehicleList) {//simple function to print vehicles in vector
	cout << "Producer:  Model:  Year:" << endl;
	for (int i = 0; i < (int)vehicleList.size(); i++)
	{
		cout << vehicleList.at(i)->Producer << "      " << vehicleList.at(i)->Model << "    " << vehicleList.at(i)->Year << endl;
	}
}

class SparePart //class for the spare parts
{
public:
	SparePart()//constructor
		: ID("No ID"), Name("No Name"), Description("No Description"), Price(0.0), Status(true),
		Replacement(0), Quantity(0) {};

	string getName() { return Name; }

	virtual void PriceToReplace(const vector<SparePart*>& spareList); //function initialization
	virtual void Warranty(const vector<SparePart*>& spareList);
	virtual string addSparePart();
	virtual void addQuantity();
	virtual double addPrice();
	virtual int addReplacement();
	virtual bool getStatus();
	virtual void printPart(const vector<SparePart*>& partsList);
	virtual bool checkPart(const vector<SparePart*>& partsList);
	virtual void addMoreQuantity(vector<SparePart*>& partsList);

private:   //data slots
	string ID;         //these will be used in the next
	string Description;//homeowork 
	string Name;
	double Price;
	bool Status;
	int Replacement;
	int Quantity;
};

void SparePart::addMoreQuantity(vector<SparePart*>& partsList) {//change quantity of a given part
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
bool SparePart::checkPart(const vector<SparePart*>& partsList)//check if part is in list 
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

bool SparePart::getStatus() {//add status
	cout << "Enter status of part, 1 for new, 0 for old: ";
	cin >> Status;
	return Status;
}

int SparePart::addReplacement() {//add replaement
	cout << "Enter the replacement labour time required: ";
	cin >> Replacement;
	return Replacement;
}

double SparePart::addPrice() {//add price
	cout << "Enter price of part: ";
	cin >> Price;
	return Price;
}

void SparePart::PriceToReplace(const vector<SparePart*>& spareList) {//price to replace part function
	cout << "Enter the part you want to find the cost of: ";
	string part;
	cin >> part;
	for (int i = 0; i < (int)spareList.size(); i++) {
		if (spareList.at(i)->Name == part)//check if part is in stock 
		{
			cout << "The price to replace is: " << spareList.at(i)->Price + (spareList.at(i)->addReplacement() * 20) << endl;
			return;
		}
	}
	cout << "Oops, we do not have this part!" << endl;//default
}

string SparePart::addSparePart() {//add spare part 
	cout << "Enter a Spare Part to add:";
	cin >> Name;
	return Name;
}

void SparePart::addQuantity() {//add quantity
	cout << "Enter a Quantity of Spare Part:";
	cin >> Quantity;
}

void SparePart::Warranty(const vector<SparePart*>& spareList) {//calculate warranty
	cout << "Enter the part you want to check warranty for: ";
	string part;
	cin >> part;
	for (int i = 0; i < (int)spareList.size(); i++)
	{
		if (spareList.at(i)->getName() == part) //check for part
		{
			if (spareList.at(i)->Status)//check status
			{
				cout << "The warranty is 3 years." << endl;
				return;
			}
			else {
				cout << "The warranty is 3 months." << endl;
				return;
			}
		}
	}
	cout << "We do not have this part in stock." << endl;//default
}

void SparePart::printPart(const vector<SparePart*>& partsList) {//simple function to print parts list
	cout << "Name:  Quantity:  Price:  Status:" << endl;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		cout << partsList.at(i)->Name << "     " << partsList.at(i)->Quantity << "        " << partsList.at(i)->Price << "       " << partsList.at(i)->Status << endl;
	}
}


void main() {
	vector<SparePart*> partsList;  //two vector to hold pointers to
	vector<Vehicle*> vehicleList;  //objects of type Vehicle and SparePart
	SparePart *part = new SparePart;//declare pointer to object type SparePart
	Vehicle *vehicle = new Vehicle;//declate pointer to object type Vehicle
	int read;
	do
	{
		cout << "Please Choose an option: " << endl;
		cout << "1. Add Vehicle           " << endl;
		cout << "2. Add Spare Part        " << endl;
		cout << "3. Check if Vehicle is in list " << endl;
		cout << "4. Check if Part is in list  " << endl;
		cout << "5. Calculate Replacement cost " << endl;
		cout << "6. Calculate Warranty" << endl;
		cout << "7. Print List of Vehicles " << endl;
		cout << "8. Print List of Spare Parts " << endl;
		cout << "9. Add more quantity of a part " << endl;
		cout << "0. Exit " << endl;
		cout << "Please Enter the number of the option: " << endl;

		cin >> read;
		switch (read)
		{
		case 1: //add vehicle 1.
			vehicleList.push_back(new Vehicle);
			vehicleList.back()->addVehicle();
			vehicleList.back()->addModel();
			vehicleList.back()->setYear();
			cout << endl;
			break;
		case 2:
			//add spare part 2.
			partsList.push_back(new SparePart);
			partsList.back()->addSparePart();
			partsList.back()->addQuantity();
			partsList.back()->addPrice();
			partsList.back()->getStatus();
			cout << endl;
			break;
		case 3:
			//check if vehicle is in list 2.
			if (vehicleList.size() != 0)
			{
				if (vehicle->checkVehicle(vehicleList)) { cout << "Yes, we do have spare parts for this vehicle." << endl; }
				else { cout << "No, we do not have spare parts for this vehicle." << endl; }
			}
			else
			{
				cout << "Oops, the list is empty. Add a vehicle first !" << endl;
			}
			cout << endl;
			break;
		case 4://check part 4.
			if (partsList.size() != 0)
			{
				if (part->checkPart(partsList)) { cout << "Yes, we have this part." << endl; }
				else { cout << "No, we do not have this part." << endl; }
			}
			else
			{
				cout << "Oops, the list is empty. Add a part first !" << endl;
			}
			cout << endl;
			break;
		case 5:
			//calculate replacement cost 5.
			if (partsList.size() != 0) { part->PriceToReplace(partsList); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 6:
			//calculate warranty 6.
			if (partsList.size() != 0) { part->Warranty(partsList); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 7:
			//print vehicles 7. 
			if (vehicleList.size() != 0) { vehicle->printVehicle(vehicleList); }
			else { cout << "Oops, the list is empty. Add a vehicle first !" << endl; }
			cout << endl;
			break;
		case 8:
			//print spare parts 8.
			if (partsList.size() != 0) { part->printPart(partsList); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 9:
			//add more quantity 9.
			if (partsList.size() != 0) { part->addMoreQuantity(partsList); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 0://exit
			break;
		default://default
			cout << "Sorry we do not have that option!" << endl;
			cout << endl;
		}
	} while (read != 0);


	//free memory
	for (int i = 0; i < (int)vehicleList.size(); i++)
	{
		delete vehicleList.at(i);
	}
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		delete partsList.at(i);
	}

	//delete contents of vectors
	partsList.clear();
	vehicleList.clear();
}

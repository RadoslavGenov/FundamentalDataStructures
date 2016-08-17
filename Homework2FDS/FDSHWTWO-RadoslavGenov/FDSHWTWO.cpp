#include <iostream>
#include <vector>
#include <string>
//Author:Radoslav Genov
//FDS COS 221 Homework 2
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
	bool checkVehicle(vector<Vehicle*>& vehicleList);
	void printVehicle(vector<Vehicle*>& vehicleList);

private://data slots
	string Producer;
	string Model;
	int Year;
};

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
		: Name(""), Price(0.0), Status(true), Replacement(0), Quantity(0), Location(""), Vendor(""), Time(0), Delivery(0.0) {};

	string getName() { return Name; }
	double getPrice() { return Price; }
	bool getStatus() { return Status; }
	int getQuantity() { return Quantity; }
	string getLocation() { return Location; }
	int getTime() { return Time; }
	double getDelivery() { return Delivery; }
	string getVendor() { return Vendor; }

	void PriceToReplace(const vector<SparePart*>& spareList); //function initialization
	void Warranty(const vector<SparePart*>& spareList);
	int addReplacement();
	bool checkPart(const vector<SparePart*>& partsList);
	void changeQuantity(vector<SparePart*>& partsList);
	void changeProducer(vector<SparePart*>& partsList);

	virtual void addSparePart();//virtual add part function used in bottom classes also

protected:   //data slots
	string Name;
	double Price;
	bool Status;
	int Replacement;
	int Quantity;
	string Location;
	string Vendor;
	int Time;
	double Delivery;
	string Producer;
	string Model;
};

void SparePart::changeProducer(vector<SparePart*>& partsList) {//change producer of Available Spare Part
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
			partsList.at(i)->Producer = newProducer;
			cout << "Enter new Model: ";
			string newModel;
			cin >> newModel;
			partsList.at(i)->Model = newModel;
			return;
		}
	}
	cout << "Oops, we do not have this Available Part!" << endl;//default
}

void SparePart::changeQuantity(vector<SparePart*>& partsList) {//change quantity of a given part
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

int SparePart::addReplacement() {//add replaement
	cout << "Enter the replacement labour time required: ";
	cin >> Replacement;
	return Replacement;
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

void SparePart::addSparePart() {//add spare part 
	cout << "Enter a Spare Part to add:";
	cin >> Name;
	cout << "Enter a Quantity of Spare Part:";
	cin >> Quantity;
	cout << "Enter price of part: ";
	cin >> Price;
	cout << "Enter status of part, 1 for new, 0 for old: ";
	cin >> Status;
	cout << "Enter what Producer this part is for: ";
	cin >> Producer;
	cout << "Enter what Model this part is for: ";
	cin >> Model;
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

class AvailableSP : public SparePart//Available Spare Part class
{
public:
	AvailableSP()
		: Location("no location") {}
	void addSparePart();
private:
	string Location;
};

void AvailableSP::addSparePart() {//add location with call to base function
	SparePart::addSparePart();
	cout << "Enter location:";
	cin >> Location;              //set location
	SparePart::Location = this->Location;
}

class ContractedSP : public AvailableSP {//class of Contracted Spare Parts 
public:
	ContractedSP()
		: vendor("no vendor"), time(0), delivery(0.0) {}
	string getVendor() { return Vendor; }
	void addSparePart();
	void calculateTotal(const vector<ContractedSP*>& list);
private://data slots
	string vendor;
	int time;
	double delivery;
};

void ContractedSP::calculateTotal(const vector<ContractedSP*>& list) {//calculating total cost of delivery and part
	cout << "Enter contracted part you want to check total of: ";
	string part;
	cin >> part;
	for (int i = 0; i < (int)list.size(); i++)
	{
		if (list.at(i)->getName() == part)
		{
			cout << "The total cost is: " << list.at(i)->Price + (list.at(i)->addReplacement() * 20) + list.at(i)->delivery;
			return;
		}
	}
	cout << "Oops, we do not have this part." << endl;//default
}

void ContractedSP::addSparePart() {//setting values for data slots
	AvailableSP::addSparePart();
	cout << "Enter vendor: ";
	cin >> vendor;
	SparePart::Vendor = this->vendor;
	cout << "Enter the amount of time for delivery: ";
	cin >> time;
	SparePart::Time = this->time;
	cout << "Enter the delivery cost: ";
	cin >> delivery;
	SparePart::Delivery = this->delivery;
}

void printAvailablePart(const vector<SparePart*>& partsList) {//simple function to print available parts list
	cout << "ID:  Name:  Quantity:  Price:  Status:  Location: " << endl;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		cout << i << "    "
			<< partsList.at(i)->getName() << "     "
			<< partsList.at(i)->getQuantity() << "        "
			<< partsList.at(i)->getPrice() << "       "
			<< partsList.at(i)->getStatus() << "     "
			<< partsList.at(i)->getLocation() << endl;
	}
}

void printContractedPart(const vector<ContractedSP*>& partsList) {//simple function to print contracted parts list
	cout << "ID:  Name:  Quantity:  Price:  Status:  Location:  Time:  Vendor:  Delivery Price:" << endl;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		cout << i << "    "
			<< partsList.at(i)->getName() << "     "
			<< partsList.at(i)->getQuantity() << "      "
			<< partsList.at(i)->getPrice() << "      "
			<< partsList.at(i)->getStatus() << "      "
			<< partsList.at(i)->getLocation() << "      "
			<< partsList.at(i)->getTime() << "       "
			<< partsList.at(i)->getVendor() << "     "
			<< partsList.at(i)->getDelivery() << endl;
	}
}

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

void main() {
	vector<SparePart*> partsList;  //two vector to hold pointers to
	vector<Vehicle*> vehicleList;  //objects of type Vehicle and SparePart
	vector<ContractedSP*> list;  //vector type ContractedSP
	vector<Vendor*> vendorList;

	Vendor *vendor = new Vendor;
	SparePart *part = new SparePart;//declare pointer to object type SparePart
	Vehicle *vehicle = new Vehicle;//declate pointer to object type Vehicle
	ContractedSP *con = new ContractedSP;//object of type ContractedSP so i can call functions

	int read;
	do
	{
		cout << "Please Choose an option: " << endl;
		cout << "1.  Add Vehicle           " << endl;
		cout << "2.  Add Available Spare Part        " << endl;
		cout << "3.  Add Contracted Part" << endl;
		cout << "4.  Add Vendor " << endl;
		cout << "5.  Check if Vehicle is in list " << endl;
		cout << "6.  Check if Part is in list  " << endl;
		cout << "7.  Calculate Replacement cost " << endl;
		cout << "8.  Calculate Warranty" << endl;
		cout << "9.  Print List of Vehicles " << endl;
		cout << "10. Print List of Available Spare Parts " << endl;
		cout << "11. Print List of Contracted Spare Parts " << endl;
		cout << "12. Add more quantity of a part " << endl;
		cout << "13. Calculate Total of Contracted Part " << endl;
		cout << "14. Check Vendor " << endl;
		cout << "15. Change Producer and Model of Available Spare Part " << endl;
		cout << "0.  Exit " << endl;
		cout << "Please Enter the number of the option: " << endl;

		cin >> read;
		switch (read)
		{
		case 1: //add vehicle 1.
			vehicleList.push_back(new Vehicle);
			vehicleList.back()->addVehicle();
			cout << endl;
			break;
		case 2:
			//add available spare part 2.
			partsList.push_back(new AvailableSP);
			partsList.back()->addSparePart();
			cout << endl;
			break;
		case 3:
			//add contracted part 3.
			if (partsList.size())
			{
				cout << "Please enter ID of the part you want to contract \nso it can be deleted from Available Spare Parts: \n(Part IDs start at 0, so the first part is 0)";
				int size = partsList.size() - 1;
				int ID;
				cin >> ID;
				while (ID < 0 || ID >= partsList.size()) {
					cout << "Oops, ID has to be between 0 and " << size << ", try again" << endl;
					cin >> ID;
				}
				partsList.erase(partsList.begin() + ID);//delete pointer
				cout << "Part succesfully deleted from AvailableSP, please re-enter the necessary information: " << endl;
				list.push_back(new ContractedSP);
				list.back()->addSparePart();
			}
			else {
				cout << "Oops, list of available spare parts is empty! Please add a part first, then you can contract the part." << endl;
			}
			break;
		case 4:
			//Add vendor 4.
			vendorList.push_back(new Vendor);
			vendorList.back()->addVendor();
			cout << endl;
			break;
		case 5:
			//check if vehicle is in list 5.
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
		case 6://check part 6.
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
		case 7:
			//calculate replacement cost 7.
			if (partsList.size() != 0) { part->PriceToReplace(partsList); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 8:
			//calculate warranty 8.
			if (partsList.size() != 0) { part->Warranty(partsList); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 9:
			//print vehicles 9. 
			if (vehicleList.size() != 0) { vehicle->printVehicle(vehicleList); }
			else { cout << "Oops, the list is empty. Add a vehicle first !" << endl; }
			cout << endl;
			break;
		case 10:
			//print available spare parts 10.
			if (partsList.size() != 0) { printAvailablePart(partsList); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 11:
			//print contracted spare parts 11.
			if (list.size() != 0) { printContractedPart(list); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 12:
			//change quantity 12.
			if (partsList.size() != 0) { part->changeQuantity(partsList); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 13:
			//calculate total for a contracted part 13.
			if (list.size()) { con->calculateTotal(list); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 14:
			//check vendor 14.
			if (vendorList.size()) {
				if (vendor->checkVendor(vendorList)) { cout << "We have that vendor!" << endl; }
				else { cout << "We do not have that vendor!" << endl; }
			}
			else { cout << "Oops, vendor list is empty please add a vendor first!" << endl; }
			cout << endl;
			break;
		case 15:
			//change producer and model 15.
			if (partsList.size()) { part->changeProducer(partsList); }
			else { cout << "Oops, please enter a part first!" << endl; }
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
	for (int i = 0; i < (int)vendorList.size(); i++)
	{
		delete vendorList.at(i);
	}
	for (int i = 0; i < (int)list.size(); i++)
	{
		delete list.at(i);
	}

	//delete contents of vectors
	partsList.clear();
	vehicleList.clear();
	vendorList.clear();
	list.clear();

	//delete pointers to objects
	delete vendor;
	delete part;
	delete vehicle;
	delete con;
}
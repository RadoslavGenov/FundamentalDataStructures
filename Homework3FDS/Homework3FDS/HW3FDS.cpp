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
	cout << "Producer:  Model:  Year:" << endl;
	for (int i = 0; i < (int)vehicleList.size(); i++)
	{
		cout << vehicleList.at(i)->Producer << "      " << vehicleList.at(i)->Model << "    " << vehicleList.at(i)->Year << endl;
	}
}

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
	cout << "ID:  Name:  Quantity:  Price:  Status:  Location:  Time:  Vendor:  Delivery Price:" << endl;
	for (int i = 0; i < (int)contractedList.size(); i++)
	{
		cout << i << "    "
			<< contractedList.at(i)->getName() << "     "
			<< contractedList.at(i)->getQuantity() << "      "
			<< contractedList.at(i)->getPrice() << "      "
			<< contractedList.at(i)->getStatus() << "      "
			<< contractedList.at(i)->getLocation() << "      "
			<< contractedList.at(i)->getTime() << "       "
			<< contractedList.at(i)->getVendor() << "     "
			<< contractedList.at(i)->getDelivery() << endl;
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

vector<Vendor*> vendorList;

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


void main() {
	Vendor *vendor = new Vendor;
	SparePart *part = new SparePart;//declare pointer to object type SparePart
	Vehicle *vehicle = new Vehicle;//declate pointer to object type Vehicle
	ContractedSP *con = new ContractedSP;//object of type ContractedSP so i can call functions
	AvailableSP *aPart = new AvailableSP;

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
		cout << "16. NEW: Search Parts Menu! " << endl;
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
				contractedList.push_back(new ContractedSP);
				contractedList.back()->contract();
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
			if (vehicleList.size())
			{
				if (vehicle->checkVehicle()) { cout << "Yes, we do have spare parts for this vehicle." << endl; }
				else { cout << "No, we do not have spare parts for this vehicle." << endl; }
			}
			else
			{
				cout << "Oops, the list is empty. Add a vehicle first !" << endl;
			}
			cout << endl;
			break;
		case 6://check part 6.
			if (partsList.size())
			{
				if (part->checkPart()) { cout << "Yes, we have this part." << endl; }
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
			if (partsList.size()) { part->PriceToReplace(); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 8:
			//calculate warranty 8.
			if (partsList.size()) {
				if (part->Warranty()) {
					cout << "The warranty is 3 years." << endl;
				}
				else {
					cout << "The warranty is 3 months." << endl;
				}
			}
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 9:
			//print vehicles 9. 
			if (vehicleList.size()) { vehicle->printVehicle(); }
			else { cout << "Oops, the list is empty. Add a vehicle first !" << endl; }
			cout << endl;
			break;
		case 10:
			//print available spare parts 10.
			if (partsList.size()) { aPart->printAvailablePart(); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 11:
			//print contracted spare parts 11.
			if (contractedList.size()) { con->printContractedPart(contractedList); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 12:
			//change quantity 12.
			if (partsList.size()) { part->changeQuantity(); }
			else { cout << "Oops, the list is empty. Add a part first !" << endl; }
			cout << endl;
			break;
		case 13:
			//calculate total for a contracted part 13.
			if (contractedList.size()) { con->calculateTotal(contractedList); }
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
			if (partsList.size()) { part->changeProducer(); }
			else { cout << "Oops, please enter a part first!" << endl; }
			break;
		case 16:
			searchMenu();
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
	for (int i = 0; i < (int)contractedList.size(); i++)
	{
		delete contractedList.at(i);
	}
	//delete contents of vectors
	partsList.clear();
	vehicleList.clear();
	vendorList.clear();
	contractedList.clear();

	//delete pointers to objects
	delete vendor;
	delete part;
	delete vehicle;
	delete con;
}
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
#include "QuickSort.h"
//Author:Radoslav Genov
//FDS COS 221 Homework 4
using namespace std;

void main() {
	Vendor *vendor = new Vendor;
	SparePart *part = new SparePart;//declare pointer to object type SparePart
	Vehicle *vehicle = new Vehicle;//declate pointer to object type Vehicle
	ContractedSP *con = new ContractedSP;//object of type ContractedSP so i can call functions
	AvailableSP *aPart = new AvailableSP;

	int read;
	do
	{
		cout << "Please Choose an option:" <<endl;
		cout << "1.  Add Vehicle" << endl;
		cout << "2.  Add Available Spare Part" << endl;
		cout << "3.  Add Contracted Part" << endl;
		cout << "4.  Add Vendor" << endl;
		cout << "5.  Check if Vehicle is in list" << endl;
		cout << "6.  Check if Part is in list" << endl;
		cout << "7.  Calculate Replacement cost" << endl;
		cout << "8.  Calculate Warranty" << endl;
		cout << "9.  Print List of Vehicles" << endl;
		cout << "10. Print List of Available Spare Parts" << endl;
		cout << "11. Print List of Contracted Spare Parts" << endl;
		cout << "12. Add more quantity of a part" << endl;
		cout << "13. Calculate Total of Contracted Part "<< endl;
		cout << "14. Check Vendor "<< endl;
		cout << "15. Change Producer and Model of Available Spare Part" << endl;
		cout << "16. NEW: Search Parts Menu!" << endl;
		cout << "17. NEW: QuickSort By Price!" << endl;
		cout << "0.  Exit" << endl;
		cout << "Please Enter the number of the option:" << endl;

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
			break;
		case 17:
			if (partsList.size()) { aPart->quickSort(partsList, 0, partsList.size() - 1); aPart->printAvailablePart(); }
			else { cout << "Oops, please enter a part first!" << endl; }
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
	delete aPart;
}
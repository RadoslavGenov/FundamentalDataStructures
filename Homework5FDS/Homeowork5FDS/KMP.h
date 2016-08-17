#pragma once
#ifndef KMP_H
#define KMP_H

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

class AvailableSP;

vector<int> AvailableSP::KMP(string text, string target)
{
	vector<int> Temp(target.size() + 1, -1);
	vector<int> matches;

	if (target.size() == 0)
	{
		matches.push_back(0);
		return matches;
	}
	for (int i = 1; i <= target.size(); i++)
	{
		int pos = Temp[i - 1];
		while (pos != -1 && target[pos] != target[i - 1]) pos = Temp[pos];
		Temp[i] = pos + 1;
	}

	int tfirst = 0;
	int tsecond = 0;
	while (tfirst < text.size())
	{
		while (tsecond != -1 && (tsecond == target.size() || target[tsecond] != text[tfirst])) tsecond = Temp[tsecond];
		tsecond++;
		tfirst++;
		if (tsecond == target.size()) matches.push_back(tfirst - target.size());
	}
	return matches;
}

void AvailableSP::checkDescription() {
	cout << "Enter the keyword you want to search for in the Descriptions: ";
	string pattern;
	cin >> pattern;
	for (int i = 0; i < (int)partsList.size(); i++)
	{
		if (AvailableSP::KMP(partsList.at(i)->getDescription(), pattern).size()) {
			cout << partsList.at(i)->getName() << " was found!" << endl;
			cout << "Do you want to contract the part? Y/N : ";
			string ans;
			cin >> ans;
			if (ans == "Y")
			{
				ContractedSP *contract = new ContractedSP;
				contract->KMPcontract(partsList.at(i)->getName());
				delete contract;
			}
			else 
			{
				return;
			}
		}
	}
}
#endif // !KMP_H

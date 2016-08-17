#pragma once
#ifndef QUICKSORT_H
#define QUICKSORT_H

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

void AvailableSP::swap(SparePart* a, SparePart* b) {//swap function to swap the values of two variables of type SparePart
	SparePart * temp = a;
	a = b;
	b = temp;
}

void AvailableSP::insertionSort(vector<SparePart*>& partsList, int low, int high) {//an insertion sort
	int j;                                                                         //if vector size is less than 10
	for (int p = low; p < high + 1; p++) {
		SparePart* temp = partsList.at(p);
		for (j = p; j > 0 && temp->getPrice() < partsList.at(j - 1)->getPrice(); j--) {
			partsList.at(j) = partsList.at(j - 1);
		}
		partsList.at(j) = temp;
	}
}

void AvailableSP::quickSort(vector<SparePart*>& partsList, int low, int high) {//quicksort through the vector 
	if (low + 10 > high) { insertionSort(partsList, low, high); }
	else {
		int middle = ((low + high) / 2);
		if (partsList.at(middle)->getPrice() < partsList.at(low)->getPrice()) { swap(partsList.at(low), partsList.at(middle)); }
		if (partsList.at(high)->getPrice() < partsList.at(low)->getPrice()) { swap(partsList.at(low), partsList.at(high)); }
		if (partsList.at(high)->getPrice() < partsList.at(middle)->getPrice()) { swap(partsList.at(middle), partsList.at(high)); }
		double pivot = partsList.at(middle)->getPrice();
		swap(partsList.at(middle), partsList.at(high - 1));
		int i, j;
		for (i = low, j = high - 1;;) {
			while (partsList.at(i++)->getPrice() < pivot) {}
			while (pivot < partsList.at(--j)->getPrice()) {}
			if (i < j) { swap(partsList.at(i), partsList.at(j)); }
			else break;
		}
		swap(partsList.at(i), partsList.at(high - 1));
		quickSort(partsList, low, i - 1); //recursive call 
		quickSort(partsList, i + 1, high);
	}
}
#endif // !QUICKSORT_H
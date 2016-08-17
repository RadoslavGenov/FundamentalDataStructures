#pragma once
#ifndef QUICKSORT_H
#define QUICKSORT_H
#include <iostream>
#include <vector>
#include <string>
#include "Character.h"

using namespace std;

void quickSort(vector<Character*>& enemies, int low, int high, int (Character::*get)());//using a pointer to function
void swap(Character*& a, Character*& b);

void sort(vector<Character*>& enemies) {
	int read;
	cout << "     Sort by:  " << endl;
	cout << " (1). Attack Points " << endl;
	cout << " (2). Health Points " << endl;
	cin >> read;
	while (read != 1 && read != 2) {
		cout << " Oops wrong input try again: ";
		cin >> read;
	}
	if (read == 1)
	{
		quickSort(enemies, 0, enemies.size() - 1, &Character::getAttack);//using a pointer to function
	}
	if (read == 2)
	{
		quickSort(enemies, 0, enemies.size() - 1, &Character::getHealth);//using a pointer to function
	}
}

void insertionSort(vector<Character*>& enemies, int low, int high, int (Character::*get)()) {
	int j;
	for (int p = low; p < high + 1; p++) {
		Character* tmp = enemies.at(p);
		for (j = p; j > 0 && (tmp->*get)() < (enemies.at(j - 1)->*get)(); j--)
			enemies.at(j) = enemies.at(j - 1);
		enemies.at(j) = tmp;
	}
}

void quickSort(vector<Character*>& enemies, int low, int high, int (Character::*get)()) {
	if (low + 10 > high) insertionSort(enemies, low, high, get);	// call insertion sort if there are less than 10 enemies
	else {
		int middle = (low + high) / 2;
		if ((enemies.at(middle)->*get)() < (enemies.at(low)->*get)()) swap(enemies.at(low), enemies.at(middle));
		if ((enemies.at(high)->*get)() < (enemies.at(low)->*get)())   swap(enemies.at(low), enemies.at(high));
		if ((enemies.at(high)->*get)() < (enemies.at(middle)->*get)())swap(enemies.at(middle), enemies.at(high));
		int pivot = (enemies.at(middle)->*get)();
		swap(enemies.at(middle), enemies.at(high - 1));
		int i, j;
		for (i = low, j = high - 1;;) {	//distribute the elements with regard to the pivot
			while ((enemies.at(++i)->*get)() < pivot) {}
			while (pivot < (enemies.at(--j)->*get)()) {}
			if (i < j) swap(enemies.at(i), enemies.at(j));
			else break;
		}
		swap(enemies.at(i), enemies.at(high - 1));       // put the pivot in its final place
		quickSort(enemies, low, i - 1, get);			 // sort the part left from the pivot
		quickSort(enemies, i + 1, high, get);			 // sort the part right from the pivot	
	}
}

void swap(Character*& a, Character*& b) {
	Character* tmp = a;
	a = b;
	b = tmp;
}
#endif // !QUICKSORT_H


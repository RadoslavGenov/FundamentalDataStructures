#pragma once
#ifndef VILLAIN_H
#define VILLAIN_H
#include <iostream>
#include <vector>
#include <string>
#include "Character.h"

using namespace std;

//Hierarchy Level 2
class Villain : public Character
{
public:
	Villain() {};
	void addCharacter();
};

void Villain::addCharacter() {
	Character::addCharacter();
	cout << " Enter attack points: (has to be between 25-30)";
	cin >> attack;
	while (attack > 30 || attack < 25)
	{
		cout << " Wrong input! Enter attack again: ";
		cin >> attack;
	}
	cout << " Enter health points: (has to be between 50-100)";
	cin >> health;
	while (health > 100 || health < 50)
	{
		cout << " Wrong input! Enter health again: ";
		cin >> health;
	}
	cout << " Enter desciption of character: ";
	cin.ignore();
	getline(cin, description);
}
#endif // !VILLAIN_H


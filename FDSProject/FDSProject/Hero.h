#pragma once
#ifndef HERO_H
#define HERO_H
#include <iostream>
#include <vector>
#include <string>
#include "Character.h"

using namespace std;

//Hierarchy Level 2
class Hero : public Character
{
public:
	Hero() {};
	void addCharacter();
};

void Hero::addCharacter() {
	Character::addCharacter();
	cout << " Enter attack points: (has to be between 20-25)";
	cin >> attack;
	while (attack > 25 || attack < 20)
	{
		cout << " Wrong input! Enter attack again: ";
		cin >> attack;
	}
	cout << " Enter health points: (has to be between 50-120)";
	cin >> health;
	while (health > 120 || health < 50)
	{
		cout << " Wrong input! Enter health again: ";
		cin >> health;
	}
	cout << " Enter desciption of character: ";
	cin.ignore();
	getline(cin, description);
}
#endif // !HERO_H

#pragma once
#ifndef CHARACTER_H
#define CHARACTER_H
#include <iostream>
#include <vector>
#include <string>

using namespace std;

//Hierarchy Level 1  
class Character
{
public:
	Character()
		: name(""), attack(0), health(0), description(""), death(false) {};
	//pure virtual function specialty
	virtual void setSpecialty() = 0;
	virtual void zeroSpecialty() = 0;
	virtual int getSpecialty() = 0;

	//virtual functions
	virtual void addCharacter();
	virtual void createRandEnemies(int rName, int rAttack, int rHealth);

	//getter functions
	string getName() { return name; }
	int getHealth() { return health; }
	int getAttack() { return attack; }
	bool getDeath() { return death; }

	//other
	bool fight(vector<Character*> enemies, Character* character);
protected:
	string name;
	int attack;
	int health;
	string description;
	bool death;
};

void Character::addCharacter() {
	cout << " Please enter the name of your Character: ";
	cin.ignore();
	getline(cin, name);
}

void Character::createRandEnemies(int rName, int rAttack, int rHealth) {
	switch (rName)
	{
	case 1: name = "Jack";
		break;
	case 2: name = "Sparrow";
		break;
	case 3: name = "Scorpion";
		break;
	case 4: name = "Kate";
		break;
	case 5: name = "Sub-Zero";
		break;
	case 6: name = "Cyclops";
		break;
	case 7: name = "Ghost";
		break;
	case 8: name = "Zombie";
		break;
	case 9: name = "Knight";
		break;
	case 10: name = "Samurai";
		break;
	default:
		break;
	}
	attack = rAttack;
	health = rHealth;
}

bool Character::fight(vector<Character*> enemies, Character* character) { //if true you lost fight; if false you won fight and beat enemies
	cout << "*     For every turn that occurs you can either attack your opponent or	   *" << endl;
	cout << "*     you can choose to defend, in both cases you opponent attacks you,	   *" << endl;
	cout << "*  but if you choose to defend, your opponents' attack inflicts less damage!  *" << endl;
	cout << endl;
	cout << "    You can either choose to (a)ttack or (d)efend: " << endl;
	char read;
	int i = 0;//increments through the enemies
	int round = 1;//keep track of rounds
	int count = enemies.size();//keeps count of the numbers of enemies you are fighting
	int tempHealth = character->health;//temp variable to hold health if character specialty is return from the dead
	character->setSpecialty();//set the specialty
	if (character->getSpecialty() == 2) { character->attack += 20; }//if specialty is 2, 20 more attack points are added
	if (character->getSpecialty() == 3) { character->health += 20; }//if specialty is 3, 20 more health points are added
	while (!character->getDeath() && i < enemies.size())
	{
		cout << endl;
		cout << " ROUND " << round << ". FIGHT! " << endl;
		cout << endl;
		cin >> read;
		if (read == 'a')
		{
			enemies.at(i)->health -= character->attack;
			character->health -= enemies.at(i)->attack;
			if (enemies.at(i)->health <= 0) { i++; count--; }//increment next enemy through vector and decrement the total number of the enemies
			if (character->health <= 0) {
				character->death = true;
				if (character->getSpecialty() == 1) {//if specialty is 1, return from the dead
					character->death = false;
					character->health = tempHealth;
					character->zeroSpecialty();
				}
			}
			cout << " Your health left: " << character->getHealth() << " Your attack power: " << character->getAttack() << " Opponenets left: " << count << endl;
		}
		if (read == 'd')
		{
			int temp = enemies.at(i)->attack;//some logic for the defending part of the game
			temp -= 2;
			character->health -= temp;
			if (enemies.at(i)->health <= 0) { i++; count--; }//increment next enemy through vector and decrement the total number of the enemies
			if (character->health <= 0)
			{
				character->death = true;
				if (character->getSpecialty() == 1) {//if specialty is 1, return from the dead
					character->death = false;
					character->health = tempHealth;
					character->zeroSpecialty();
				}
			}
			cout << " Your health left: " << character->getHealth() << " Your attack power: " << character->getAttack() << " Opponenets left: " << count << endl;
		}
		round++;//increment round
	}//some logic to continue the fighting loop
	if (character->getDeath()) { return true; } //character was killed!
	if (character->getHealth() > 0) { return false; } // you killed wave of enemies!
	return 0;
}
#endif // !CHARACTER_h

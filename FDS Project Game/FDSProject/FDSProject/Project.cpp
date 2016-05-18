#include <iostream>
#include <vector>
#include <string>
#include <iomanip>
#include "Character.h"
#include "Hero.h"
#include "Villain.h"
#include "Quicksort.h"
//FDS Individual Class Project Game
//Radoslav Genov
using namespace std;

//Hierarchy Level 3
class Samurai : public Hero
{
public:
	Samurai()
		: special(0) {};
	void addCharacter();
	void setSpecialty();
	void zeroSpecialty() { special = 0; }
	int getSpecialty() { return special; }
private:
	int special;
};

void Samurai::addCharacter() {
	Hero::addCharacter();
}

void Samurai::setSpecialty() {
	special = 1;
}

class Knight : public Hero
{
public:
	Knight()
		: special(0) {};
	void addCharacter();
	void setSpecialty();
	void zeroSpecialty() { special = 0; }
	int getSpecialty() { return special; }
private:
	int special;
};

void Knight::addCharacter() {
	Hero::addCharacter();
}

void Knight::setSpecialty() {
	special = 2;
}

class Zombie : public Villain
{
public:
	Zombie()
		: special(0) {};
	void addCharacter();
	void setSpecialty();
	void zeroSpecialty() { special = 0; }
	int getSpecialty() { return special; }
private:
	int special;
};

void Zombie::addCharacter() {
	Villain::addCharacter();
}

void Zombie::setSpecialty() {
	special = 1;
}

class Ghost : public Villain
{
public:
	Ghost()
		: special(0) {};
	void addCharacter();
	void setSpecialty();
	void zeroSpecialty() { special = 0; }
	int getSpecialty() { return special; }
private:
	int special;
};

void Ghost::addCharacter() {
	Villain::addCharacter();
}

void Ghost::setSpecialty() {
	special = 3;
}

vector<Character*> randEnemies();
Character* chooseCharacter();
void driver();

int main() {//loops while the user wants to continue
	int playAgain;
	do
	{
		driver();
		cout << endl;
		cout << " Would you like to play again? (1)YES/(0)NO: ";
		cin >> playAgain;
	} while (playAgain);
}

void driver() {//the driver of the game
	cout << endl;
	cout << " Welcome to Death Fighter! " << endl;
	cout << endl;
	Character* character = chooseCharacter();
	vector<Character*> enemies = randEnemies();
	vector<Character*> tempEnemies = enemies;

	cout << " Would you like to sort your enemies using QuickSort? (Y)es/(N)o " << endl;
	char read;
	cin >> read;
	if (read == 'Y') {
		//use different vector for quicksort so it does not to mess with gameplay
		sort(tempEnemies);
		cout << " The list of sorted enemies: " << endl;
		cout << " Health:     Name:     Attack: " << endl;
		for (size_t i = 0; i < tempEnemies.size(); i++)
		{
			cout << tempEnemies.at(i)->getHealth() << " " << setw(20) << tempEnemies.at(i)->getName() << setw(10) << tempEnemies.at(i)->getAttack() << endl;
		}
	}
	cout << " * LET THE FIGHT BEGIN! * " << endl;

	if (character->fight(enemies, character))//checks whether you won or lost
	{
		cout << endl;
		cout << " You lost the fight! " << endl;
	}
	else {
		cout << endl;
		cout << " You won the fight! " << endl;
	}

	delete character;
}

Character* chooseCharacter() {
	Character* character;

	cout << " Character Special Powers: " << endl;
	cout << endl;
	cout << " Samurai: returns from the dead! " << endl;
	cout << " Knight: gains 20 extra attack points! " << endl;
	cout << " Zombie: returns from the dead! " << endl;
	cout << " Ghost: gains 20 extra health points! " << endl;
	cout << endl;
	cout << " What character do you want to play as: (S)amurai, (K)night, (Z)ombie or (G)host: ";

	char name;
	cin >> name;
	while (name != 'S' && name != 'K' && name != 'Z' && name != 'G')
	{
		cout << " That is an incorrect choice. Try again! ";
		cin >> name;
	}
	if (name == 'S') {
		character = new Samurai;
		character->addCharacter();
		return character;
	}
	if (name == 'K') {
		character = new Knight;
		character->addCharacter();
		return character;
	}
	if (name == 'Z') {
		character = new Zombie;
		character->addCharacter();
		return character;
	}
	if (name == 'G') {
		character = new Ghost;
		character->addCharacter();
		return character;
	}
}

vector<Character*> randEnemies() {
	vector<Character*> enemy;
	cout << " Enter the number of enemies you want to fight: ";
	int n;
	cin >> n;
	for (int i = 0; i < n; i++)
	{
		int r = rand() % 4 + 1;
		switch (r)
		{
		case 1:
			enemy.push_back(new Samurai);
			break;
		case 2:
			enemy.push_back(new Knight);
			break;
		case 3:
			enemy.push_back(new Zombie);
			break;
		case 4:
			enemy.push_back(new Ghost);
			break;
		default:
			break;
		}
		enemy.back()->createRandEnemies(rand() % 10 + 1, rand() % 5 + 1, rand() % 10 + 1);
	}
	return enemy;
}
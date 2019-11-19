#include "Noble.h"
#include "Warrior.h"

#include <iostream>
#include <string>


using namespace std;


namespace WarriorCraft {
	ostream& operator<<(ostream& os, const Noble& rhs) {
		os << rhs.name << " has an army of " << rhs.army.size() << endl;
		for (size_t i = 0; i < rhs.army.size(); ++i) {
			os << *rhs.army[i];
		}
		return os;
	}

	//contructor
	Noble::Noble(const string& name) : name(name), armyStrength(0), isAlive(true) {}

	//get name
	const string& Noble::getName() const {
		return name;
	}


	//hire function
	bool Noble::hire(Warrior& warrior) {
		if (warrior.newMaster(*this) && isAlive) {
			armyStrength += warrior.getStrength();
			army.push_back(&warrior);
			return true;
		}
		return false;
	}

	//remove warrior
	bool Noble::removeWarrior(Warrior& warrior) {
		for (size_t i = 0; i < army.size(); ++i) {
			if (army[i] == &warrior) {
				armyStrength -= army[i]->getStrength();
				army[i]->removeMaster();
				swap(army[i], army[army.size() - 1]);
				army.pop_back();
				return true;
			}
		}
		return false;
	}



	//fire function
	bool Noble::fire(Warrior& warrior) {
		if (isAlive && removeWarrior(warrior)) {
			cout << warrior.getName() << ", you're fired! -- " << name << endl;
			return true;
		}
		return false;
	}

	//battle function
	void Noble::battle(Noble& opponent) {
		cout << name << " battles " << opponent.name << endl;
		//Conditions to find the outcome of the battle
		if (!isAlive && !opponent.isAlive) {
			cout << "Oh, NO! They're both dead! Yuck!\n";
		}
		else if (isAlive && !opponent.isAlive) {
			cout << "He's dead, " << name << endl;
		}
		else if (!isAlive && opponent.isAlive) {
			cout << "He's dead, " << opponent.name << endl;
		}
		else {
			if (armyStrength == opponent.armyStrength) {
				cout << "Mutual Annihilation: " << name << " and " << opponent.name << " die at each other's hands\n";
				for (size_t i = 0; i < army.size(); ++i) {
					army[i]->changeStrength(0);
				}
				for (size_t i = 0; i < opponent.army.size(); ++i) {
					opponent.army[i]->changeStrength(0);
				}
				armyStrength = 0;
				opponent.armyStrength = 0;
				isAlive = false;
				opponent.isAlive = false;
			}
			else if (armyStrength > opponent.armyStrength) {
				cout << name << " defeats " << opponent.name << endl;
				double ratio = opponent.armyStrength / armyStrength;
				for (size_t i = 0; i < army.size(); ++i) {
					army[i]->changeStrength(ratio);
				}
				for (size_t i = 0; i < opponent.army.size(); ++i) {
					opponent.army[i]->changeStrength(0);
				}
				armyStrength *= ratio;
				opponent.armyStrength = 0;
				opponent.isAlive = false;
			}
			else {
				cout << opponent.name << " defeats " << name << endl;
				double ratio = armyStrength / opponent.armyStrength;
				for (size_t i = 0; i < army.size(); ++i) {
					army[i]->changeStrength(0);
				}
				for (size_t i = 0; i < opponent.army.size(); ++i) {
					opponent.army[i]->changeStrength(ratio);
				}
				opponent.armyStrength *= ratio;
				armyStrength = 0;
				isAlive = false;
			}
		}
	}



}
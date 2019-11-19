#include "Warrior.h"
#include "Noble.h"
#include <iostream>
#include <string>
using namespace std;


namespace WarriorCraft {
	//operator overload
	ostream& operator<<(ostream& os, const Warrior& warrior) {
		os << "        " << warrior.name << ": " << warrior.strength << endl;
		return os;
	}

	//contructor
	Warrior::Warrior(const string& name, double str) : name(name), strength(str), master(nullptr) {}


	//name getter
	const string& Warrior::getName() const {
		return name;
	}

	//strength getter
	const double Warrior::getStrength() const {
		return strength;
	}

	//strength setter
	void Warrior::changeStrength(double ratio) {
		if (ratio == 0) {
			strength = 0;
		}
		else {
			strength = strength - strength*ratio;
		}
	}


	//set new noble
	bool Warrior::newMaster(Noble& noble) {
		if (master == nullptr) {
			master = &noble;
			return true;
		}
		return false;
	}

	//remove noble
	void Warrior::removeMaster() {
		master = nullptr;
	}

	//runaway function
	bool Warrior::runaway() {
		if (master != nullptr) {
			cout << name << " flees in terror, abandoning his lord, " << master->getName() << endl;
			master->removeWarrior(*this);
			return true;
		}
		return false;
	}

}
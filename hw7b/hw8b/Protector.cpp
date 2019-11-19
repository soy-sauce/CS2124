#include "Noble.h"
#include "Protector.h"
#include <iostream>
#include <string>

namespace WarriorCraft {

	Protector::Protector(const std::string& name, int strength)
		: name(name), strength(strength), master(nullptr) {}

	//get stren
	int Protector::getStrength() const {
		return strength;
	}

	//get name
	const std::string& Protector::getName() const {
		return name;
	}

	//set stren
	void Protector::changeStrength(double ratio) {
		if (ratio == 0) {
			strength = 0;
		}
		else {
			strength = strength - strength*ratio;
		}
	}

	//set noble
	void Protector::getNewMaster(Lord* master) {
		this->master = master;
	}

	//remove noble
	void Protector::removeMaster() {
		master = nullptr;
	}

	bool Protector::isHirable() const {
		return master == nullptr;
	}

	void Protector::quit() {
		master->fire(*this);
	}

	void Protector::warcry() {
		std::cout << name;
		std::cout << " says: Take that in the name of my lord, ";
		std::cout << master->getName() << std::endl;
	};

	void Wizard::warcry() {
		if (master) {
			std::cout << "POOF!" << std::endl;
		}
	}

	//void Warrior::warcry() {
		//std::cout << name;
		//std::cout << " says: Take that in the name of my lord, ";
		//std::cout << master->getName() << std::endl;
	//}

	void Archer::warcry() {
		if (master) {
			std::cout << "TWANG! ";
			Protector::warcry();
		}
	}

	void Swordsman::warcry() {
		if (master) {
			std::cout << "CLANG! ";
			Protector::warcry();
		}
	}

}
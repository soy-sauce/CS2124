#include "Noble.h"
#include "Protector.h"
#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {
	//prototypes
	void PersonWithStrengthToFight::changeArmyStrength(double) {}
	void PersonWithStrengthToFight::battleMessages() {}

	Noble::Noble(const std::string& name, int strength)
		: name(name), strength(strength), isAlive(true) {}

	const std::string& Noble::getName() const {
		return name;
	}

	void Noble::battle(Noble& opponent) {
		std::cout << name << " battles " << opponent.name << std::endl;


		//Battle outcomes
		if (!isAlive && !opponent.isAlive) {
			std::cout << "Oh, NO! They're both dead! Yuck!\n";
		}
		else if (isAlive && !opponent.isAlive) {
			std::cout << "He's dead, " << name << std::endl;
		}
		else if (!isAlive && opponent.isAlive) {
			std::cout << "He's dead, " << opponent.name << std::endl;
		}
		else {
			//print protector battle message
			this->battleMessages();
			opponent.battleMessages();
			if (strength == opponent.strength) {
				std::cout << "Mutual Annihilation: " << name << " and " << opponent.name << " die at each other's hands\n";
				this->changeArmyStrength(0);
				strength = 0;
				isAlive = false;
				opponent.changeArmyStrength(0);
				opponent.strength = 0;
				opponent.isAlive = false;
			}
			else if (strength > opponent.strength) {
				std::cout << name << " defeats " << opponent.name << std::endl;
				double ratio = opponent.strength / strength;
				this->changeArmyStrength(ratio);
				strength *= ratio;
				opponent.changeArmyStrength(0);
				opponent.strength = 0;
				opponent.isAlive = false;
			}
			else {
				std::cout << opponent.name << " defeats " << name << std::endl;
				double ratio = strength / opponent.strength;
				this->changeArmyStrength(0);
				strength = 0;
				isAlive = false;
				opponent.changeArmyStrength(ratio);
			}
		}
	}



	Lord::Lord(const std::string& name) : Noble(name, 0) {}

	//hire protector
	bool Lord::hires(Protector& protector) {
		if (protector.isHirable() && isAlive) {
			strength += protector.getStrength();
			protector.getNewMaster(this);
			army.push_back(&protector);
			return true;
		}
		return false;
	}

	//set strength
	void Lord::changeArmyStrength(double ratio) {
		for (size_t i = 0; i < army.size(); ++i) {
			army[i]->changeStrength(0);
		}
	}

	//battle messages
	void Lord::battleMessages() {
		for (Protector* protector : army) {
			protector->warcry();
		}
	}

	//fire protector
	bool Lord::fire(Protector& protector) {
		if (isAlive) {
			for (size_t i = 0; i < army.size(); ++i) {
				if (army[i] == &protector) {
					std::cout << army[i]->getName() << ", you're fired! -- " << name << std::endl;
					strength -= army[i]->getStrength();
					army[i]->removeMaster();
					std::swap(army[i], army[army.size() - 1]);
					army.pop_back();
					return true;
				}
			}
			return false;
		}
		return false;
	}
}
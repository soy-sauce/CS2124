//Connie Zhou
//cz1529
//HW 5

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Warrior {
public:

	//constructor
	Warrior(const string& name, double str) :name(name), strength(str) {}

	//display name and strength
	void display() const {
		cout << name << ": " << strength << endl;
	}

	//return name
	string getName() const {
		return name;
	}

	//return strength
	double getStren() const {
		return strength;
	}

	//modify strength
	void setStren(double ratio) {
		if (ratio == 0) {
			strength = 0;
		}
		else {
			strength -= (strength*ratio);
		}
	}

	//hires warrior
	void hire() {
		employed = true;
	}

	//fires warrior
	void fire() {
		employed = false;
	}

	bool isEmployed() {
		if (employed == true) {
			return true;
		}
		return false;
	}


private:
	const string name;
	double strength;
	bool employed;

};

class Noble {
public:
	//constructor
	Noble(const string& name) :name(name), armyStren(0), isAlive(true) {}

	//display noble and its army
	void display() const {
		cout << name << " has an army of " << army.size() << endl;
		for (size_t i = 0; i < army.size(); ++i) {
			cout << "\t";
			army[i]->display();
		}
	}

	//return name
	string getName() const {
		return name;
	}

	//checks if warrior in army
	bool inArmy(const string& warName) {
		for (size_t i = 0; i < army.size(); ++i) {
			if (army[i]->getName() == warName) {
				return true;

			}
		}
		return false;
	}

	//hires a warrior
	bool hire(Warrior& warrior) {
		if (isAlive) {
			armyStren += warrior.getStren();
			army.push_back(&warrior);
			warrior.hire();
			return true;
		}
		return false;
	}

	//fires a warrior
	bool fire(const string& warName) {
		if ((isAlive) && (inArmy(warName))) {
			for (size_t i = 0; i < army.size(); ++i) {
				if (army[i]->getName() == warName) {
					armyStren -= army[i]->getStren();
					swap(army[i], army[army.size() - 1]);
					army[army.size() - 1]->fire();
					army.pop_back();
					return true;

				}
			}
		}
		return false;
	}

	void battle(Noble& otherNoble) {
		cout << name << " battles " << otherNoble.getName() << endl;
		if (!isAlive && !otherNoble.isAlive) {
			cout << "Oh, NO! They're both dead! Yuck!\n";
		}
		else if (isAlive && !otherNoble.isAlive) {
			cout << "He's dead, " << name << endl;
		}
		else if (!isAlive && otherNoble.isAlive) {
			cout << "He's dead, " << otherNoble.name << endl;
		}
		else {
			if (armyStren == otherNoble.armyStren) {
				cout << "Mutual Annihilation: " << name << " and " << otherNoble.name << " die at each other's hands\n";
				for (size_t i = 0; i < army.size(); ++i) {
					army[i]->setStren(0);
				}
				for (size_t i = 0; i < otherNoble.army.size(); ++i) {
					otherNoble.army[i]->setStren(0);
				}
				armyStren = 0;
				otherNoble.armyStren = 0;
				isAlive = false;
				otherNoble.isAlive = false;
			}
			else if (armyStren > otherNoble.armyStren) {
				cout << name << " defeats " << otherNoble.name << endl;
				double ratio = otherNoble.armyStren / armyStren;
				for (size_t i = 0; i < army.size(); ++i) {
					army[i]->setStren(ratio);
				}
				for (size_t i = 0; i < otherNoble.army.size(); ++i) {
					otherNoble.army[i]->setStren(0);
				}
				armyStren *= ratio;
				otherNoble.armyStren = 0;
				otherNoble.isAlive = false;
			}
			else {
				cout << otherNoble.name << " defeats " << name << endl;
				double ratio = armyStren / otherNoble.armyStren;
				for (size_t i = 0; i < army.size(); ++i) {
					army[i]->setStren(0);
				}
				for (size_t i = 0; i < otherNoble.army.size(); ++i) {
					otherNoble.army[i]->setStren(ratio);
				}
				otherNoble.armyStren *= ratio;
				armyStren = 0;
				isAlive = false;
			}
		}
	}




private:
	const string name;
	bool isAlive;
	double armyStren;
	vector<Warrior*> army;
};



//error checking
//does noble already exist
bool nobleExist(const vector<Noble*>& nobles, const string& nName) {
	for (size_t i = 0; i < nobles.size(); ++i) {
		if (nobles[i]->getName() == nName) {
			return true;
		}
	}
	return false;
}

//does warrior already exist
bool warriorExist(const vector<Warrior*>& warriors, const string& wName) {
	for (size_t i = 0; i < warriors.size(); ++i) {
		if (warriors[i]->getName() == wName) {
			return true;
		}
	}
	return false;
}



void addNoble(vector<Noble*>& nobles, const string& nName) {
	if (!nobleExist(nobles, nName)) {
		nobles.push_back(new Noble(nName));
	}
	else {
		cout << nName << " exists already!" << endl;
	}
}

void addWarrior(vector<Warrior*>& warriors, const string& wName, int stren) {
	if (!warriorExist(warriors, wName)) {
		warriors.push_back(new Warrior(wName, stren));
	}
	else {
		cout << wName << " exists already!" << endl;
	}
}

bool HireAction(vector<Warrior*>& warriors, vector<Noble*>& nobles, const string& noble_name, const string& warrior_name) {
	for (size_t i = 0; i < nobles.size(); ++i) {
		if (nobles[i]->getName() == noble_name) {
			for (size_t j = 0; j < warriors.size(); ++j) {
				if (warriors[j]->getName() == warrior_name) {
					if (nobles[i]->hire(*warriors[j])) {
						//cout << warrior_name << " gets hired by " << noble_name << "!\n";
						swap(warriors[j], warriors[warriors.size() - 1]);
						warriors[warriors.size() - 1]->hire();
						return true;
					}
					else {
						cout << noble_name << " is dead already! They can't hire anymore!\n";
						return false;
					}
				}
			}
			cout << warrior_name << " doesn't exist or cannot be hired!\n";
			return false;
		}
	}
	cout << noble_name << " doesn't exist!\n";
	return false;
}

bool FireAction(vector<Noble*>& nobles, vector<Warrior*>& warriors, const string& nName, const string& wName) {
	for (size_t i = 0; i < nobles.size(); ++i) {
		if (nobles[i]->getName() == nName) {
			if (nobles[i]->inArmy(wName)) {
				if (nobles[i]->fire(wName)) {
					cout << "You don't work for me anymore " << wName << "! -- " << nName << endl;
					return true;
				}
			}
		}
	}
	cout << wName << " doesn't exist in " << nName << "'s army or " << nName << " is dead already!" << endl;
	return false;
}

void displayNobles(vector<Noble*>& nobles) {
	cout << "Nobles:\n";
	if (nobles.size() == 0) {
		cout << "NONE\n";
	}
	else {
		for (size_t i = 0; i < nobles.size(); ++i) {
			nobles[i]->display();
		}
	}
}

void displayUnemployedWarriors(vector<Warrior*>& warriors) {
	bool noUnemployed = true;
	cout << "Unemployed Warriors:\n";
	for (size_t i = 0; i < warriors.size(); ++i) {
		if (!warriors[i]->isEmployed()) {
			noUnemployed = false;
			warriors[i]->display();
		}
	}
	if (noUnemployed == true) {
		cout << "NONE" << endl;
	}
}

void battleAction(vector<Noble*>& nobles, const string& noble1, const string& noble2) {
	for (size_t i = 0; i < nobles.size(); ++i) {
		if (nobles[i]->getName() == noble1) {
			for (size_t j = 0; j < nobles.size(); ++j) {
				if (nobles[j]->getName() == noble2) {
					nobles[i]->battle(*nobles[j]);
					return;
				}
			}
			cout << noble2 << " do not exist!" << endl;
			return;
		}
	}
	cout << noble1 << " do not exist!" << endl;
	return;
}

void clearAction(vector<Noble*>& nobles, vector<Warrior*>& warriors) {
	for (size_t i = 0; i < nobles.size(); ++i) {
		delete nobles[i];
	}
	nobles.clear();
	for (size_t i = 0; i < warriors.size(); ++i) {
		delete warriors[i];
	}
	warriors.clear();
}


int main() {
	vector<Noble*> nobles;
	vector<Warrior*> warriors;
	string action, noble_name, warrior_name;
	int strength;

	ifstream ifs("warrior.txt");
	if (!ifs) {
		cerr << "Could not open the file.\n";
		exit(1);
	}

	while (ifs >> action) {
		if (action == "Noble") {
			ifs >> noble_name;
			addNoble(nobles, noble_name);
		}
		else if (action == "Warrior") {
			ifs >> warrior_name >> strength;
			addWarrior(warriors, warrior_name, strength);
		}
		else if (action == "Hire") {
			ifs >> noble_name >> warrior_name;
			HireAction(warriors, nobles, noble_name, warrior_name);
		}
		else if (action == "Fire") {
			ifs >> noble_name >> warrior_name;
			FireAction(nobles, warriors, noble_name, warrior_name);
		}
		else if (action == "Status") {
			cout << "Status\n" << "======" << endl;
			displayNobles(nobles);
			displayUnemployedWarriors(warriors);
		}
		else if (action == "Battle") {
			ifs >> noble_name >> warrior_name;
			battleAction(nobles, noble_name, warrior_name);
		}
		else if (action == "Clear") {
			clearAction(nobles, warriors);
		}
	}
	ifs.close();
}




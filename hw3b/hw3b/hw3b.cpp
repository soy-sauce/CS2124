//Connie Zhou
//cz1529
//CS2124 HW 3


#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

class Warrior {
	//display operator
	friend ostream& operator<<(ostream& os,const Warrior& rhs) {
		os << "Warrior: " << rhs.name << ", weapon: " << rhs.aWeapon.getWepName() << ", " 
			<< rhs.aWeapon.getWepStren() << endl;
		return os;
	}

	//weapon class
	class Weapon {

	public:
		Weapon(string wName, int strength) :name(wName), strength(strength) {}

		string getWepName() const {
			return name;
		}

		int getWepStren() const {
			return strength;
		}

		void setStren(int newstren) {
			strength = newstren;
		}


	private:
		string name;
		int strength;
	};

private:
	string name;
	Weapon aWeapon;


public:
	Warrior(const string name, const string& weapon, int strength) : name(name), aWeapon(weapon, strength) {}

	string getName() const {
		return name;
	}

	string getWep() const {
		return aWeapon.getWepName();
	}

	int getStren() const {
		return aWeapon.getWepStren();
	}

	//takes in a opponent name and finds it
	void doBattle(vector<Warrior>& warriors,const string& warrior2) {
		int opponent;

		for (size_t i = 0; i < warriors.size(); ++i) {
			if (warriors[i].name == warrior2) {
				opponent = i;
			}
		}

		cout << name << " battles " << warriors[opponent].name << endl;


		//checks if anyone is dead before battle
		if (aWeapon.getWepStren() == 0 && warriors[opponent].aWeapon.getWepStren() == 0) {
			cout << "Oh, NO! They're both dead! Yuck!" << endl;
		}
		else if (aWeapon.getWepStren() > 0 && warriors[opponent].aWeapon.getWepStren() == 0) {
			cout << "He's Dead, " << name << endl;
		}
		else if (aWeapon.getWepStren() == 0 && warriors[opponent].aWeapon.getWepStren() > 0) {
			cout << "He's Dead, " << warriors[opponent].name << endl;
		}


		//no dead warriors, continue
		else {
			int minusStrength = aWeapon.getWepStren();
			aWeapon.setStren(aWeapon.getWepStren() - warriors[opponent].aWeapon.getWepStren());
			warriors[opponent].aWeapon.setStren(aWeapon.getWepStren() - aWeapon.getWepStren());

			if (aWeapon.getWepStren() < 0) {
				aWeapon.setStren(0); //corrector if strength is negative
			}
			else if (warriors[opponent].aWeapon.getWepStren() < 0) {
				warriors[opponent].aWeapon.setStren(0); //corrector is strength is negative
			}

			if (aWeapon.getWepStren() > warriors[opponent].aWeapon.getWepStren()) {
				cout << name << " defeats " << warriors[opponent].name << endl;
			}

			else if (aWeapon.getWepStren() < warriors[opponent].aWeapon.getWepStren()) {
				cout << name << " defeats " << warriors[opponent].name << endl;
			}
			else if (aWeapon.getWepStren() == warriors[opponent].aWeapon.getWepStren()) {
				cout << "Mutual Annihilation: " << name << " and " << warriors[opponent].name << " die at each other's hands" << endl;
			}
		}
	}








};

void displayStatus(const vector<Warrior>& warriors) {

	cout << "There are: " << warriors.size() << " warriors" << endl;
	for (size_t i = 0; i < warriors.size(); i++) {
		cout << warriors[i] << endl;
	}
}


int main() {
	string type;
	string name;
	int strength;
	string weapon;

	string warrior1;
	string warrior2;
	string battles;
	vector<Warrior> warriors;

	ifstream ifs("warriors.txt");
	if (!ifs) {
		cerr << "failed to open warriors";
		exit(1);
	}

	while (ifs >> type) {

		if (type == "Warrior") {
			ifs >> name >> weapon >> strength;
			Warrior newPerson(name, weapon, strength);
			warriors.push_back(newPerson);
		}


		if (type == "Battle") {
			ifs >> warrior1 >> warrior2;

			//for battle go through all and enter warrior 2 as parameter
			for (size_t i = 0; i < warriors.size(); ++i) {

				if (warriors[i].getName() == warrior1) {
					Warrior war1 = warriors[i];
					war1.doBattle(warriors, warrior2);
					break;
				}

			}

			
			//end


		}

		if (type == "Status") {
			displayStatus(warriors);
		}



	}
	ifs.close();
}











//Connie Zhou
//cz1529
//CS2124 HW 2


#include <iostream>
#include <vector>
#include <string>
#include <fstream>

using namespace std;

struct Warrior {
	string name;
	int strength;
};


void openFile(ifstream& ifs,const string& file);
void displayStatus(const vector<Warrior>& warriors);
void readFile(vector<Warrior>& warriors, ifstream& ifs);
void addWarrior(vector<Warrior>& warriors,const string& name, int strength);
void doBattle(vector<Warrior>& warriors,const string& warrior1, const string& warrior2);



int main() {
	vector<Warrior> warriors;

	ifstream ifs;
	openFile(ifs, "warrior.txt");
	readFile(warriors, ifs);

}

//open the file
void openFile(ifstream& ifs,const string& file) {
	ifs.open(file);

	while (!ifs) {
		cerr << "failed to open file\n";
		exit(1);
	}
}

//add warrior to collection of warriors
void addWarrior(vector<Warrior>& warriors, const string& name, int strength) {
	Warrior newPerson;
	newPerson.name = name;
	newPerson.strength = strength;
	warriors.push_back(newPerson);
}

//read the file to add warriors, do battles, and display
void readFile(vector<Warrior>& warriors, ifstream& ifs) {
	string type;
	string name;
	int strength;

	string warrior1;
	string warrior2;
	string battles;

	while (ifs >> type) {

		if (type == "Warrior") {
			ifs >> name >> strength;
			addWarrior(warriors, name, strength);
		}


		if (type == "Battle") {
			ifs >> warrior1 >> warrior2;
			doBattle(warriors, warrior1, warrior2);
		}

		if (type == "Status") {
			displayStatus(warriors);
		}



	}
	ifs.close();
}

//will battle two warriors against each other
void doBattle(vector<Warrior>& warriors, const string& warrior1, const string& warrior2) {

	int person1;
	int person2;

	for (size_t i = 0; i < warriors.size(); ++i) {
		if (warriors[i].name == warrior1) {
			person1 = i;
		}
		else if (warriors[i].name == warrior2) {
			person2 = i;
		}
	}

	cout << warriors[person1].name << " battles " << warriors[person2].name << endl;


	//checks if anyone is dead before battle
	if (warriors[person1].strength == 0 && warriors[person2].strength == 0) {
		cout << "Oh, NO! They're both dead! Yuck!" << endl;
	}
	else if (warriors[person1].strength > 0 && warriors[person2].strength == 0) {
		cout << "He's Dead, " << warriors[person1].name << endl;
	}
	else if (warriors[person1].strength == 0 && warriors[person2].strength > 0) {
		cout << "He's Dead, " << warriors[person2].name << endl;
	}


	//no dead warriors, continue
	else {
		int minusStrength = warriors[person1].strength;
		warriors[person1].strength = warriors[person1].strength - warriors[person2].strength;
		warriors[person2].strength = warriors[person1].strength - warriors[person1].strength;

		if (warriors[person1].strength < 0) {
			warriors[person1].strength = 0; //corrector if strength is negative
		}
		else if (warriors[person2].strength < 0) {
			warriors[person2].strength = 0; //corrector is strength is negative
		}

		if (warriors[person1].strength > warriors[person2].strength) {
			cout << warriors[person1].name << " defeats " << warriors[person2].name << endl;
		}

		else if (warriors[person1].strength < warriors[person2].strength) {
			cout << warriors[person1].name << " defeats " << warriors[person2].name << endl;
		}
		else if (warriors[person1].strength == warriors[person2].strength) {
			cout << "Mutual Annihilation: " << warriors[person1].name << " and " 
				<< warriors[person2].name << " die at each other's hands" << endl;
		}
	}
}

//display warriors and their info
void displayStatus(const vector<Warrior>& warriors) {
	cout << "There are: " << warriors.size() << " warriors" << endl;
	for (size_t i = 0; i < warriors.size(); i++) {
		cout << "Warrior: " << warriors[i].name << ", strength: " << warriors[i].strength << endl;
	}

}



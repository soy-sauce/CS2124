//Connie Zhou
//cz1529
//HW04

#include <vector>
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

class Warrior;
class Noble;


//warrior class
class Warrior {
public:
	Warrior(const string& name, int strength) :wName(name), strength(strength), employed(false) {}

	//return name
	string getName() const {
		return wName;
	}

	//return strength
	int getStren() const {
		return strength;
	}

	//set strength
	void setStren(int newStren) {
		strength = newStren;
	}

	//display name and strength
	void display() const {
		cout << wName << ": " << strength;
	}

	//return true is hire, false if not hired
	bool isEmployed() const {
		return employed;
	}

	//hire warrior
	void hire() {
		employed = true;
	}
	//fire warrior
	void fire() {
		employed = false;
	}
private:
	string wName;
	int strength;
	bool employed;

};

class Noble {
public:

	Noble(const string& name) :nName(name), alive(true) {}

	//return name
	string getName() const {
		return nName;
	}

	//check if warrior in army
	bool isInArmy(const Warrior& warrior)const {
		for (size_t i = 0; i < army.size(); i++) {
			if (army[i] == &warrior) {
				return true;
			}
		}
		return false;
	}

	int findWarrior(const Warrior& warrior)const {
		for (size_t i = 0; i < army.size(); i++) {
			if (army[i] == &warrior) {
				return i;
			}
		}
		return -1;
	}


	//hire warrior, returns bool to prevent silent fail
	bool hire(Warrior& warrior) {
		//cant employ if already employed or noble is dead
		if (warrior.isEmployed() || !alive) {
			return false;
		}
		Warrior* aWarrior = &warrior;
		army.push_back(aWarrior);
		warrior.hire();
		return true;
	}

	//fire warrior from army
	bool fire(Warrior& warrior) {
		//cant fire if warrior is not in army or noble is dead
		if ((isInArmy(warrior)==-1) || !alive) {
			return false;
		}
		cout << warrior.getName() << ", you're fired! --" << nName << endl;
		warrior.fire();

		//have to move to end to delete and popback
		for (size_t i = 0; i < army.size(); i++) {
			if (army[i] == &warrior) {
				Warrior* temp = army[i];
				army[i] = army[army.size() - 1];
				army[army.size() - 1] = temp;
				temp = nullptr;
				army.pop_back();
				break;
			}

		}
		return true;
	}

	//display noble and army
	void display() const {

		cout << nName << " has an army of " << army.size() << endl;
		for (size_t i = 0; i < army.size(); i++) {
			cout << "\t" << army[i]->getName() << ": " << army[i]->getStren() << endl;
		}
	}

	//do the battle
	void battle(Noble& otherNoble) {
		cout << nName << " battles " << otherNoble.getName() << endl;

		//both alive
		if (alive && otherNoble.alive)
		{
			//total strength of army1
			int resStrength1 = 0;
			for (size_t i = 0; i < army.size(); i++)
			{
				resStrength1 += army[i]->getStren();
			}

			//total strength of army2
			int resStrength2 = 0;
			for (size_t i = 0; i < otherNoble.army.size(); i++)
			{
				resStrength2 += otherNoble.army[i]->getStren();
			}

			//both groups die
			if (resStrength1 == resStrength2)
			{
				//group 1 dead
				alive = false;
				for (size_t i = 0; i < army.size(); i++)
				{
					army[i]->setStren(0);
				}

				//group 2 dead
				otherNoble.alive = false;
				for (size_t i = 0; i < otherNoble.army.size(); i++)
				{
					otherNoble.army[i]->setStren(0);
				}

				cout << "Mutual Annihilation : " << nName << " and " << otherNoble.nName << " die at each other's hands \n";
			}

			//group 1 died
			else if (resStrength2 > resStrength1)
			{
				//group 1 dead
				alive = false;
				for (size_t i = 0; i < army.size(); i++)
				{
					army[i]->setStren(0);
				}

				double dmgRatio = 1 - double(resStrength1) / resStrength2;

				//apply damage to army 2
				for (size_t i = 0; i < otherNoble.army.size(); i++)
				{
					int newStrength = otherNoble.army[i]->getStren() * dmgRatio;
					otherNoble.army[i]->setStren(newStrength);
				}

				cout << otherNoble.nName << " defeats "
					<< nName << endl;
			}

			//group 2 died
			else //(resStrength1 > resStrength2)
			{
				//group 2 dead
				otherNoble.alive = false;
				for (size_t i = 0; i < otherNoble.army.size(); i++)
				{
					otherNoble.army[i]->setStren(0);
				}

				double dmgRatio = 1 - double(resStrength2) / resStrength1;

				//apply damage to army 1 - round down
				for (size_t i = 0; i < army.size(); i++)
				{
					int newStrength = army[i]->getStren() * dmgRatio;
					army[i]->setStren(newStrength);
				}

				cout << nName << " defeats "
					<< otherNoble.nName << endl;
			}
		}

		//noble1 alive while noble2 already dead
		else if (alive && !(otherNoble.alive))
		{
			cout << "He's dead, " << nName << endl;
		}

		//noble2 alive while noble1 already dead
		else if (!(alive) && otherNoble.alive) {
			cout << "He's dead, " << otherNoble.nName << endl;
		}

		//both nobles already dead
		else { // ( !(alive) && !(royal.alive))
			cout << "Oh, NO! They're both dead! Yuck! \n";
		}
	}

private:
	string nName;
	bool alive;
	vector <Warrior*> army;

};




int main()
{
	Noble art("King Arthur");
	Noble lance("Lancelot du Lac");
	Noble jim("Jim");
	Noble linus("Linus Torvalds");
	Noble billie("Bill Gates");

	Warrior cheetah("Tarzan", 10);
	Warrior wizard("Merlin", 15);
	Warrior theGovernator("Conan", 12);
	Warrior nimoy("Spock", 15);
	Warrior lawless("Xena", 20);
	Warrior mrGreen("Hulk", 8);
	Warrior dylan("Hercules", 3);

	jim.hire(nimoy);
	lance.hire(theGovernator);
	art.hire(wizard);
	lance.hire(dylan);
	linus.hire(lawless);
	billie.hire(mrGreen);
	art.hire(cheetah);

	jim.display();
	lance.display();
	art.display();
	linus.display();
	billie.display();

	art.fire(cheetah);
	art.display();

	art.battle(lance);
	jim.battle(lance);
	linus.battle(billie);
	billie.battle(lance);
}
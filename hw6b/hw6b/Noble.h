#ifndef NOBLE_H //if not defined then define, if it is, go to #endif
#define NOBLE_H

#include <string>
#include <vector>
#include<iostream>

//using namespace std; //namespace pollution
namespace WarriorCraft {
	class Warrior;

	class Noble {
		friend std::ostream& operator<<(std::ostream& os, const Noble& noble);
	public:
		Noble(const std::string& name);
		bool hire(Warrior& warrior);
		bool fire(Warrior& warrior);
		void battle(Noble& opponent);
		bool Noble::removeWarrior(Warrior& warrior);
		const std::string& getName() const;
	private:
		const std::string name;
		bool isAlive;
		double armyStrength;
		std::vector<Warrior*> army;
	};//Noble class

}
#endif

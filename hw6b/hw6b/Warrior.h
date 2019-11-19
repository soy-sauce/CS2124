#ifndef WARRIOR_H //if not defined then define, if it is, go to #endif
#define WARRIOR_H


#include <string>
#include <vector>
#include<iostream>

//using namespace std; //namespace pollution
namespace WarriorCraft {
	class Noble;


	//warrior class
	class Warrior {
		friend std::ostream& operator<<(std::ostream& os, const Warrior& warrior);


	public:
		Warrior(const std::string& name, double str);
		const std::string& getName() const;
		const double getStrength() const;
		void changeStrength(double ratio);
		bool newMaster(Noble& noble);
		void removeMaster();
		bool runaway();


	private:
		const std::string name;
		double strength;
		Noble* master;

	};
}
#endif

#include <iostream>
#include <string>
#include <vector>

namespace WarriorCraft {

	class Protector;

	class Noble {
	public:
		Noble(const std::string& name, int strength);
		const std::string& getName() const;
		virtual void battle(Noble& opponent);
		virtual void changeArmyStrength(double ratio) = 0;
		virtual void battleMessages() = 0;
	protected:
		const std::string name;
		bool isAlive;
		int strength;
	};

	class PersonWithStrengthToFight : public Noble {
	public:
		using Noble::Noble;
		void changeArmyStrength(double);
		void battleMessages();
	};

	class Lord : public Noble {
	public:
		Lord(const std::string& name);
		bool hires(Protector& protector);
		using Noble::battle;
		void changeArmyStrength(double ratio);
		void battleMessages();
		bool fire(Protector& protector);
	private:
		std::vector<Protector*> army;
	};

}
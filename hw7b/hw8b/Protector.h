#include <iostream>
#include <string>

namespace WarriorCraft {

	class Lord;

	class Protector {
	public:
		Protector(const std::string& name, int strength);
		int getStrength() const;
		const std::string& getName() const;
		void changeStrength(double ratio);
		void getNewMaster(Lord* master);
		void removeMaster();
		bool isHirable() const;
		virtual void warcry();
		void quit();
	protected:
		const std::string name;
		int strength;
		Lord* master;
	};

	class Wizard : public Protector {
	public:
		using Protector::Protector;
		void warcry();
	};

	class Warrior : public Protector {
	public:
		using Protector::Protector;
		//void warcry();
	};

	class Archer : public Warrior {
	public:
		using Warrior::Warrior;
		void warcry();
	};

	class Swordsman : public Warrior {
	public:
		using Warrior::Warrior;
		void warcry();
	};

}
#include <vector>
#include <iostream>
using namespace std;

class Instrument {
private:
public:
	virtual void makeSound() = 0;
	virtual void play() = 0;

};

void Instrument::makeSound() {
	cout << "To make a sound...";
};

class Brass :public Instrument {
public:
	Brass(int piece) :mouthpiece(piece) {}

	void makeSound() {
		Instrument::makeSound();
		cout << "blow on mouthpiece of size " << mouthpiece << endl;

	}
private:
	int mouthpiece;
};

class Trumpet :public Brass {
public:
	Trumpet(int piece) :Brass(piece) {}
	void play() {
		cout << "Toot"<<endl;
	}

};

class Trombone : public Brass {
public:
	Trombone(int piece):Brass(piece) {}
	void play() {
		cout << "Blat" << endl;
	}
};

class String :public Instrument {
public:
	String(int pitch) :pitch(pitch) {}

	void makeSound() {
		Instrument::makeSound();
		cout << "bow a string of pitch " << pitch << endl;

	}
private:
	int pitch;

};

class Violin :public String {
public:
	Violin(int pitch) :String(pitch) {}
	void play() {
		cout << "Screech" << endl;
	}
};

class Cello :public String {
public:
	Cello(int pitch) :String(pitch) {}
	void play() {
		cout << "Squawk" << endl;
	}
};

class Percussion :public Instrument {

public:
	Percussion() {}
	void makeSound() {
		Instrument::makeSound();
		cout << "hit me" << endl;

	}
private:
};

class Drum :public Percussion {
public:
	Drum() :Percussion() {}
	void play() {
		cout << "Boom" << endl;
	}

};

class Cymbal :public Percussion {
public:
	Cymbal() :Percussion() {}
	void play() {
		cout << "Crash" << endl;
	}
};




class Musician {
public:
	Musician() : instr(nullptr) {}

	void acceptInstr(Instrument* instPtr) { instr = instPtr; }

	Instrument* giveBackInstr() {
		Instrument* result(instr);
		instr = nullptr;
		return result;
	}

	void testPlay() const {
		if (instr) instr->makeSound();
		else cerr << "have no instr\n";
	}

	void play() const {
		if (instr) instr->play();
	}

private:
	Instrument* instr;
};

class MILL {
public:
	void receiveInstr(Instrument& instr) {
		instr.makeSound();
		for (size_t i = 0; i < library.size(); ++i) {
			if (library[i] == nullptr){
				library[i] = &instr;
				return;
			}
		}
		library.push_back(&instr);
		
	}

	void dailyTestPlay() {
		for (size_t i = 0; i < library.size(); ++i) {
			if (library[i] != nullptr) {
				library[i]->makeSound();
			}
		}
	}

	Instrument* loanOut() {
		for (size_t i = 0; i < library.size(); ++i) {
			if (library[i] != nullptr) {
				Instrument* toLend= library[i];
				library[i] = nullptr;
				return toLend;
			}
		}
		return nullptr;
	
	}


private:
	vector<Instrument*> library;
};

class Orch {
public:
	void addPlayer(Musician& person) {
		musicians.push_back(&person);
	}

	void play() {
		for (size_t i = 0; i < musicians.size(); ++i) {
			musicians[i]->play();
		}
	}
private:
	vector<Musician*> musicians;


};

// PART ONE
int main() {

	 //cout << "Define some instruments ------------------------------------\n";
	 //Drum drum;
	 //Cello cello(673);
	 //Cymbal cymbal;
	 //Trombone tbone(4);
	 //Trumpet trpt(12) ;
	 //Violin violin(567) ;

	 //// use the debugger to look at the mill
	 //cout << "Define the MILL --------------------------------------------\n";
	 //MILL mill;

	 //cout << "Put the instruments into the MILL --------------------------\n";
	 //mill.receiveInstr(trpt);
	 //mill.receiveInstr(violin);
	 //mill.receiveInstr(tbone);
	 //mill.receiveInstr(drum);
	 //mill.receiveInstr(cello);
	 //mill.receiveInstr(cymbal);

	 //cout << "Daily test -------------------------------------------------\n";
	 //cout << endl;
	 //cout << "dailyTestPlay()" << endl;
	 //mill.dailyTestPlay();
	 //cout << endl;

	 //cout << "Define some Musicians---------------------------------------\n";
	 //Musician harpo;
	 //Musician groucho;

	 //cout << "TESTING: groucho.acceptInstr(mill.loanOut());---------------\n";
	 //groucho.testPlay();	
	 //cout << endl;
	 //groucho.acceptInstr(mill.loanOut());
	 //cout << endl;
	 //groucho.testPlay();
	 //cout << endl;
	 //cout << "dailyTestPlay()" << endl;
	 //mill.dailyTestPlay();

	 //cout << endl << endl;

	 //groucho.testPlay();	
	 //cout << endl;
	 //mill.receiveInstr(*groucho.giveBackInstr());
	 //harpo.acceptInstr(mill.loanOut());
	 //groucho.acceptInstr(mill.loanOut());
	 //cout << endl;
	 //groucho.testPlay();
	 //cout << endl;
	 //harpo.testPlay();
	 //cout << endl;
	 //cout << "dailyTestPlay()" << endl;
	 //mill.dailyTestPlay();

	 //cout << "TESTING: mill.receiveInstr(*groucho.giveBackInstr()); ------\n";

	 //// fifth
	 //mill.receiveInstr(*groucho.giveBackInstr());
	 //cout << "TESTING: mill.receiveInstr(*harpo.giveBackInstr()); ------\n";
	 //mill.receiveInstr(*harpo.giveBackInstr());


	 //cout << endl;
	 //cout << "dailyTestPlay()" << endl;
	 //mill.dailyTestPlay();
	 //cout << endl;

	 //cout << endl;


	Drum drum;
	Cello cello(673);
	Cymbal cymbal;
	Trombone tbone(4);
	Trumpet trpt(12);
	Violin violin(567);

	MILL mill;
	mill.receiveInstr(trpt);
	mill.receiveInstr(violin);
	mill.receiveInstr(tbone);
	mill.receiveInstr(drum);
	mill.receiveInstr(cello);
	mill.receiveInstr(cymbal);

	Musician bob;
	Musician sue;
	Musician mary;
	Musician ralph;
	Musician jody;
	Musician morgan;

	Orch orch;

	// THE SCENARIO

	//Bob joins the orchestra without an instrument.
	orch.addPlayer(bob);

	//The orchestra performs
	cout << "orch performs\n";
	orch.play();

	//Sue gets an instrument from the MIL2 and joins the orchestra.
	sue.acceptInstr(mill.loanOut());
	orch.addPlayer(sue);

	//Ralph gets an instrument from the MIL2.
	ralph.acceptInstr(mill.loanOut());

	//Mary gets an instrument from the MIL2 and joins the orchestra.
	mary.acceptInstr(mill.loanOut());
	orch.addPlayer(mary);

	//Ralph returns his instrument to the MIL2.
	mill.receiveInstr(*ralph.giveBackInstr());

	//Jody gets an instrument from the MIL2 and joins the orchestra.
	jody.acceptInstr(mill.loanOut());
	orch.addPlayer(jody);

	// morgan gets an instrument from the MIL2
	morgan.acceptInstr(mill.loanOut());

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	//Ralph joins the orchestra.
	orch.addPlayer(ralph);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	// bob gets an instrument from the MIL2
	bob.acceptInstr(mill.loanOut());

	// ralph gets an instrument from the MIL2
	ralph.acceptInstr(mill.loanOut());

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();

	//Morgan joins the orchestra.
	orch.addPlayer(morgan);

	//The orchestra performs.
	cout << "orch performs\n";
	orch.play();
}

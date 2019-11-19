#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

//decode each letter
char decode(int rotation,char& letter) {
	//check to make sure not capital or punctuation
	if (isalpha(letter) && islower(letter)) {
		//if letter at end of alphabet, wrap around
		if (!((letter-rotation)>='a' && (letter - rotation)<'z')) {
			letter += ((26 - rotation));
		}
		//if not at the end, perform the rotation
		else { letter -= rotation; }
	}
	return letter;
}

//decode the string
void decodeLine(int rotation,string& line) {
	for (size_t i = 0; i < line.length(); i++) {
		decode(rotation, line[i]);
	}
}

void displayDecoded(const vector<string> lines) {
	for (size_t i = 0; i < lines.size(); i++) {
		cout << lines[i] << endl;
	}
}


int main() {
	//open file stream
	ifstream ifs("encrypt.txt");
	if (!ifs) {
		cerr << "failed to open encrypt";
		exit(1);
	}

	string line;
	int rotation;
	vector<string> lines;

	ifs >> rotation;
	
	//correct rotation if over length of the alphabet
	while (rotation > 25) {
		rotation -= 26;
	}

	//clear new line after rotation num
	getline(ifs, line);
	
	while (getline(ifs,line)){
		decodeLine(rotation,line);
		//push front to unreverse the lines
		lines.insert(lines.begin(), line);
		}
		
	
	ifs.close();
	displayDecoded(lines);


}


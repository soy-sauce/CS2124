//Connie Zhou
//cz1529
//rec01 

#include <iostream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

void loadText(const string& name, vector<string>& lines) {
	ifstream ifs(name);
	if (!ifs) {
		cerr << "Failed to open life";
		exit(1);
	}


	string line;
	//create top and bottom borders;
	bool first = true;
	string border = "";

	while (getline(ifs, line)) {
		//if first line make border
		if (first) {
			for (size_t i = 0; i < (line.size() + 2); i++) {
				border = border + '0';
			}
			lines.push_back(border);
		}

		first = false;
		//load in the lines with right and left border
		lines.push_back('0' + line + '0');
	}
	lines.push_back(border);
	ifs.close();

}


void displayGen(const vector<string>& lines) {
	for (size_t i = 0; i < lines.size(); ++i) {
		for (size_t j = 0; j < lines[i].size(); ++j) {
			cout << lines[i][j];
		}
		cout << endl;
	}
	cout << "----------------------------------\n";
}

void playGame(vector<string>& lines,int plays) {
	vector<string> linesCopy = lines;//copy which will be changed, lines will be evaluated
	
	int numPlays = plays; //number of times to play/num of generations
	int count = 0; //count the number of cells around it
	while (numPlays > 0) {
		for (size_t i = 1; i < lines.size() - 1; ++i) {
			for (size_t j = 1; j < lines[i].size()-1; ++j) {

				//check  each adjacent cell around the cell you are checking
				if (lines[i - 1][j] == '*') {
					count = count + 1;
				}

				if (lines[i - 1][j + 1] == '*') {
					count = count + 1;
				}
				if (lines[i][j + 1] == '*') {
					count = count + 1;
				}
				if (lines[i + 1][j + 1] == '*') {
					count = count + 1;
				}
				if (lines[i + 1][j] == '*') {
					count = count + 1;
				}
				if (lines[i - 1][j - 1] == '*') {
					count = count + 1;
				}
				if (lines[i][j - 1] == '*') {
					count = count + 1;
				}
				if (lines[i + 1][j - 1] == '*') {
					count = count + 1;
				}
			
				//decide what to do with the cell: death or alive
				//only change when alive becomes dead and dead becomes alive
				if ((count > 3) && (lines[i][j] == '*')) {
					linesCopy[i][j] = '-';
				}
				else if ((count < 2) && (lines[i][j] == '*')) {
					linesCopy[i][j] = '-';
				}
				else if ((count == 3) && (lines[i][j] == '-')) {
					linesCopy[i][j] = '*';
				}
				count = 0;
			}
		}
		lines = linesCopy; //replace lines with the changed board
		displayGen(lines);
		numPlays=numPlays-1;
	}

}

int main() {
	vector<string> lines;
	loadText("life.txt",lines);
	displayGen(lines);
	playGame(lines,10);


}


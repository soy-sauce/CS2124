
#include "stdafx.h"
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

int main() {
	ifstream ifs("life.txt");
	if (!ifs) {
		cerr << "failed to open life";
		exit(1);
	}

	string line;
	vector<string> lines;
	getline(ifs, line);
	bool first = true;
	string border = "";
	while (getline(ifs, line)) {
		if (first) {
			
			for (size_t i = 0; i < (line.size() + 2); i++) {
				border = border + '0';
			}
			lines.push_back(border);
		}
		first = false;

		lines.push_back('0'+line+'0');
	}

	lines.push_back(a);

	ifs.close();

	for (size_t i = 0; i < lines.size(); ++i) {
		for (size_t j = 0; j < lines[i].size(); ++j) {
			cout << lines[i][j] << ' ';
		}
		cout << endl;
	}


	vector<string> linescopy;


	//each generation


	int x = 10;
	int count = 0;
	while (x > 0) {
		linescopy = lines;
		for (size_t i = 1; i<(lines.size()-1); i++) {
			for (int j = 1; j < (lines[i].size()-1); j++) {
				//cout << "i: " << i << " j: " << j << endl;
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
					
				if ((count > 3) && (lines[i][j] == '*')) {
					linescopy[i][j] = '-';
				}
				else if ((count < 2) && (lines[i][j] == '*')) {
					linescopy[i][j] = '-';
				}
				else if ((count==3) && (lines[i][j] == '-')) {
					linescopy[i][j] = '*';
				}
				count = 0;


				
			}


		}
		
		lines = linescopy;
		for (size_t i = 0; i<lines.size(); i++) {
			for (size_t j = 0; j < lines[i].size(); j++) {
				cout << lines[i][j] << ' ';
			}
			cout << endl;
		}
		x = x - 1;
	}
	}

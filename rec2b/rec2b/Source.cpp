#include <string>
#include <vector>
#include <iostream>
#include <fstream>

using namespace std;

struct Hydrocarbon {
	vector<string> names;
	int num_carbon;
	int num_hydro;

};


void openFile(ifstream& ifs);
void fillVector(vector<Hydrocarbon>& hydrocarbons, ifstream& ifs);
void displayCollection(const vector<Hydrocarbon>& collection);
void sorting(vector<Hydrocarbon>& hydrocarbons);

bool searchSameMolecule(vector<Hydrocarbon>& hydrocarbons, int carbon, int hydro, const string& name);

//open ifs
void openFile(ifstream& ifs) {
	string file;
	cout << "Enter your file name: " << endl;
	cin >> file;
	ifs.open(file);
	
	while (!ifs) {
		cerr << "Failed to open file" << endl;;
		ifs.clear();
		cout << "Enter your file name: " << endl;
		cin >> file;
		ifs.open(file);
	
	}

}

//fill vector with data from file
void fillVector(vector<Hydrocarbon>& hydrocarbons, ifstream& ifs) {
	string name;
	int num_carbon;
	int num_hydro;
	char carbon;



	while (ifs >> name >> carbon >> num_carbon >> carbon >> num_hydro) {
		//check if molecule with that composition already exists
		//if not, add the molecule to collection
		if (!(searchSameMolecule(hydrocarbons,num_carbon,num_hydro,name))) {
			Hydrocarbon newHydro;
			newHydro.names.push_back(name);
			newHydro.num_carbon = num_carbon;
			newHydro.num_hydro = num_hydro;
			hydrocarbons.push_back(newHydro);

		}
	
	}
	ifs.close();

}

//display
void displayCollection(const vector<Hydrocarbon>& hydrocarbons) {
	for (size_t i = 0; i < hydrocarbons.size(); ++i) {
		cout << "C" << hydrocarbons[i].num_carbon << "H" << hydrocarbons[i].num_hydro << " ";
		for (size_t j = 0; j < hydrocarbons[i].names.size(); ++j) {
			cout << hydrocarbons[i].names[j] << " ";
		}
		cout << endl;
	}
	

}


//selection sort
void sorting(vector<Hydrocarbon>& hydrocarbons) {
	int min;

	for (size_t i = 0; i < hydrocarbons.size() - 1; i++) {
		min = i;
		for (size_t j = i + 1; j < hydrocarbons.size(); j++) {
			if (hydrocarbons[j].num_carbon < hydrocarbons[min].num_carbon) {
				min = j;
			}
			else if (hydrocarbons[j].num_carbon == hydrocarbons[min].num_carbon) {
				if (hydrocarbons[j].num_hydro < hydrocarbons[min].num_hydro) {
					min = j;
				}
			}


		}
		Hydrocarbon temp = hydrocarbons[i];
		hydrocarbons[i] = hydrocarbons[min];
		hydrocarbons[min] = temp;


	}

}


//searches to see if a molecule with indicated num of carbon/hydrogen exists

//return index instead or a pointer if i want to change or improve code
bool searchSameMolecule(vector<Hydrocarbon>& hydrocarbons,int carbon, int hydro,const string& name) {
	for (size_t i = 0; i < hydrocarbons.size(); ++i) {
		if ((hydrocarbons[i].num_carbon==carbon)&&(hydrocarbons[i].num_hydro==hydro)) {
			hydrocarbons[i].names.push_back(name);
			return true;
		}
	}
	return false;
}

int main() {
	ifstream ifs;
	vector<Hydrocarbon> hydrocarbons;
	openFile(ifs);
	fillVector(hydrocarbons, ifs);
	//displayCollection(hydrocarbons);
	//cout << "------------------------------" << endl;
	sorting(hydrocarbons);
	displayCollection(hydrocarbons);
}
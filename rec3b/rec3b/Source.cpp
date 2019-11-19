//cz1529
//rec 3

#include <iostream>
#include <string>
#include <vector>
#include <fstream>
#include <ctime>

using namespace std;


struct Tile{
	//two types of tiles, bomb or normal tile with numbers
	//keep track of visibility
	bool isVisible;
	bool isBomb;
	int numBombs;

	//coordinates
	int xcor;
	int ycor;


};

class Minesweeper {
private:
	vector<vector<Tile>> gameboard;
	int ncol; //number of columns
	int nrow; //number of rows
	const int BOMBPROBABILITY=10; //affects number of bombs

public:
	Minesweeper(int numrow = 10, int numcol = 10) :nrow(numrow), ncol(numcol) {
		//creation of a border
		Tile borderTile;
		borderTile.isVisible = true;
		borderTile.numBombs = 0;
		borderTile.isBomb = false;
		borderTile.xcor = 0;
		borderTile.ycor = 0;

		bool first = true;
		vector<Tile> border;
		if (first) {
			for (int i = 0; i < ncol + 2; ++i) {
				border.push_back(borderTile);
			}
			gameboard.push_back(border);
		}
		first = false;

		srand(time(NULL));
		//create the gamebord
		for (int i = 0; i < ncol; ++i) {
			vector<Tile> newRow; //pushback this vector to represent each row
			newRow.push_back(borderTile);
			for (int j = 0; j < nrow; ++j) {
				//create a tile based on probability, is it a bomb or not?
				if ((rand() % 100) < BOMBPROBABILITY) {
					Tile newTile;
					newTile.isBomb = true;
					newTile.numBombs = 0;
					newTile.isVisible = false;
					newTile.xcor = i;
					newTile.ycor = j;
					newRow.push_back(newTile);
				}
				else {
					Tile newTile;
					newTile.isBomb = false;
					newTile.numBombs = 0; //keep at zero for now, we'll come back later
					newTile.isVisible = false;
					newTile.xcor = i;
					newTile.ycor = j;
					newRow.push_back(newTile);

				}

			}
			newRow.push_back(borderTile);
			gameboard.push_back(newRow);
		}
		gameboard.push_back(border);
		modifyNeighbors(); //go back to change tiles adjacent to bombs

	}


	//checks if game is over
	bool done() {
		//check is any non bomb tile still hasn't been clicked
		for (size_t i = 0; i < gameboard.size(); ++i) {
			for (size_t j = 0; j < gameboard[i].size(); ++j) {
				if ((!gameboard[i][j].isVisible) && !(gameboard[i][j].isBomb)) {
					return false;
				}
			}
		}
		return true;
	}

	//display the board, if showbomb is true, show everything
	void display(bool showBomb) {
		for (size_t i = 1; i < ncol+1; ++i) {
			for (size_t j = 1; j < nrow+1; ++j) {
				//for each item depending on showbomb, display a symbol
				if (showBomb) {
					if(gameboard[i][j].isBomb){
						cout << 'O';
					}
					else {
						cout << gameboard[i][j].numBombs;
					}
				}
				else {
					if (gameboard[i][j].isVisible) {
						cout << gameboard[i][j].numBombs;
					}
					else if(!gameboard[i][j].isVisible) {
						cout << '?';
					}
				
				}
			}
			cout << endl;
		}
	}

	bool validRow(int row) {
		return (row > 0 && row <= nrow);
	}

	bool validCol(int col) {
		return (col > 0 && col <= ncol);
	}
	bool isVisible(int row, int col) {
		return gameboard[row][col].isVisible;
	}
	void modifyNeighbors() {
		int count = 0;
		for (size_t i = 1; i < gameboard.size() - 1; i++) {
			for (size_t j = 1; j < gameboard[i].size() - 1; j++) {
				if (gameboard[i - 1][j].isBomb == true) {
					count = count + 1;
				}

				if (gameboard[i - 1][j + 1].isBomb == true) {
					count = count + 1;
				}
				if (gameboard[i][j + 1].isBomb == true) {
					count = count + 1;
				}
				if (gameboard[i + 1][j + 1].isBomb == true) {
					count = count + 1;
				}
				if (gameboard[i + 1][j].isBomb == true) {
					count = count + 1;
				}
				if (gameboard[i - 1][j - 1].isBomb == true) {
					count = count + 1;
				}
				if (gameboard[i][j - 1].isBomb == true) {
					count = count + 1;
				}
				if (gameboard[i + 1][j - 1].isBomb == true) {
					count = count + 1;
				}
				gameboard[i][j].numBombs = count;
				count = 0;
			}
		}
	}

	bool play(int row, int col) {
		gameboard[row][col].isVisible = true; //make clicked tile visible
		if (gameboard[row][col].isBomb) {
			return false; //ends because it was a bomb
		}
		else if (gameboard[row][col].numBombs==0) { //do the chaining for zero tiles
			//run play on every adjacent tile
			if (gameboard[row - 1][col].isVisible == false) {
				play(row - 1, col);
			}

			if (gameboard[row - 1][col + 1].isVisible == false) {
				play(row - 1, col + 1);
			}
			if (gameboard[row][col + 1].isVisible == false) {
				play(row, col + 1);
			}
			if (gameboard[row + 1][col + 1].isVisible == false) {
				play(row + 1, col + 1);
			}
			if (gameboard[row + 1][col].isVisible == false) {
				play(row + 1, col);
			}
			if (gameboard[row - 1][col - 1].isVisible == false) {
				play(row - 1, col - 1);
			}
			if (gameboard[row][col - 1].isVisible == false) {
				play(row, col - 1);
			}
			if (gameboard[row + 1][col - 1].isVisible == false) {
				play(row + 1, col - 1);
			}
		}
		//is not bomb or a tile that needs chaining, do nothing
	
		
	}

};






int main() {
	Minesweeper sweeper;
	sweeper.display(true);
	// Continue until only invisible cells are bombs
	while (!sweeper.done()) {
		sweeper.display(false); // display board without bombs

		int row_sel = -1, col_sel = -1;
		while (row_sel == -1) {
			// Get a valid move
			int r, c;
			cout << "row? ";
			cin >> r;
			if (!sweeper.validRow(r)) {
				cout << "Row out of bounds\n";
				continue;
			}
			cout << "col? ";
			cin >> c;
			if (!sweeper.validCol(c)) {
				cout << "Column out of bounds\n";
				continue;
			}
			if (sweeper.isVisible(r, c)) {
				cout << "Square already visible\n";
				continue;
			}
			row_sel = r;
			col_sel = c;
		}
		// Set selected square to be visible. May effect other cells.
		if (!sweeper.play(row_sel, col_sel)) {
			cout << "Sorry, you died..\n";
			sweeper.display(true); // Final board with bombs shown
			exit(0);
		}
	}
	// Ah! All invisible cells are bombs, so you won!
	cout << "You won!!!!\n";
	sweeper.display(true); // Final board with bombs shown
}
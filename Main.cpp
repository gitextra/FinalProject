
// file main.cpp

#include "MorseTree.h"

int main() {
	string file;
	ifstream fin;
	// Open file and handle error (if occur)
	while (true) {
		cout << "Enter the file name: ";
		cin >> file;
		fin.open(file);
		if (!fin) {
			cerr << "Error opening input file!" << endl;
			continue;
		}
		else { break; }
	}
	getline(cin, file); // Get rid of '\n'
	Tree T;
	T.buildTree(fin);
	T.encode();
	T.decode();
	system("pause");

}

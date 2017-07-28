
// file MorseTree.h

#include <string>
#include <iostream>
#include <fstream>
#include <vector>
#include <map>
#include <iomanip>
using namespace std;

#ifndef MORSETREE
#define MORESETREE

class Tree
{
public:
	// Node contain data and ptr to its left and right nodes
	struct Node {
	public:
		Node(char d) {
			data = d;
			left = right = NULL;
		}
		char data;
		Node* left;
		Node* right;
	};
	typedef Node* Node_ptr;

	void buildTree(ifstream& s); // Build tree function
	void insert(char word, string code); // Insert char to the specified node based on the morse code
	void display(Node_ptr first_root, int indent); // Display node recursively
	void encode(); // Encrypt the words
	void decode(); // Decrypt the morse code

private:
	Node_ptr first_root = new Node('<'); // Initial root 
	map<char, string> word_code_data; // word->code map to encrypt
	map<string, char> code_word_data; // code->word map to decrypt


};






#endif // !MORSETREE


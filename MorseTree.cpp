
// file MorseTree.cpp

#include "MorseTree.h"



// Build tree based on data in the input file
void Tree::buildTree(ifstream & s)
{
	char w;
	string c;
	while (true) {
		s >> w >> c; // Read word as char and its morse code as string
		word_code_data[w] = c; // Add data to word->code map to encrypt
		code_word_data[c] = w; // Add data to code->word map to decrypt
		insert(w, c); // Insert data to specified node
		if (s.eof()) { break; };
	}
	// Print header
	cout << setw(20) << " " << "FULL TREE" << endl;
	cout << setw(10) << " " << "(read vertically from left -> right)" << endl;
	display(first_root, 0); // Print tree
}

// Insert char to specified node based on the morse code
void Tree::insert(char word, string code)
{
	int i = 0;
	Node_ptr temp = first_root; // Start with a ptr point to initial root
	while (i < code.length()) { // Read morse code char by char and move ptr based on the char until reach the desired node
		switch (code[i]) {
		case '.': // Go left if the char is '.'
			if (temp->left == NULL) { temp->left = new Tree::Node('<'); } // If there is no node on the left, create one
			temp = temp->left; // Move ptr to the left
			break;
		case '_': // Go right if the char is '_'
			if (temp->right == NULL) { temp->right = new Tree::Node('<'); } // If there is no node on the right, create one
			temp = temp->right; // Move ptr to the right
			break;
		default:
			cerr << "Unable to identify character" << endl; // If tree is empty, notify error and exit
			exit(1);
		}
		i++;
	}
	temp->data = word; // After moved to the desired node based on the morse code, set the data to that node.
}

// Display the tree recursively
void Tree::display(Node_ptr first_root, int indent)
{
	if (first_root != 0)
	{
		display( first_root->right, indent + 8);
		cout << setw(indent) << " " << first_root->data << endl;
		display( first_root->left, indent + 8);
	}

}

// Encrypt input char
void Tree::encode()
{
	string word, result;
	bool bad_input = false;
	cout << "Please enter word to encrypt: ";
	while (!(getline(cin, word)) || word.empty()) { cout << "Please enter valid word: "; } // Prevent empty input
	for (int i = 0; i < word.length(); i++){  // Encrypt word by word
		word[i] = tolower(word[i]);
		if (word_code_data.find(word[i]) == word_code_data.end()) { // If the word cannot be encrypted, redo the process (below)
			cout << "This word cannot be encrypted. Please try again" << endl;
			bad_input = true;
			break;
		}
		else {
			result += (word_code_data.find(word[i])->second + " "); // Add encrypted char into the result
		}
	}
	if (bad_input == true) { encode(); } // Redo the process
	else { cout << "Encrypted word: " << result << endl; } // Print the result 

}

// Decrypt input morse code
void Tree::decode()
{
	string code, result;
	bool bad_input = false;
	char c;
	cout << "Please enter code to decrypt: ";
	/* Read input char by char and add it to var code .
	 Whhen reach ' ' (full piece of code is read), start decrypt that code. Then continue until the end of the input */
	while (cin.get(c)) {
		if (c == ' ' || c == '\n') { 
			if (c == '\n' && code == "") {  // Prevent empty input
				cout << "Please enter valid code: ";
				continue;
			}
			if (code_word_data.find(code) == code_word_data.end()){ // If the code cannot be decrypted, redo the process (below)
				cout << "This code cannot be decrypted. Please try again" << endl;
				bad_input = true;
				break;
			}
			else {
				result += code_word_data.find(code)->second; // Add the decrypted code into the result
				code = "";
				if (c == '\n') { break; }
				cin.get(c);
			}
		}
		code.push_back(c);
	}
	if (bad_input == true) { decode(); } // Redo the process
	else { cout << "Decrypted code: " << result << endl; } // Print the result 
	
}



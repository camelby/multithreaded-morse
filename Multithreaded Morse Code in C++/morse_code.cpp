#include "morse_code.h"
Node* Btree::loadTree(Node*& btree, std::string fileName) {
	Node* root = new Node;
	root->character = ' ';
	root->left = nullptr;
	root->right = nullptr;
	std::ifstream fin;
	fin.open(fileName);
	//file check
	if (!fin.is_open() && !fin.eof()) {
		std::cout << "Error opening file!" << std::endl;
		system("QUIT");
	}
	std::string dataCode = " ";
	char dataSymbol = ' ';
	//takes the character and its morse code and inserts it into the binary tree until end of file
	while (!fin.eof()) {
		fin >> dataSymbol;
		fin >> dataCode;
		insert(root, dataCode, dataSymbol);
	}
	return root;
	fin.close();
}

void Btree::insert(Node*& root, std::string morseCode, char character) {
	Node* temp = new Node;
	temp->character = character;
	temp->left = nullptr;
	temp->right = nullptr;
	Node* currNode = root;
	while (currNode != nullptr) {
		//for how many characters are in the morse code 
		for (int i = 0; i < morseCode.size(); i++) {
			if (morseCode[i] == '.') {
				if (currNode->left == nullptr) {
					currNode->left = temp;
					return;
				}
				else {
					currNode = currNode->left; //increment till an empty node to the left is found
				}
			}
			else {
				if (currNode->right == nullptr) {
					currNode->right = temp;
					return;
				}
				else {
					currNode = currNode->right; //increment till an empty node to the right is found
				}
			}
		}
	}
}

void Btree::displayMenu(Node* root) {
	int command = 0;
	while (command != 3) {
		std::cout << "\t\t\t Welcome to the Morse Code Translator!\n\n";
		std::cout << "\t\t Please choose one of the options for translating morse code.\n";
		std::cout << "\t\t 1. Enter morse code and translate to a word or phrase\n";
		std::cout << "\t\t 2. Enter a word or phrase and translate to morse code\n";
		std::cout << "\t\t 3. Quit the program\n";
		std::cin >> command;
		system("CLS");
		switch (command) {
		case 1: {
			Node* currNode = root;
			std::cout << "Please enter the morse code you want to translate (ex. -.-- .---)\n";
			std::cout << "Type | for spaces and * to smoothly end the translation\n";
			std::string morseCode = " ";
			while (std::cin >> morseCode) {
				if (morseCode == "*") {
					std::cout << std::endl;
					system("PAUSE");
					system("CLS");
					break;
				}
				else {
					translateFromMorse(root, morseCode);
				}
			}
			break;
		}
		case 2: {
			std::cout << "Please enter the word or phrase you to want translate to morse code\n";
			std::cout << "Type * to end translation\n";
			std::string convertText;
			while (std::cin >> convertText) {
				//converts any lowercase characters to uppercase for binary tree
				for (int i = 0; i < convertText.size(); i++) {
					convertText[i] = toupper(convertText[i]);
				}
				if (convertText == "*") {
					std::cout << std::endl;
					system("PAUSE");
					system("CLS");
					break;
				}
				else {
					//searches for every character and outputs the morse code
					for (int i = 0; i < convertText.size(); i++) {
						Node* currNode = root;
						std::stack<char> morseStack;
						translateToMorse(currNode, convertText, morseStack, i);
					}

				}
			}
			break;
		}
		case 3: {
			system("EXIT");
			break;
		}
		default: {
			system("CLS");
			break;
		}
		}
	}
}
void Btree::translateFromMorse(Node* root, std::string morseCode) {
	Node* currNode = root;
	if (morseCode == "|") {
		std::cout << " ";
		return;
	}
	//navigate to the node with the correct character 
	for(int i = 0; i < morseCode.size(); i++) {
		if (morseCode[i] == '.') {
			currNode = currNode->left;
		}
		else if (morseCode[i] == '-') {
			currNode = currNode->right;
		}
		else {
			std::cout << "Error reading morse code. Please retry morse code" << std::endl;
			break;
		}
	}
	std::cout << currNode->character;
}
void Btree::translateToMorse(Node* currNode, std::string convertText, std::stack<char> morseStack, int i) {
	if (currNode == nullptr) {
		morseStack.pop();
		return;
	}
	else {
		if (currNode->character == convertText[i]) {
			int j = 0;
			std::vector<char> code;
			//store the characters from the stack into a vector to be printed out in reverse order
			while (!morseStack.empty()) {
				char temp = ' ';
				temp = morseStack.top();
				code.push_back(temp);
				morseStack.pop();
			}
			//prints the stack in reverse order using a vector 
			for (j = code.size() - 1; j >= 0; j--) {
				std::cout << code.at(j);
			}
			std::cout << " ";
			return;
		}
		else {
			//going left down the tree and pushing .
			morseStack.push('.');
			translateToMorse(currNode->left, convertText, morseStack, i);
			morseStack.pop();
			//going right down the tree and pushing -
			morseStack.push('-');
			translateToMorse(currNode->right, convertText, morseStack, i);
		}
	}
}
std::string Btree::get_file() {
	return fileName;
}
void Btree::runMultiThread(Node*& root, std::string fileName) {
	std::thread t1(&Btree::loadTree,this,std::ref(root), fileName);
	std::thread t2(&Btree::displayMenu,this, std::ref(root));
	t1.join();
	t2.join();
}



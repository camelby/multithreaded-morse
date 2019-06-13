#ifndef MORSE_CODE_H
#define MORSE_CODE_H
#include <iostream>
#include <fstream>
#include <stack>
#include <string>
#include <vector>
#include <thread>
class Node {
	friend class Btree;
private:
	char character;
	Node* left;
	Node* right;
};

class Btree {
private:
	std::string fileName = "morse.txt";
public:
	Node* loadTree(Node*&, std::string);
	void insert(Node*&, std::string, char);
	void displayMenu(Node*);
	void translateFromMorse(Node*, std::string);
	void translateToMorse(Node*, std::string, std::stack<char>, int);
};

#endif

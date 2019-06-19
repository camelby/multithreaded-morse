#include "morse_code.h"
int main() {
	Btree btree;
	Node* node = new Node();
	node = btree.loadTree(std::ref(node),btree.get_file());
	btree.runMultiThread(std::ref(node), btree.get_file());
	return 0;
}

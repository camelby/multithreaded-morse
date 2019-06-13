#include "morse_code.h"
int main() {
//FIX
	Btree btree;
	std::thread t1(Btree::loadTree(root, fileName));
	std::thread t2(btree.displayMenu(root));
	t1.join();
	t2.join();
	return 0;
}

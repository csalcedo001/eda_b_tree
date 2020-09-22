#include <iostream>

#include "b_tree.hpp"

using namespace std;

int main()
{
	eda::BTree<3, int> btree;
	// using btree_int = eda::btree<int, 3>; 

	// btree_int bt;

	// for (size_t i = 0; i <= 1000; i++) {
	// 	bt.insert(i);
	// }

	// bt.print();

	// eda::btree_int::iterator begin = bt.find(100);
	// eda::btree_int::iterator end = bt.find(200);

	// for (auto iter = begin; iter != end; iter++ ) {
	// 	std::cout << *iter << std::endl;
	// }

	return 0;
}

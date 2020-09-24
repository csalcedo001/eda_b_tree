#include <iostream>

#include "b_tree.hpp"
#include "drawable.hpp"

using namespace std;

int main()
{
	eda::BTree<4, int> btree;

	btree.insert(1);
	btree.insert(4);
	btree.insert(5);
	btree.insert(1);
	btree.insert(-1);
	btree.insert(8);
	btree.insert(9);
	btree.insert(2);
	btree.insert(7);

	btree.print();
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

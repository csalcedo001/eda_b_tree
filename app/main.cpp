#include <iostream>

#include "b_tree.hpp"

int main()
{
    eda::b_tree::BTree<3, int> btree;
    
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

    return 0;
}

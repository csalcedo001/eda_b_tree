#ifndef B_TREE_B_TREE_HPP_
#define B_TREE_B_TREE_HPP_

namespace eda {

template <int m, typename T>
class BTree {
public:
	class Node;

private:
	Node *root_;

	// struct iterator {
	// 	Node<m, t> *node;
	// 	size_t index;

	// 	iterator(Node<m, t> *, size_t);
	// 	iterator &operator++(int);
	// 	bool operator!=();
	// 	bool operator==();
	// 	bool operator*();
	// };

public:
	BTree();

	void insert(T);
	bool exists(T);
	void remove(T);

private:
	bool insert_(Node *, T);
	Node *divide_(Node *);
	void insert_within_(Node *, int, T, Node *);
	int child_key_(Node *, T);
};

} // namespace eda

#include "impl/b_tree.ipp"

#endif // B_TREE_B_TREE_HPP_

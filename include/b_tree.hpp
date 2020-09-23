#ifndef B_TREE_B_TREE_HPP_
#define B_TREE_B_TREE_HPP_

#include <array>

namespace eda {

template <int m, typename T>
class BTree {
public:
	struct Node;

	enum State {
		OVERFLOW,
		UNDERFLOW,
		OK
	};

private:
	Node *root_;

public:
	BTree();
	~BTree();

	void insert(T);
	bool exists(T);
	void remove(T);
	int size();

private:
	State insert_(Node *, T);
	Node *divide_(Node *&);
	void insert_within_(Node *, int, T, Node *);
	int child_key_(Node *, T);
	void kill_(Node *);
};

} // namespace eda

#include "impl/b_tree.ipp"

#endif // B_TREE_B_TREE_HPP_

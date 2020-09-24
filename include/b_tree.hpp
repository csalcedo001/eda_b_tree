#ifndef B_TREE_B_TREE_HPP_
#define B_TREE_B_TREE_HPP_

#include <array>

#include "drawable/tree.hpp"

namespace eda {

template <int m, typename T>
class BTree : public drawable::Tree<T> {
public:
	class Node;

	enum State {
		OVERFLOW,
		UNDERFLOW,
		OK
	};

private:
	Node *head_;

public:
	BTree();
	~BTree();

	void insert(T);
	bool exists(T);
	void remove(T);
	int size();
	void print();

private:
	State insert_(Node *, T);
	Node *divide_(Node *&);
	void insert_within_(Node *, int, T, Node *);
	int child_key_(Node *, T);
	void print_(Node *, int level);
	void kill_(Node *);

	Node *root_();
};

} // namespace eda

#include "impl/b_tree.ipp"

#endif // B_TREE_B_TREE_HPP_

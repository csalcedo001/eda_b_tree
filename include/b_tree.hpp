#ifndef B_TREE_B_TREE_HPP_
#define B_TREE_B_TREE_HPP_

#include "node.hpp"

namespace eda {

namespace b_tree {

template <int m, typename T>
class BTree {
public:
	enum State {
		NODE_OVERFLOW,
		NODE_UNDERFLOW,
		NODE_OK
	};

private:
	Node<m, T> *head_;

public:
	BTree();
	~BTree();

	void insert(T);
	bool exists(T);
	void remove(T);
	int size();
	void print();

private:
	State insert_(Node<m, T> *, T);
	Node<m, T> *divide_(Node<m, T> *&);
	void insert_within_(Node<m, T> *, int, T, Node<m, T> *);
	int child_key_(Node<m, T> *, T);
	void print_(Node<m, T> *, int level);
	void kill_(Node<m, T> *);
};

} // namespace b_tree

} // namespace eda

#include "impl/b_tree.ipp"

#endif // B_TREE_B_TREE_HPP_

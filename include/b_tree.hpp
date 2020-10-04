#ifndef B_TREE_B_TREE_HPP_
#define B_TREE_B_TREE_HPP_

#include "node.hpp"

namespace eda {

namespace b_tree {

template <typename T, int m>
class BTree {
public:
	enum State {
		NODE_OVERFLOW,
		NODE_UNDERFLOW,
		NODE_OK
	};

private:
	Node<T, m> *head_;

public:
	BTree();
	~BTree();

	void insert(T);
	bool exists(T);
	void remove(T);
	int size();
	void print();

private:
	State insert(Node<T, m> *, T);
	Node<T, m> *divide(Node<T, m> *&);
	void insert_within(Node<T, m> *, int, T, Node<T, m> *);
	int child_key(Node<T, m> *, T);
	void print(Node<T, m> *, int level);
	void kill(Node<T, m> *);
};

} // namespace b_tree

} // namespace eda

#include "impl/b_tree.ipp"

#endif // B_TREE_B_TREE_HPP_

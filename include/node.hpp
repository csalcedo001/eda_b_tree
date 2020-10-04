#ifndef B_TREE_NODE_HPP_
#define B_TREE_NODE_HPP_

#include "b_tree.hpp"
#include "drawable/tree.hpp"

namespace eda {

template <int m, typename T>
class BTree<m, T>::Node : public drawable::Tree<T>::Node {
public:
	std::array<T, m> values_;
	std::array<Node *, m + 1> children_;
	int capacity_;

public:
	Node(void);
	
	void search(T key);

	int children();
	int values();

	T value(int);
	Node *child(int);
	bool is_leave();

protected:
	int leaves_();
	int leave_level_values_();
};

} // namespace eda

#include "impl/node.ipp"

#endif // B_TREE_NODE_HPP_

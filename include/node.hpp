#ifndef B_TREE_NODE_HPP_
#define B_TREE_NODE_HPP_

#include <array>

namespace eda {

namespace b_tree {

template <int m, typename T>
class Node {
public:
	std::array<T, m> values_;
	std::array<Node *, m + 1> children_;
	int capacity_;

public:
	Node(void);

	int children();
	int values();

	T value(int);
	Node *child(int);
	bool is_leave();

protected:
	int leaves_();
	int leave_level_values_();
};

} // namespace b_tree

} // namespace eda

#include "impl/node.ipp"

#endif // B_TREE_NODE_HPP_

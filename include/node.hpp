#ifndef B_TREE_NODE_HPP_
#define B_TREE_NODE_HPP_

#include "b_tree.hpp"

namespace eda {

template <int m, typename T>
struct BTree<m, T>::Node {
	std::array<T, m - 1> values;
	std::array<Node *, m> children;
	int capacity;

	Node(void);
	
	void search(T key);
};

} // namespace eda

#include "impl/node.ipp"

#endif // B_TREE_NODE_HPP_

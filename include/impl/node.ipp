#ifndef B_TREE_NODE_IPP_
#define B_TREE_NODE_IPP_

#include "node.hpp"

#include "b_tree.hpp"

namespace eda {

namespace b_tree {

template <int m, typename T>
Node<m, T>::Node() {
	for (int i = 0; i < m; i++) {
		this->children_[i] = nullptr;
	}
}

} // namespace b_tree

} // namespace eda

#endif // B_TREE_NODE_IPP_

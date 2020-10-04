#ifndef B_TREE_B_STAR_TREE_NODE_IPP_
#define B_TREE_B_STAR_TREE_NODE_IPP_

#include <array>

#include "b_star_tree/b_star_tree.hpp"
#include "b_star_tree/node.hpp"

#include "drawable/tree.hpp"

namespace eda {

template <int m, typename T>
BStarTree<m, T>::Node::Node() : utec::memory::bstar<T, m>::Node() { }

template <int m, typename T>
BStarTree<m, T>::Node::Node(typename utec::memory::bstar<T, m>::Node node) :
    keys(node.keys),
    children_(node.children_),
    isLeaf(node.isLeaf)
{
    
}

template <int m, typename T>
int BStarTree<m, T>::Node::values() {
	return this->keys.size();
}

template <int m, typename T>
int BStarTree<m, T>::Node::children() {
	return this->is_leave() ? 0 : this->children.size();
}

template <int m, typename T>
T BStarTree<m, T>::Node::value(int index) {
	return this->keys[index];
}

template <int m, typename T>
typename BStarTree<m, T>::Node *BStarTree<m, T>::Node::child(int index) {
	return this->children[index];
}

template <int m, typename T>
bool BStarTree<m, T>::Node::is_leave() {
	return this->isLeaf;
}

template <int m, typename T>
int BStarTree<m, T>::Node::leaves_() {
	if (this->is_leave()) return 1;

	int total = 0;

	for (int i = 0; i < this->children(); i++) {
		if (this->children(i) != nullptr) {
			total += this->children(i)->leaves_();
		}
	}

	return total;
}

template <int m, typename T>
int BStarTree<m, T>::Node::leave_level_values_() {
	if (this->is_leave()) return this->capacity_ - 1;

	int total = 0;

	for (int i = 0; i < this->children(); i++) {
		if (this->children(i) != nullptr) {
			total += this->children(i)->leave_level_values_();
		}
	}

	return total;
}

} // namespace eda

#endif // B_TREE_B_STAR_TREE_NODE_IPP_

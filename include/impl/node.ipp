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

template <int m, typename T>
int Node<m, T>::values() {
	return this->capacity_ - 1;
}

template <int m, typename T>
int Node<m, T>::children() {
	return this->is_leave() ? 0 : this->capacity_;
}

template <int m, typename T>
T Node<m, T>::value(int index) {
	return this->values_[index];
}

template <int m, typename T>
Node<m, T> *Node<m, T>::child(int index) {
	return this->children_[index];
}

template <int m, typename T>
bool Node<m, T>::is_leave() {
	return this->capacity_ == 0 || this->children_[0] == nullptr;
}

template <int m, typename T>
int Node<m, T>::leaves_() {
	if (this->is_leave()) return 1;

	int total = 0;

	for (int i = 0; i < this->capacity_; i++) {
		if (this->children_[i] != nullptr) {
			total += this->children_[i]->leaves_();
		}
	}

	return total;
}

template <int m, typename T>
int Node<m, T>::leave_level_values_() {
	if (this->is_leave()) return this->capacity_ - 1;

	int total = 0;

	for (int i = 0; i < this->capacity_; i++) {
		if (this->children_[i] != nullptr) {
			total += this->children_[i]->leave_level_values_();
		}
	}

	return total;
}

} // namespace b_tree

} // namespace eda

#endif // B_TREE_NODE_IPP_

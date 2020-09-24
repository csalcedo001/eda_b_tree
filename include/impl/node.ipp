#ifndef B_TREE_NODE_IPP_
#define B_TREE_NODE_IPP_

#include "node.hpp"

#include "b_tree.hpp"

namespace eda {

template <int m, typename T>
BTree<m, T>::Node::Node() {
	for (int i = 0; i < m; i++) {
		this->children_[i] = nullptr;
	}
}

template <int m, typename T>
void BTree<m, T>::Node::search(T key) {
	
}

template <int m, typename T>
int BTree<m, T>::Node::values() {
	return this->capacity_ - 1;
}

template <int m, typename T>
int BTree<m, T>::Node::children() {
	return this->is_leave() ? 0 : this->capacity_;
}

template <int m, typename T>
T BTree<m, T>::Node::value(int index) {
	return this->values_[index];
}

template <int m, typename T>
typename BTree<m, T>::Node *BTree<m, T>::Node::child(int index) {
	return this->children_[index];
}

template <int m, typename T>
bool BTree<m, T>::Node::is_leave() {
	return this->capacity_ == 0 || this->children_[0] == nullptr;
}

template <int m, typename T>
int BTree<m, T>::Node::leaves_() {
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
int BTree<m, T>::Node::leave_level_values_() {
	if (this->is_leave()) return this->capacity_ - 1;

	int total = 0;

	for (int i = 0; i < this->capacity_; i++) {
		if (this->children_[i] != nullptr) {
			total += this->children_[i]->leave_level_values_();
		}
	}

	return total;
}

} // namespace eda

#endif // B_TREE_NODE_IPP_

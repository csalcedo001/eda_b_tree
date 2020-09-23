#ifndef B_TREE_B_TREE_IPP_
#define B_TREE_B_TREE_IPP_

#include "b_tree.hpp"

#include "node.hpp"

namespace eda {

template <int m, typename T>
BTree<m, T>::BTree() : root_(nullptr) {}

template <int m, typename T>
void BTree<m, T>::insert(T value) {
	if (this->root_ == nullptr) {
		this->root_ = new Node;

		this->root_.values[0] = value;

		this->root_.capacity = 2;
	}
	else if (this->insert_(this->root_, value) == OVERFLOW) {
		Node *right_child = this->root_;
		Node *left_child = this->divide_(right_child);

		this->root_ = new Node;

		this->root_.values[0] = right_child->values[right_child->capacity];
		this->root_.children[0] = left_child;
		this->root_.children[1] = right_child;
		
		this->capacity = 1;
	}
}

template <int m, typename T>
typename BTree<m, T>::State BTree<m, T>::insert_(Node *node, T value) {
	int child_index = this->child_key_(node, value);
	int value_index = std::min(child_index, m - 1);

	Node *child = node->children[child_index];

	if (child == nullptr) {
		this->insert_within_(node, child_index, value, nullptr);
	}
	else if (this->insert_(child, value) == OVERFLOW) {
		Node *new_child = this->divide_(child);
		this->insert_within_(node, child_index, child->values[child->capacity], new_child);
	}

	return this->capacity == m ? OVERFLOW : OK;
}

template <int m, typename T>
typename BTree<m, T>::Node *BTree<m, T>::divide_(Node *&right_node) {
	int mid = (m - 1) / 2;

	Node *left_node = right_node;
	right_node = new Node;

	for (int i = mid + 1; i < m; i++) {
		right_node->values[i - mid - 1] = left_node->value[i];
		right_node->children[i - mid - 1] = left_node->children[i];
	}

	right_node->children[m - mid - 1] = left_node->children[m];

	left_node->capacity = mid + 1;
	right_node->capacity = m - mid;

	return left_node;
}

template <int m, typename T>
void BTree<m, T>::insert_within_(Node *node, int child_index, T value, Node *child) {
	for (int i = node->capacity; i > std::max(child_index, 1); i--) {
		node->children[i] = node->children[i - 1];
		node->value[i - 1] = node->value[i - 2];
	}

	if (child_index == 0) {
		node->children[1] = node->children[0];
	}

	int value_index = std::min(child_index, m - 1);

	node->children[child_index] = child;
	node->values[value_index] = value;
}

template <int m, typename T>
int BTree<m, T>::child_key_(Node *node, T value) {
	for (int i = 0; i < node->capacity - 1; i++) {
		if (value < node->values[i]) {
			return i;
		}
	}

	return node->capacity - 1;
}

template <int m, typename T>
void BTree<m, T>::kill_(Node *node) {
	if (node->capacity > 0 && node->children[0] != nullptr) {
		for (int i = 0; i < node->children.size(); i++) {
			this->kill_(node->children[i]);
		}
	}

	delete node;
}

template <int m, typename T>
BTree<m, T>::~BTree() {
	if (this->root_ != nullptr) {
		this->kill_(this->root_);
	}
}

} // namespace eda

#endif // B_TREE_B_TREE_IPP_

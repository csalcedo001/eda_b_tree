#ifndef B_TREE_B_TREE_IPP_
#define B_TREE_B_TREE_IPP_

#include "b_tree.hpp"

#include "node.hpp"

namespace eda {

template <int m, typename T>
BTree<m, T>::BTree() : head_(nullptr) {}

template <int m, typename T>
BTree<m, T>::~BTree() {
	this->kill_(this->head_);
}

template <int m, typename T>
void BTree<m, T>::print() {
	this->print_(this->head_, 0);
}

template <int m, typename T>
void BTree<m, T>::insert(T value) {
	if (this->head_ == nullptr) {
		this->head_ = new Node;

		this->head_->values[0] = value;
		this->head_->children[0] = nullptr;
		this->head_->children[1] = nullptr;

		this->head_->capacity = 2;
	}
	else if (this->insert_(this->head_, value) == OVERFLOW) {
		Node *right_child = this->head_;
		Node *left_child = this->divide_(right_child);

		this->head_ = new Node;

		this->head_->values[0] = left_child->values[left_child->capacity - 1];
		this->head_->children[0] = left_child;
		this->head_->children[1] = right_child;
		
		this->head_->capacity = 2;
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
		Node *new_child = this->divide_(node->children[child_index]);
		this->insert_within_(node, child_index, new_child->values[new_child->capacity - 1], new_child);
	}

	return node->capacity == m + 1 ? OVERFLOW : OK;
}

template <int m, typename T>
typename BTree<m, T>::Node *BTree<m, T>::divide_(Node *&right_node) {
	int mid = (m - 1) / 2;

	Node *left_node = right_node;
	right_node = new Node;

	for (int i = mid + 1; i < m; i++) {
		right_node->values[i - mid - 1] = left_node->values[i];
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
		node->values[i - 1] = node->values[i - 2];
	}

	if (child_index == 0) {
		node->children[1] = node->children[0];
	}

	int value_index = std::min(child_index, m - 1);

	node->children[child_index] = child;
	node->values[value_index] = value;

	node->capacity++;
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
void BTree<m, T>::print_(Node *node, int level) {
	if (node != nullptr) {
		this->print_(node->children[0], level + 1);

		for (int i = 1; i < node->capacity; i++) {
			for (int j = 0; j < level; j++) {
				std::cout << "    ";
			}
			std::cout << node->values[i - 1] << std::endl;

			this->print_(node->children[i], level + 1);
		}
	}
}

template <int m, typename T>
void BTree<m, T>::kill_(Node *node) {
	if (node != nullptr) {
		for (int i = 0; i < node->capacity; i++) {
			this->kill_(node->children[i]);
		}

		delete node;
	}
}

} // namespace eda

#endif // B_TREE_B_TREE_IPP_

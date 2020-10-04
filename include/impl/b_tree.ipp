#ifndef B_TREE_B_TREE_IPP_
#define B_TREE_B_TREE_IPP_

#include "b_tree.hpp"

#include "node.hpp"

namespace eda {

namespace b_tree {

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
		this->head_ = new Node<m, T>;

		this->head_->values_[0] = value;
		this->head_->children_[0] = nullptr;
		this->head_->children_[1] = nullptr;

		this->head_->capacity_ = 2;
	}
	else if (this->insert_(this->head_, value) == NODE_OVERFLOW) {
		Node<m, T> *right_child = this->head_;
		Node<m, T> *left_child = this->divide_(right_child);

		this->head_ = new Node<m, T>;

		this->head_->values_[0] = left_child->values_[left_child->capacity_ - 1];
		this->head_->children_[0] = left_child;
		this->head_->children_[1] = right_child;
		
		this->head_->capacity_ = 2;
	}
}

template <int m, typename T>
typename BTree<m, T>::State BTree<m, T>::insert_(Node<m, T> *node, T value) {
	int child_index = this->child_key_(node, value);
	int value_index = std::min(child_index, m - 1);

	Node<m, T> *child = node->children_[child_index];

	if (child == nullptr) {
		this->insert_within_(node, child_index, value, nullptr);
	}
	else if (this->insert_(child, value) == NODE_OVERFLOW) {
		Node<m, T> *new_child = this->divide_(node->children_[child_index]);
		this->insert_within_(node, child_index, new_child->values_[new_child->capacity_ - 1], new_child);
	}

	return node->capacity_ == m + 1 ? NODE_OVERFLOW : NODE_OK;
}

template <int m, typename T>
Node<m, T> *BTree<m, T>::divide_(Node<m, T> *&right_node) {
	int mid = (m - 1) / 2;

	Node<m, T> *left_node = right_node;
	right_node = new Node<m, T>;

	for (int i = mid + 1; i < m; i++) {
		right_node->values_[i - mid - 1] = left_node->values_[i];
		right_node->children_[i - mid - 1] = left_node->children_[i];
	}

	right_node->children_[m - mid - 1] = left_node->children_[m];

	left_node->capacity_ = mid + 1;
	right_node->capacity_ = m - mid;

	return left_node;
}

template <int m, typename T>
void BTree<m, T>::insert_within_(Node<m, T> *node, int child_index, T value, Node<m, T> *child) {
	for (int i = node->capacity_; i > std::max(child_index, 1); i--) {
		node->children_[i] = node->children_[i - 1];
		node->values_[i - 1] = node->values_[i - 2];
	}

	if (child_index == 0) {
		node->children_[1] = node->children_[0];
	}

	int value_index = std::min(child_index, m - 1);

	node->children_[child_index] = child;
	node->values_[value_index] = value;

	node->capacity_++;
}

template <int m, typename T>
int BTree<m, T>::child_key_(Node<m, T> *node, T value) {
	for (int i = 0; i < node->capacity_ - 1; i++) {
		if (value < node->values_[i]) {
			return i;
		}
	}

	return node->capacity_ - 1;
}

template <int m, typename T>
void BTree<m, T>::print_(Node<m, T> *node, int level) {
	if (node != nullptr) {
		this->print_(node->children_[0], level + 1);

		for (int i = 1; i < node->capacity_; i++) {
			for (int j = 0; j < level; j++) {
				std::cout << "    ";
			}
			std::cout << node->values_[i - 1] << std::endl;

			this->print_(node->children_[i], level + 1);
		}
	}
}

template <int m, typename T>
void BTree<m, T>::kill_(Node<m, T> *node) {
	if (node != nullptr) {
		for (int i = 0; i < node->capacity_; i++) {
			this->kill_(node->children_[i]);
		}

		delete node;
	}
}

} // namespace b_tree

} // namespace eda

#endif // B_TREE_B_TREE_IPP_

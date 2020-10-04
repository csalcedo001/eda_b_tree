#ifndef B_TREE_B_TREE_IPP_
#define B_TREE_B_TREE_IPP_

#include "b_tree.hpp"

#include "node.hpp"

namespace eda {

namespace b_tree {

template <typename T, int m>
BTree<T, m>::BTree() : head_(nullptr) {}

template <typename T, int m>
BTree<T, m>::~BTree() {
	this->kill(this->head_);
}

template <typename T, int m>
void BTree<T, m>::print() {
	this->print(this->head_, 0);
}

template <typename T, int m>
void BTree<T, m>::insert(T value) {
	if (this->head_ == nullptr) {
		this->head_ = new Node<T, m>;

		this->head_->values_[0] = value;
		this->head_->children_[0] = nullptr;
		this->head_->children_[1] = nullptr;

		this->head_->capacity_ = 2;
	}
	else if (this->insert(this->head_, value) == NODE_OVERFLOW) {
		Node<T, m> *right_child = this->head_;
		Node<T, m> *left_child = this->divide(right_child);

		this->head_ = new Node<T, m>;

		this->head_->values_[0] = left_child->values_[left_child->capacity_ - 1];
		this->head_->children_[0] = left_child;
		this->head_->children_[1] = right_child;
		
		this->head_->capacity_ = 2;
	}
}

template <typename T, int m>
typename BTree<T, m>::State BTree<T, m>::insert(Node<T, m> *node, T value) {
	int child_index = this->child_key(node, value);
	int value_index = std::min(child_index, m - 1);

	Node<T, m> *child = node->children_[child_index];

	if (child == nullptr) {
		this->insert_within(node, child_index, value, nullptr);
	}
	else if (this->insert(child, value) == NODE_OVERFLOW) {
		Node<T, m> *new_child = this->divide(node->children_[child_index]);
		this->insert_within(node, child_index, new_child->values_[new_child->capacity_ - 1], new_child);
	}

	return node->capacity_ == m + 1 ? NODE_OVERFLOW : NODE_OK;
}

template <typename T, int m>
Node<T, m> *BTree<T, m>::divide(Node<T, m> *&right_node) {
	int mid = (m - 1) / 2;

	Node<T, m> *left_node = right_node;
	right_node = new Node<T, m>;

	for (int i = mid + 1; i < m; i++) {
		right_node->values_[i - mid - 1] = left_node->values_[i];
		right_node->children_[i - mid - 1] = left_node->children_[i];
	}

	right_node->children_[m - mid - 1] = left_node->children_[m];

	left_node->capacity_ = mid + 1;
	right_node->capacity_ = m - mid;

	return left_node;
}

template <typename T, int m>
void BTree<T, m>::insert_within(Node<T, m> *node, int child_index, T value, Node<T, m> *child) {
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

template <typename T, int m>
int BTree<T, m>::child_key(Node<T, m> *node, T value) {
	for (int i = 0; i < node->capacity_ - 1; i++) {
		if (value < node->values_[i]) {
			return i;
		}
	}

	return node->capacity_ - 1;
}

template <typename T, int m>
void BTree<T, m>::print(Node<T, m> *node, int level) {
	if (node != nullptr) {
		this->print(node->children_[0], level + 1);

		for (int i = 1; i < node->capacity_; i++) {
			for (int j = 0; j < level; j++) {
				std::cout << "    ";
			}
			std::cout << node->values_[i - 1] << std::endl;

			this->print(node->children_[i], level + 1);
		}
	}
}

template <typename T, int m>
void BTree<T, m>::kill(Node<T, m> *node) {
	if (node != nullptr) {
		for (int i = 0; i < node->capacity_; i++) {
			this->kill(node->children_[i]);
		}

		delete node;
	}
}

} // namespace b_tree

} // namespace eda

#endif // B_TREE_B_TREE_IPP_

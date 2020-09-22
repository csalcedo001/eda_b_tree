#ifndef B_TREE_B_TREE_IPP_
#define B_TREE_B_TREE_IPP_

namespace eda {

template <int m, typename T>
BTree<m, T>::BTree() {}

template <int m, typename T>
void BTree<m, T>::insert(T value) {
	if (this->root_ == nullptr) {
		this->root_ = new Node;

		this->root_.values[0] = value;

		// TODO: Check if capacity should be 1 or 2 (according to m-way branching)
		this->root_.capacity = 1;
	}
	else if (!this->insert_(this->root_, value)) {
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
bool BTree<m, T>::insert_(Node *node, T value) {
	int child_index = this->child_key_(node, value);
	int value_index = std::min(child_index, m - 1);

	Node *child = node->children[child_index];

	if (child == nullptr) {
		this->insert_within_(node, child_index, value, nullptr);
	}
	else if (!this->insert_(child, value)) {
		Node *new_child = this->divide_(child);
		this->insert_within_(node, child_index, child->values[child->capacity], new_child);
	}

	return this->capacity == m;
}

template <int m, typename T>
typename BTree<m, T>::Node *BTree<m, T>::divide_(Node *node) {
	// TODO: check if mid follows this formula:
	int mid = m / 2;

	Node *new_node = new Node;

	for (int i = 0; i < mid; i++) {
		new_node->values[i] = node->value[i + mid];
		new_node->children[i] = node->children[i + mid];
	}
	// TODO: verify m
	for (int i = 0; i < m - mid; i++) {
		node->values[i] = node->value[i + mid + 1];
		node->children[i] = node->children[i + mid + 1];
	}
	
	return new_node;
}

} // namespace eda

#endif // B_TREE_B_TREE_IPP_

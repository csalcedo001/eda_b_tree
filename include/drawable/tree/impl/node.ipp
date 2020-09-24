#ifndef B_TREE_DRAWABLE_TREE_NODE_IPP_
#define B_TREE_DRAWABLE_TREE_NODE_IPP_

#include "drawable/drawable.hpp"

namespace eda {

namespace drawable {

template <typename T>
void Tree<T>::Node::render(double x, double y) {
	for (float i = 0; i < node->size() - 1; i++) {
		render_shape(node->values(i), i + x - (node->size() - 1.0f) / 2.0f, y);
	}

	double current = x - node->width() / 2.0f;

	for (int i = 0; i < node->size(); i++) {
		if (node->children(i) != nullptr) {
			node->children(i)->render(current + node->children(i)->width() / 2.0f, y - 2.0f);
		}

		current += 1.0f + node->children(i)->width();
	}
}

template <typename T>
void Tree<T>::Node::width() {
	return this->leaves_() + this->leave_level_nodes_() - 1;
}

} // namespace drawable

} // namespace eda

#endif // B_TREE_DRAWABLE_TREE_NODE_IPP_

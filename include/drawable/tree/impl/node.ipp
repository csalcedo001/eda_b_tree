#ifndef B_TREE_DRAWABLE_TREE_NODE_IPP_
#define B_TREE_DRAWABLE_TREE_NODE_IPP_

#include "drawable/tree/tree.hpp"

#include "drawable/drawable.hpp"
// #include "drawable/shape.hpp"

namespace eda {

namespace drawable {

template <typename T>
void Tree<T>::Node::render(double x, double y) {
	for (float i = 0; i < this->values(); i++) {
		render_shape(this->value(i), i + x - this->values() / 2.0f, y);
	}

	double current = x - this->width() / 2.0f;

	for (int i = 0; i < this->children(); i++) {
		if (this->child(i) != nullptr) {
			this->child(i)->render(current + this->child(i)->width() / 2.0f, y - 2.0f);
		}

		current += 1.0f + this->child(i)->width();
	}
}

template <typename T>
int Tree<T>::Node::width() {
	return this->leaves_() + this->leave_level_values_() - 1;
}

} // namespace drawable

} // namespace eda

#endif // B_TREE_DRAWABLE_TREE_NODE_IPP_

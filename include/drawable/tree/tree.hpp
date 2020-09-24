#ifndef B_TREE_DRAWABLE_TREE_TREE_HPP_
#define B_TREE_DRAWABLE_TREE_TREE_HPP_

#include "drawable/drawable.hpp"

namespace eda {

namespace drawable {

template <typename T>
class Tree : Drawable {
private:
	class Node;

public:
	void render(double x, double y);

private:
	Node *root_();
};

} // namespace drawable

} // namespace eda

#include "drawable/tree/impl/tree.ipp"

#endif // B_TREE_DRAWABLE_TREE_TREE_HPP_

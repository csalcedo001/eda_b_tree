#ifndef B_TREE_DRAWABLE_TREE_IPP_
#define B_TREE_DRAWABLE_TREE_IPP_

namespace eda {

namespace drawable {

template <typename T>
void Tree<T>::render(double x, double y) {
	this->root_()->render(x, y);
}

} // namespace drawable

} // namespace eda

#endif // B_TREE_DRAWABLE_TREE_IPP_

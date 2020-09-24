#ifndef B_TREE_DRAWABLE_NODE_HPP_
#define B_TREE_DRAWABLE_NODE_HPP_

#include "drawable/drawable.hpp"

namespace eda {

namespace drawable {

template <typename T>
class Tree<T>::Node : public Drawable {
public:
	int width();

public:
	virtual int size() = 0;
	
	virtual T values(int) = 0;
	virtual Node *children(int) = 0;

private:
	virtual int leaves_() = 0;
	virtual int leave_level_nodes_() = 0;
};

} // namespace drawable

} // namespace eda

#include "drawable/impl/node.ipp"

#endif // B_TREE_DRAWABLE_NODE_HPP_

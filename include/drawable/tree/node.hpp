#ifndef B_TREE_DRAWABLE_TREE_NODE_HPP_
#define B_TREE_DRAWABLE_TREE_NODE_HPP_

#include "drawable/tree/node.hpp"

#include "drawable/drawable.hpp"

namespace eda {

namespace drawable {

template <typename T>
class Tree<T>::Node : public Drawable {
public:
	int width();
	void render(double x, double y);

public:
	virtual int values() = 0;
	virtual int children() = 0;
	
	virtual T value(int) = 0;
	virtual Node *child(int) = 0;
	virtual bool is_leave() = 0;

protected:
	virtual int leaves_() = 0;
	virtual int leave_level_values_() = 0;
};

} // namespace drawable

} // namespace eda

#include "drawable/tree/impl/node.ipp"

#endif // B_TREE_DRAWABLE_TREE_NODE_HPP_

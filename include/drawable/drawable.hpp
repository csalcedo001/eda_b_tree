#ifndef B_TREE_DRAWABLE_DRAWABLE_HPP_
#define B_TREE_DRAWABLE_DRAWABLE_HPP_

namespace eda {

namespace drawable {

class Drawable {
public:
	virtual void render(double x, double y) = 0;
};

} // namespace drawable

} // namespace eda

#endif // B_TREE_DRAWABLE_DRAWABLE_HPP_

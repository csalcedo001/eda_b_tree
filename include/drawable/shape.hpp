#ifndef B_TREE_DRAWABLE_SHAPE_HPP_
#define B_TREE_DRAWABLE_SHAPE_HPP_

namespace eda {

namespace drawable {

void init_render();
void cleanup_render();
void render_shape(int, double, double);
void render_square(double x, double y);
void render_text(int e, double x, double y);
void render_shape(std::vector<int> &v, double x, double y);

} // namespace eda

} // namespace drawable

#include "drawable/impl/shape.ipp"

#endif // B_TREE_DRAWABLE_SHAPE_HPP_

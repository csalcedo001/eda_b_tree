#ifndef B_TREE_B_STAR_TREE_HPP_
#define B_TREE_B_STAR_TREE_HPP_

#include <array>

#include "b_star_tree/b_star/src/utec/memory/bstar.h"
#include "drawable/tree.hpp"

namespace eda {

template <int m, typename T>
class BStarTree :
	public utec::memory::bstar<T, m>,
	public drawable::Tree<T>
{
public:
	class Node;

private:
    Node *root;

public:
    BStarTree();

private:
	BStarTree<m, T>::Node *root_();
};

} // namespace eda

#include "b_star_tree/impl/b_star_tree.ipp"

#endif // B_TREE_B_STAR_TREE_HPP_

#ifndef B_TREE_B_STAR_TREE_IPP_
#define B_TREE_B_STAR_TREE_IPP_

#include <array>

#include "b_star_tree/b_star_tree.hpp"

#include "b_star_tree/node.hpp"

namespace eda {

template <int m, typename T>
BStarTree<m, T>::BStarTree() : root(nullptr), utec::memory::bstar<T, m>() {
    std::cout << "Constructor: " << root << std::endl;
}

template <int m, typename T>
typename BStarTree<m, T>::Node *BStarTree<m, T>::root_() {
    std::cout << this->root << std::endl;
	return this->root;
}

} // namespace eda

#endif // B_TREE_B_STAR_TREE_IPP_

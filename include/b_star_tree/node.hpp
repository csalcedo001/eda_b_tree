#ifndef B_TREE_B_STAR_TREE_NODE_HPP_
#define B_TREE_B_STAR_TREE_NODE_HPP_

#include <vector>

#include "b_star_tree/b_star_tree.hpp"

#include "b_star_tree/b_star/src/utec/memory/bstar.h"
#include "drawable/tree.hpp"

namespace eda {

template <int m, typename T>
class BStarTree<m, T>::Node :
	public utec::memory::bstar<T, m>::Node,
	public drawable::Tree<T>::Node
{
public:
    vector<T> keys;
    vector<Node*> children_;
    bool isLeaf;
    
public:
    Node();
    Node(typename utec::memory::bstar<T, m>::Node);
    
	int children();
	int values();

	T value(int);
	Node *child(int);
	bool is_leave();

private:
	int leaves_();
	int leave_level_values_();

};

} // namespace eda

#include "b_star_tree/impl/node.ipp"

#endif // B_TREE_B_STAR_TREE_NODE_HPP_

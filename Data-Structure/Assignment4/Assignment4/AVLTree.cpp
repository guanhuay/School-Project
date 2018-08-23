//
//  AVLTree.cpp
//  Binary Search Trees
//
//  Derived by Ted Kirkpatrick on 2015-06-05.
//  from Goodrich et al., 2d. Ed., Section 10.2.2.
//

#include <iostream>

#include "AVLTree.h"

using std::tie;

void AVLTree::setHeight(TPos v) {
    int hl = height(v.left());
    int hr = height(v.right());
    v->setHeight(1 + std::max(hl, hr));
}

bool AVLTree::isBalanced(const TPos& v) const {
    int bal = height(v.left()) - height(v.right());
    return ((-1 <= bal) && bal <= 1);
}

AVLTree::TPos AVLTree::tallGrandchild(const TPos& z) const {
    TPos zl = z.left();
    TPos zr = z.right();
    if (height(zl) >= height(zr))
        if (height(zl.left()) >= height(zl.right()))
            return zl.left();
        else
            return zl.right();
    else
        if (height(zr.right()) >= height(zr.left()))
            return zr.right();
        else
            return zr.left();
}

void AVLTree::rebalance(const TPos& v) {
    TPos z = v;
    while ( ! (z == ST::root())) {
        z = z.parent();
        setHeight(z);
        if ( ! isBalanced(z)) {
            TPos x = tallGrandchild(z);
            z = T.restructure(x);
            setHeight(z.left());
            setHeight(z.right());
            setHeight(z);
        }
    }
}

AVLTree::Iterator AVLTree::insert(const K& k, const V& x) {
    TPos v = inserter(k, x);
    setHeight(v);
    rebalance(v);
    return Iterator(v);
}

void AVLTree::erase(const K& k) {
    TPos v {};
    long count {};
    tie(v, count) = finder(k, ST::root());
    comparisons += count;
    if (Iterator(v) == ST::end())
        throw NonexistentElement("Erase of nonexistent");
    TPos w = eraser(v);
    rebalance(w);
}

std::ostream& operator<<(std::ostream& os, const AVLEntry& e)
{
    return os << '(' << e.key() << ", " << e.value() << " [" << e.height() << "])";
}

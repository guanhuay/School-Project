//
//  AVLTree.h
//  Binary Search Trees
//
//  Derived by Ted Kirkpatrick on 2015-06-05
//  from Goodrich et al., 2d. Ed., Section 10.2.2.
//

#ifndef __Binary_Search_Trees__AVLTree__
#define __Binary_Search_Trees__AVLTree__

#include "SearchTree.h"
#include "AVLEntry.h"

class AVLTree : public SearchTree {
public:
    using AVLEntry = AVLEntry;
    using Iterator = SearchTree::Iterator;
    
protected:
    using K = AVLEntry::Key;
    using V = AVLEntry::Value;
    using ST = SearchTree;
    using TPos = ST::TPos;
    
public:
    AVLTree() : ST() {};
    Iterator insert(const K& k, const V& x);
    void erase(const K& k);
    void erase(const Iterator& p);
    
protected:
    int height(const TPos& v) const { return (v.isExternal() ? 0 : v->height()); }
    void setHeight(TPos v);
    bool isBalanced(const TPos& v) const;
    TPos tallGrandchild(const TPos& v) const;
    void rebalance(const TPos& v);
};



#endif /* defined(__Binary_Search_Trees__AVLTree__) */

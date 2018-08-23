//
//  BinaryTree.h
//  Binary Search Trees
//
//  Derived by Ted Kirkpatrick on 2015-05-30.
//  from Goodrich et al., 2d. ed., pp. 290--294.
//

#ifndef Binary_Search_Trees_BinaryTree_h
#define Binary_Search_Trees_BinaryTree_h

#include <string>
#include <memory>
#include <list>
#include <iostream>
#include <cassert>

using std::shared_ptr;
using std::make_shared;
using std::weak_ptr;

using std::string;

template<typename E>
class BinaryTree {
protected:
    
    struct Node {
        using EType = E;
        EType elt;
        weak_ptr<Node> par;
        shared_ptr<Node> left;
        shared_ptr<Node> right;
        Node() : elt(), par(), left(), right() { }
    };

public:
    class Position {
    public:
        Position(shared_ptr<Node>n) : node(n) {}
        Position(const Position& from) : node(from.node) {}
        Position() : node() {}
        
        bool operator==(const Position& rpos) const { return node == rpos.node; }
        bool operator!=(const Position& rpos) const { return node != rpos.node; }
        
        typename Node::EType& operator*() const { return node->elt; }
        typename Node::EType* operator->() const { return &node->elt; }
        
        Position left() const { return Position(node->left); }
        Position right() const { return Position(node->right); }
        Position parent() const { return Position(node->par.lock()); }
        bool isRoot() const { auto sp = node->par.lock(); return sp && sp == nullptr; }
        bool isExternal() const { return node->left == nullptr && node->right == nullptr; }
        bool isInternal() const { return ! isExternal(); }
       
        friend class BinaryTree;
        
        //Debugging
        long use_count() const { return node.use_count(); }
        string counted_elt() const;

    private:
        shared_ptr<Node> node;
    };

    using TPos = Position;
    using TPosList = std::list<TPos>;
    friend TPos;

public:
    BinaryTree() : _root(nullptr), n(0) {}
    BinaryTree(const BinaryTree& bt) = delete;
    BinaryTree operator=(const BinaryTree& bt) = delete;
    explicit BinaryTree(int n);
    
    int size() const { return n; }
    bool empty() const { return _root == nullptr; }
    TPos root() const { return Position(_root); }
    TPosList positions() const;
    void addRoot();
    void expandExternal(const Position&);
    Position removeAboveExternal(const Position& p);
    Position restructure(const Position& x);
    
protected:
    // These thee functions leave the invariant for BinaryTree.n
    // inconsistent. It is up to the caller to use them in a way
    // that preserves the invariant after all calls.
    void replace(const Position& place, const Position& subtree);
    void setLeft(const Position& place, const Position& subtree);
    void setRight(const Position& place, const Position& subtree);
    
protected:
    void preorder(shared_ptr<Node> v, TPosList& pl) const;
    void delSubTree(const Position& v);
    
private:
    shared_ptr<Node> _root;
    int n;
};

template<typename E>
typename BinaryTree<E>::TPosList BinaryTree<E>::positions() const {
    auto lst = TPosList();
    if (_root != nullptr)
        preorder(_root, lst);
    return TPosList(lst);
}

template<typename E>
void BinaryTree<E>::preorder(shared_ptr<Node> v, TPosList& lst) const {
    assert(v != nullptr);
    lst.push_back(Position(v));
    if (v->left != nullptr)
        preorder(v->left, lst);
    if (v->right != nullptr)
        preorder(v->right, lst);
}

template<typename E>
void BinaryTree<E>::addRoot() {
    assert(_root == nullptr);
    _root = make_shared<Node>();
    n = 1;
}

template<typename E>
void BinaryTree<E>::expandExternal(const Position& p) {
    assert(p.isExternal());
    auto v = p.node;
    
    v->left = make_shared<Node>();
    v->left->par = v;
    v->right = make_shared<Node>();
    v->right->par = v;
    n+=2;
}

template<typename E>
typename BinaryTree<E>::Position BinaryTree<E>::removeAboveExternal(const Position& p) {
    assert( ! p.isRoot());
    assert(p.isExternal());
    auto w = p.node;
    auto v = w->par.lock();
    assert(v != nullptr);  // Position's Node must be actively in the tree
    auto sib = (w == v->left ? v->right : v->left);
    if (v == _root) {
        _root = sib;
        sib->par.reset();
    }
    else {
        auto gpar = v->par.lock();
        assert(gpar != nullptr); //Position's parent Node must also be actively in the tree
        if (v == gpar->left) gpar->left = sib;
        else gpar->right = sib;
        sib->par = gpar;
    }
    n -= 2;
    return Position(sib);
}
    
template<typename E>
/*
 Algorithm restructure (), Code Fragment 10.2, p. 442.
 */
typename BinaryTree<E>::Position BinaryTree<E>::restructure(const Position& x) {
    assert( ! x.isRoot() && ! x.parent().isRoot());
    auto y = x.parent();
    auto z = y.parent();
    
    // Step 1 of algorithm: Determine node order
    
    // a, b, c will hold the inorder traversal of x, y, z
    // (Equivalent to: a < b < c)
    auto a = TPos{};
    auto b = TPos{};
    auto c = TPos{};
    
    // T0--T3 will hold the inorder subtrees of a, b, c
    auto T0 = TPos{};
    auto T1 = TPos{};
    auto T2 = TPos{};
    auto T3 = TPos{};
    
    // Case 1: Grandparent (z) is smallest value of 3
    if (z->key() < y->key()) {
        a = z;
        T0 = z.left();
        // Parent (y) is middle value
        if (y->key() < x->key()){
            b = y;
            T1 = y.left();
            c = x;
            T2 = x.left();
            T3 = x.right();
        }
        // Child (x) is middle value
        else {
            b = x;
            T1 = x.left();
            T2 = x.right();
            c = y;
            T3 = y.right();
        }
    }
    // Case 2: Grandparent (z) is largest value of 3
    // (This exhausts all cases:  The grandparent can never be middle or equal)
    else {
        c = z;
        T3 = z.right();
        // Parent (y) is smallest value
        if (y->key() < x->key()) {
            a = y;
            T0 = y.left();
            b = x;
            T1 = x.left();
            T2 = x.right();
        }
        // Child (x) is smallest value
        else {
            a = x;
            T0 = x.left();
            T1 = x.right();
            b = y;
            T2 = y.right();
        }
    }
    
    // Balance the tree, maintaining the order
    
    // Step 2 of algorithm: Move middle value to middle node
    replace(z, b);
    
    // Step 3 of algorithm: Build left subtree of middle node
    setLeft(a, T0);
    setRight(a, T1);
    setLeft(b, a);
    
    // Step 4 of algorithm: Build right subtree of middle node
    setLeft(c, T2);
    setRight(c, T3);
    setRight(b, c);
    
    return b;
}

/*
 Replace place with subtree.
 
 This operation does NOT update the tree node count. It is to be used as part
 of a larger restructuring operation that simply reorganizes nodes and does not
 add or delete any. Its primary use case is the restructure() operaton for
 AVL search trees.
 
 Because this function can violate the invariants, it is protected, only
 accessible to subclasses and friends.
 */
template<typename E>
void BinaryTree<E>::replace(const Position& place, const Position& subtree) {
    if (place.isRoot()) {
        _root = subtree.node;
        subtree.node->par.reset();
    }
    else {
        auto parent = Position(place.node->par.lock());
        assert(parent.node);
        if (parent.left() == place)
            parent.node->left = subtree.node;
        else
            parent.node->right = subtree.node;
        subtree.node->par = parent.node;
    }
}
    
template<typename E>
void BinaryTree<E>::setLeft(const Position& place, const Position& subtree) {
    place.node->left = subtree.node;
    subtree.node->par = place.node;
}
    
template<typename E>
void BinaryTree<E>::setRight(const Position& place, const Position& subtree) {
    place.node->right = subtree.node;
    subtree.node->par = place.node;
}

// Create binary tree with specified height
template<typename E>
BinaryTree<E>::BinaryTree(int height) : _root(),  n(0) {
    assert(height > 0);
    std::cout << "In BinaryTree(int)\n";
    addRoot();
    auto next = root();
    for (int i = 1; i < height; i++) {
        expandExternal(next);
        next = next.left();
    }
    
}

// Return string (element contents, use_count) (debugging)
template<typename E>
string BinaryTree<E>::Position::counted_elt() const {
    return "(" + string(this->operator*()) + ", " + std::to_string(this->use_count()) + ")";
}

#endif

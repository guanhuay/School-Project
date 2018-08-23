//
//  SearchTree.cpp
//  Binary Search Trees
//
//  Derived by Ted Kirkpatrick on 2015-06-02
//  from Goodrich et al., 2d. Ed., Section 10.1.
//
#include <cassert>

#include "SearchTree.h"

using std::make_pair;
using std::tie;

// Inorder traversal from node v
SearchTree::Iterator& SearchTree::Iterator::operator++() {
    TPos w = v.right();
    if (w.isInternal()) {
        do {
            v = w;
            w = w.left();
        }
        while (w.isInternal());
    }
    else {
        w = v.parent();
        while (v == w.right()) {
            v = w;
            w = w.parent();
        }
        v = w;
    }
    return *this;
}

SearchTree::SearchTree() : T{}, n{0}, comparisons{0L} {
    T.addRoot();
    T.expandExternal(T.root());
}

SearchTree::TPos SearchTree::root() const { return T.root().left(); }

SearchTree::Iterator SearchTree::begin() const {
    TPos v = root();
    while (v.isInternal())
        v = v.left();
    return Iterator(v.parent());
}

SearchTree::Iterator SearchTree::end() const { return Iterator(T.root()); }

std::pair<SearchTree::TPos,int> SearchTree::finder(const K& k, TPos v) {
    int count {0};
    while (! v.isExternal()) {
        ++count;
        if (k < v->key()) {
            v = v.left();
        }
        else if (v->key() < k) {
            v = v.right();
        }
        else
            return make_pair(v, count);
    }
    return make_pair(v, count);
}

SearchTree::Iterator SearchTree::find(const K& k) {
    TPos v {};
    long count {};
    tie(v,count) = finder(k, root());
    comparisons += count;
    if(v.isInternal())
        return Iterator(v);
    else
        return end();
}

SearchTree::TPos SearchTree::inserter(const K& k, const V& x) {
    TPos v {};
    long count {};
    tie(v,count) = finder(k, root());
    comparisons += count;
    if (v.isInternal())
        return v; // Already there---dictionary ADT keeps 1 copy
    T.expandExternal(v);
    v->setKey(k);
    v->setValue(x);
    n++;
    return v;
}

SearchTree::Iterator SearchTree::insert(const K& k, const V& x) {
    TPos v = inserter(k, x);
    return Iterator(v);
}

SearchTree::TPos SearchTree::eraser(TPos& v) {
    TPos w;
    if (v.left().isExternal())
        w = v.left();
    else if (v.right().isExternal())
        w = v.right();
    else {
        w = v.right();
        do {
            w = w.left();
        }
        while (w.isInternal());
        TPos u = w.parent();
        v->setKey((*u).key());
        v->setValue((*u).value());
    }
    n--;
    return T.removeAboveExternal(w);
}

void SearchTree::erase(const K& k) {
    TPos v {};
    long count {};
    tie(v,count) = finder(k, root());
    comparisons += count;
    if (v.isExternal())
        throw Exceptions::NonexistentElement("Erase of nonexistent value");
    eraser(v);
}

/*
 Display the tree structure as an indented hierarchy on os.
 Used for debugging.
 */
void SearchTree::debugPrintTree(std::ostream& os, const string& name) const {
    os << "SearchTree " << name << " size " << T.size()-2 << '\n';
    auto depth = int{0};
    
    if (empty())
        os << "<empty--only sentinel node>\n";
    else
        debugPrintTree(os, T.root().left(), depth);
}

void SearchTree::debugPrintTree(std::ostream& os, const TPos& subRoot, int depth) const {
    printIndented(os, *subRoot, depth);

    if (subRoot.left().isExternal())
        printIndented(os, "X", depth+1);
    else
        debugPrintTree(os, subRoot.left(), depth+1);
    
    if (subRoot.right().isExternal())
        printIndented(os, "X", depth+1);
    else
        debugPrintTree(os, subRoot.right(), depth+1);
}

void SearchTree::printIndented(std::ostream& os, const char* st, int depth) const {
    for (auto i =  0; i < depth*indent; i++)
        os << ' ';
    os << st << "\n";
}
void SearchTree::printIndented(std::ostream& os, const ET& val, int depth) const {
    for (auto i =  0; i < depth*indent; i++)
        os << ' ';
    os << val << "\n";
}
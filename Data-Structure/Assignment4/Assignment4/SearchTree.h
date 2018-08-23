//
//  SearchTree.h
//  Binary Search Trees
//
//  Derived by Ted Kirkpatrick on 2015-06-02
//  from Goodrich et al., 2d. Ed., Section 10.1.
//

#ifndef __Binary_Search_Trees__SearchTree__
#define __Binary_Search_Trees__SearchTree__

#include <iostream>
#include <string>
#include <utility>

#include "Exception.h"
#include "Entry.h"
#include "AVLEntry.h"
#include "BinaryTree.h"

using std::string;

using ET = AVLEntry;

class SearchTree {
public:
    using K = ET::Key;
    using V = ET::Value;
    class Iterator;
protected:
    using BinaryTree = BinaryTree<ET>;
    using TPos = BinaryTree::Position;
protected:
    BinaryTree T;
    int n;
    long comparisons;
public:
    SearchTree();
    SearchTree(const SearchTree& st) = delete;
    SearchTree& operator=(const SearchTree& st) = delete;
    int size() const { return n; }
    bool empty() const {  return T.root().left().isExternal(); }
    Iterator find(const K& k);
    Iterator insert(const K& k, const V& x);
    void restructure(TPos& x);
    void erase(const K& k) throw (NonexistentElement);
    void erase(const Iterator& p);
    Iterator begin() const;
    Iterator end() const;
    long getComparisons() const { return comparisons; }
    void clearComparisons() { comparisons = 0L; }

    void debugPrintTree(std::ostream& os, const string& name) const;
protected:
    TPos root() const;
    std::pair<TPos, int> finder(const K& k, TPos v);
    TPos inserter(const K& k, const V& x);
    TPos eraser(TPos& v);
    constexpr static int indent {4};
    void debugPrintTree(std::ostream& os, const TPos& subRoot, int depth) const;
    void printIndented(std::ostream& os, const char* st, int depth) const;
    void printIndented(std::ostream& os, const ET& val, int depth) const;

public:
    class Iterator {
    private:
        TPos v;
    public:
        Iterator(const TPos& vv) : v(vv) {}
        const ET& operator*() const { return *v; }
        ET& operator*() { return *v; }
        TPos pos() const { return v; }
        bool operator==(const Iterator& p) const { return v == p.v; }
        bool operator!=(const Iterator& p) const { return ! (*this == p); }
        Iterator& operator ++();
        friend class SearchTree;
    };
};

#endif /* defined(__Binary_Search_Trees__SearchTree__) */

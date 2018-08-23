//
//  AVLEntry.h
//  Binary Search Trees
//
//  Derived by Ted Kirkpatrick on 2015-06-09
//  From Goodrich et al., 2d Ed., Section 10.2.2
//

#ifndef Binary_Search_Trees_AVLEntry_h
#define Binary_Search_Trees_AVLEntry_h

#include <ostream>
#include <string>
using std::string;

#include "Entry.h"
using ETbase = Entry<int,string>;

class AVLTree;

class AVLEntry : public ETbase {
private:
    int ht;
    
protected:
    using K = ETbase::Key;
    using V = ETbase::Value;
    int height() const { return ht; }
    void setHeight(int h) { ht = h; }
    
public:
    AVLEntry(const K& k = K(), const V& v = V()) : ETbase(k, v), ht(0) {}
    friend class AVLTree;
    friend std::ostream& operator<<(std::ostream& os, const AVLEntry& e);
};


#endif

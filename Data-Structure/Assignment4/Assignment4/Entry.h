//
//  Entry.h
//  Binary Search Trees
//
//  Derived by Ted Kirkpatrick on 2015-05-30.
//  from Goodrich et al. 2d. ed., p. 369.
//

#ifndef Binary_Search_Trees_Entry_h
#define Binary_Search_Trees_Entry_h

#include <iostream>

template <typename K, typename V>
class Entry {
public:
    using Key = K;
    using Value = V;
public:
    Entry(const K& k = K(), const V& v = V()) : _key(k), _value(v) {}
    const K& key() const { return _key; }
    const V& value() const { return _value; }
    void setKey(const K& k) { _key = k; }
    void setValue(const V& v) { _value = v; }
    
private:
    K _key;
    V _value;
};

template<typename K, typename V>
std::ostream& operator<<(std::ostream& os, const Entry<K, V>& e)
{
    return os << '(' << e.key() << ", " << e.value() << ')';
}


#endif

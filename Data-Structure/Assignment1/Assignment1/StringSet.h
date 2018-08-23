//
//  StringSet.h
//  Assignment1
//
//  Created by Guanhua Yang on 2015-09-22.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#include <string>
using std::string;
#ifndef StringSet_header
#define StringSet_header
class StringSet
{
public:
    
    
    //Default constructor : Create an array of strings in
    //dynamic memory, with maximum size 4 and current size 0.
    StringSet();
    
    
    //Copy constructor : make a deep copy of its parameter.
    StringSet(const StringSet &);
    
    
    //Destructor : Free dynamic memory associated with the
    //objects string(str) pointer.
    ~StringSet();
    
    
    //Insert Function follow the following algorithm:
    //1.If a string matching the parameter is already in the array,
    //return false and do not change the array.
    //2.Otherwise: Insert the string parameter at the next available index;
    //3.if the underlying array is full, double the maximum size attribute,
    //create an array of twice the size of the current array, copy the contents of the
    //old array to the new array, free memory associated with the old array,
    //and assign new arrays address to objects array pointer, then insert
    //parameter; increment current size and return true.
    bool insert(string);
    
    
    //Remove Function follow the following algorithm:
    //1.If no string matching the parameter is in the array, return false .
    //2.Otherwise: Replace the matching string with the last string in the
    //array(if there is one); decrement current size and return true.
    bool remove(string);
    
    
    //Find function follow the follwing algorithm:
    //1.If a string matching the parameter is in the array return the index of
    //that string,
    //2.otherwise return -1.
    int find(string) const;
    
    
    //Size Function:
    //Return the current size (the number of strings in the array).
    int size() const;
    
    
    //Setunion Function have the following algorithm:
    //Return a StringSet object that contains the union of this object and the
    //parameter(if the result is the empty set the returned StringSet objects
    //current size should equal zero); in case you were wondering, this method is
    //called setunion because union is a reserved word.
    StringSet setunion(const StringSet &) const;
    
    
    //Intersection Function have the following algorithm:
    //Return a StringSet object that contains the intersection of this object and the parameter.
    StringSet intersection(const StringSet &) const;
    
    
    //Difference Function have the following algorithm:
    //Return a StringSet object that contains the set difference of this object and the parameter.
    StringSet difference(const StringSet &) const;
    
    
    //Include this statement in the class definition in StringSet.h.It does not matter whether you
    //put it in the public or private sections.It prevents the compiler from defining a copy assignment
    //operator for StringSet.Unfortunately, the default assignment defined by the language will not be
    //correct for a class like StringSet that assumes it has exclusive use of a storage referenced by a pointer.
    StringSet& operator=(const StringSet &) = delete; // Prevent default copy assignment
    
    ////string get function
    string get(int i);
    
private:
    string *str;
    int currsize;
    int maxsize;
};
#endif

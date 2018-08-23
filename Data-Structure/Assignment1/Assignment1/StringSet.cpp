//
//  StringSet.cpp
//  Assignment1
//
//  Created by Guanhua Yang on 2015-09-22.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#include "StringSet.h"
#include <cassert>

//Default Constructor
StringSet::StringSet()
{
    maxsize = 4;
    currsize = 0;
    str = new string[maxsize];
}


//Copy Constructor
StringSet::StringSet(const StringSet & strset)
{
    maxsize = strset.maxsize;
    currsize = strset.currsize;
    str = new string[maxsize];
    for (int i = 0; i < currsize; i++)
    {
        str[i] = strset.str[i];
    }
}


//destructor
StringSet::~StringSet()
{
    delete[] str;
}


//Insert Function
bool StringSet::insert(string strings)
{
    for (int i = 0; i < currsize; i++)
    {
        if (strings == str[i])
        {
            return false;
        }
    }
    
    
    //check if the memory is enough
    if (currsize >= maxsize)
    {
        string* str_double = new string[maxsize * 2];
        maxsize = maxsize * 2;
        for (int i = 0; i < currsize; i++)
        {
            str_double[i] = str[i];
        }
        delete[] str;
        str = str_double;
    }
    
    str[currsize] = strings;
    currsize++;
    return true;
}


//Remove Function
bool StringSet::remove(string strings)
{
    for (int i = 0; i < currsize; i++)
    {
        if (strings == str[i])
        {
            str[i] = str[currsize - 1];
            currsize--;
            return true;
        }
    }
    return false;
}


//Find the match string in the stringset
int StringSet::find(string strings) const
{
    for (int i = 0; i < currsize; i++)
    {
        if (strings == str[i])
        {
            return i;
        }
    }
    return -1;
}


//Return the current size of the stringset
int StringSet::size() const
{
    return currsize;
}


//Setunion function
StringSet StringSet::setunion(const StringSet & otherset) const
{
    StringSet result;
    if (currsize == 0 && otherset.currsize == 0)
    {
        result.currsize = 0;
        return result;
    }
    else if (currsize == 0)
    {
        for (int i = 0; i<otherset.currsize; i++)
        {
            result.insert(otherset.str[i]);
        }
        return result;
    }
    else if (otherset.currsize == 0)
    {
        for (int i = 0; i<currsize; i++)
        {
            result.insert(str[i]);
        }
        return result;
    }
    
    for (int i = 0; i<currsize; i++)
    {
        result.insert(str[i]);
    }
    
    for (int j = 0; j<otherset.currsize; j++)
    {
        int i = 0;
        for (; i<currsize; i++)
        {
            if (otherset.str[j] == str[i])
            {
                break;
            }
        }
        // make sure there is no duplicate of otherset.str[j]
        if (i == currsize) {
            result.insert(otherset.str[j]);
        }
    }
    return result;
}


//Intersection function
StringSet StringSet::intersection(const StringSet & otherset) const
{
    StringSet result;
    for (int i = 0; i<currsize; i++)
    {
        for (int j = 0; j<otherset.currsize; j++)
        {
            if (str[i] == otherset.str[j])
            {
                result.insert(str[i]);
                break;
            }
        }
    }
    return result; // Return empty StringSet
}


//difference function
StringSet StringSet::difference(const StringSet & otherset) const
{
    StringSet result;
    result.currsize = 0;
    result.maxsize = maxsize;
    
    for (int i = 0; i<currsize; i++)
    {
        int j = 0;
        for (; j<otherset.currsize; j++)
        {
            if (str[i] == otherset.str[j])
            {
                break;
            }
        }
        if (j == otherset.currsize)
            result.insert(str[i]);
    }
    return result;
}



//string get function
string StringSet::get(int i) {
    assert(i < currsize);
    return str[i];
}

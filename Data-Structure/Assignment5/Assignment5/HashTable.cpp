//
//  HashTable.cpp
//  Assignment5
//
//  Created by Guanhua Yang on 2015-11-21.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#include "HashTable.h"
#include <string>
#include <iostream>
#include <vector>
#include <cmath>
using std::vector;
using std::string;

//Default Constructor
HashTable::HashTable():tablesize(101),curritem(0),table(new LinkedList[tablesize]){};

//Constructor take single int argument
HashTable::HashTable(int n)
{
    bool isitprime = false;
    n = 2*n;
    while(!isitprime)
    {
        n++;
        isitprime = is_prime(n);
    }
    tablesize = n;
    table = new LinkedList[tablesize];
    curritem = 0;
}

//Copy Constructor
HashTable::HashTable(const HashTable & otherhash)
{
    tablesize = otherhash.tablesize;
    curritem = otherhash.curritem;
    table = new LinkedList[tablesize];
    for (int i=0;i<tablesize;i++)
    {
        table[i] = otherhash.table[i];
    }
};

//Destructor
HashTable::~HashTable()
{
    delete [] table;
}

//Operator
HashTable &HashTable::operator=(const HashTable & otherhash)
{
    if( &otherhash != this)
    {
        delete [] table;
        tablesize = otherhash.tablesize;
        curritem = otherhash.curritem;
        table = new LinkedList[tablesize];
        for(int i=0; i<otherhash.tablesize;i++)
        {
            table[i]=otherhash.table[i];
        }
    }
    return *this;
}

//insert
bool HashTable::insert(string toinsert)
{
    int index = hashfunc(toinsert);
    bool success = table[index].insert(toinsert);
    if(success)
    {
        curritem ++;
        return true;
    }
    return false;
}

//remove
bool HashTable::remove(string toremove)
{
    int index = hashfunc(toremove);
    bool success = table[index].remove(toremove);
    if(success)
    {
        curritem--;
        return true;
    }
    return false;
}

//search
bool HashTable::search(string tosearch) const
{
    int index = hashfunc(tosearch);
    return table[index].search(tosearch);
}

//size
int HashTable::size() const
{
    return curritem;
}

//hashfunction
int HashTable::hashfunc(string toinsert) const
{
    int ascii=0;
    int total=0;
    int deduct=1;
    unsigned long wordlength = toinsert.size();
    for(int i=0; i<wordlength;i++)
    {
        ascii = toinsert[i] - 96;
        total = total + (ascii * (pow(32.0,wordlength-deduct)));
        total = (total % tablesize);
        deduct++;
    }
    return total;
}

//maxsize
int HashTable::maxSize() const
{
    return tablesize;
}

//loadfactor
float HashTable::loadFactor() const
{
    return curritem/tablesize;
}

//intersection
vector<string> HashTable::intersection(const HashTable & otherhash) const
{
    vector<string> intersection_store;
    vector<string> temp;
    for(int i=0; i<tablesize;i++)
    {
        temp = table[i].get();
        for(int j=0;j<temp.size();j++)
        {
                if(otherhash.search(temp[j]))
                {
                    intersection_store.push_back(temp[j]);
                }
        }
    }
    return intersection_store;
}

//setunion
vector<string> HashTable::setunion(const HashTable &otherhash) const
{
    vector<string> setunion_store;
    vector<string> temp;
    for(int i = 0; i < otherhash.tablesize; i++)
    {
        temp = otherhash.table[i].get();
        for(int j = 0; j < temp.size(); j++)
        {
            setunion_store.push_back(temp[j]);
        }
    }
    for(int i = 0; i < tablesize; i++)
    {
        temp = table[i].get();
        for(int j = 0; j < temp.size(); j++)
        {
            if(! otherhash.search(temp[j]) )
            {
                setunion_store.push_back(temp[j]);
            }
        }
    }
    return setunion_store;
}

//difference
vector<string> HashTable::difference(const HashTable &otherhash) const
{
    vector<string> difference_store;
    vector<string> temp;
    for(int i = 0; i < tablesize; i++)
    {
        temp = table[i].get();
        for(int j = 0; j < temp.size(); j++)
        {
            if(! otherhash.search(temp[j]) )
            {
                difference_store.push_back(temp[j]);
            }
        }
    }
    return difference_store;
}










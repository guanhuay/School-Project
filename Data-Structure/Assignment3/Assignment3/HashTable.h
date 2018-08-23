//
//  HashTable.h
//  Assignment5
//
//  Created by Guanhua Yang on 2015-11-21.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#ifndef __Assignment5__HashTable__
#define __Assignment5__HashTable__

#include <string>
#include <vector>
#include <iostream>
#include "LinkedList.h"
using std::vector;
using std::string;

class HashTable
{
    public:
    
    //Default Constructor
    HashTable();
    
    //Constructor take single int argument
    HashTable(int);
    
    //Copy Constructor
    HashTable(const HashTable &);
    
    //Destructor
    ~HashTable();
    
    //Operator
    HashTable & operator = (const HashTable & );
    
    //insert
    bool insert(string);
    
    //remove
    bool remove(string);
    
    //search
    bool search(string) const;
    
    //size
    int size() const;
    
    //maxsize
    int maxSize() const;
    
    //loadFactor
    float loadFactor() const;
    
    //intersection
    vector<string> intersection(const HashTable &otherhash) const;
    
    //setunion
    vector<string> setunion(const HashTable &) const;
    
    //difference
    vector<string> difference(const HashTable &otherhash) const;
    
    private:
    int tablesize;
    int curritem;
    LinkedList * table;
    //check whether the number n is prime or not
    bool is_prime(int n) const
    {
        if(n==1 || n==0)
        {
            return false;
        }
        for(int i=2; i*i<= n; i++)
        {
            if((n%i)==0)
            {
                return false;
            }
        }
        return true;
    }
    int hashfunc(string) const;
};

#endif /* defined(__Assignment5__HashTable__) */

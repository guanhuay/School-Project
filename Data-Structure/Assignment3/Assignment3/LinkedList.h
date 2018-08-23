//
//  LinkedList.h
//  Assignment5
//
//  Created by Guanhua Yang on 2015-11-21.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#ifndef __Assignment5__LinkedList__
#define __Assignment5__LinkedList__

#include <stdio.h>
#include <iostream>
#include <string>
#include <vector>
using std::vector;
using std::string;

class Node
{
    public:
    string data;
    Node * next;
    //constructor
    Node(string value, Node * nde):data(value),next(nde){};
};

class LinkedList
{
    public:
    
    //Default Constructor
    LinkedList();
    
    //Copy Constructor
    LinkedList(const LinkedList &);
    
    //Destructor
    ~LinkedList();
    
    //operator
    LinkedList& operator=(const LinkedList&);
    
    //insert
    bool insert(string);
    
    //remove
    bool remove(string);
    
    //search
    bool search(string) const;
    
    //get
    vector<string> get() const;
    
    private:
        Node * head;
        int linksize;
        //used for copy constructor & operator = 
        void copylink (const LinkedList &);
        //used for destructor & operator =
        void removelink();
};
#endif /* defined(__Assignment5__LinkedList__) */

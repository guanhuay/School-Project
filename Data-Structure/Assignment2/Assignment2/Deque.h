//
//  Deque.h
//  Assignment2
//
//  Created by Guanhua Yang on 2015-09-28.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#include <stdexcept>

class Node
{
public:
    int data;
    Node * next;
};


class Deque
{
public:
    //default constructor
    Deque();
    
    //copy construtor
    Deque(const Deque & otherque);
    
    //destructor
    ~Deque();
    
    //copy the current deque into the target deque
    Deque & operator=(const Deque& otherque);
    
    //insert front
    void insert_front(int);
    
    //insert back
    void insert_back(int);
    
    //remove front
    int remove_front();
    
    //remove back
    int remove_back();
    
    //return the value at the front of deque
    int peek_front() const;
    
    //return the value at the end of deque
    int peek_back() const;
    
    //check whether the deque is empty or not
    bool empty() const;
    
    //check the size of deque
    int size() const;
    
private:
    Node * front;
    Node * back;
    int currsize; //size of the quene, how many element in there.
};

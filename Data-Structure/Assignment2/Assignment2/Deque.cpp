//
//  Deque.cpp
//  Assignment2
//
//  Created by Guanhua Yang on 2015-09-28.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#include "Deque.h"

//default constructor
Deque::Deque():front(NULL),back(NULL),currsize(0){}

//copy contructor
Deque::Deque(const Deque & otherque)
{
    //base case where otherque is NULL
    if (otherque.empty())
    {
        front=NULL;
        back=NULL;
        return;
    }
    //case when otherque contain multiple value
    Node * curr = new Node();
    Node * temp = otherque.front;
    front = curr;
    while (temp->next != NULL)
    {
        curr->data=temp->data;
        Node * currx =new Node();
        curr->next=currx;
        currsize++;
        curr=curr->next;
        temp=temp->next;
    }
    curr->data = temp->data;
    currsize++;
    back=curr;
}

//destructor
Deque::~Deque()
{
    if (front == NULL) return;
    Node * cur = new Node();
    front = cur;
    while (front->next != NULL) {
        cur = front->next;
        delete front;
        front = cur;
    }
    delete front;
    front = NULL;
}

//copy the current deque into the target deque
Deque & Deque::operator=(const Deque & target)
{
    if(!empty())
    {
        front=NULL;
        back=NULL;
        currsize=0;
        if(target.empty())
        {
            return *this;
        }
    }
    Node * curr = new Node();
    Node * temp = target.front;
    front = curr;
    while(temp->next != NULL)
    {
        curr->data=temp->data;
        Node * currx =new Node();
        curr->next=currx;
        currsize++;
        curr=curr->next;
        temp=temp->next;
    }
    curr->data = temp->data;
    currsize++;
    back=curr;
    return *this;
}

//insert front of deque
void Deque::insert_front(int val)
{
    Node * insert = new Node();
    insert->data = val;
    insert->next = NULL;
    if(empty())
    {
        front=back=insert;
    }
    else
    {
        insert->next = front;
        front = insert;
    }
    currsize++;
}

//insert back of deque
void Deque::insert_back(int val)
{
    Node * insert = new Node();
    insert->data = val;
    insert->next = NULL;
    if(empty())
    {
        front=insert;
    }
    else
    {
        back->next = insert;
        back=insert;
    }
    currsize++;
}

//remove the front of deque
int Deque::remove_front()
{
    if(empty())
    {
        throw std::runtime_error("The deque is empty");
    }
    int result=front->data;
    Node * temp = new Node();
    temp = front;
    if(front->next!=NULL)
    {
        front=front->next;
    }
    else
    {
        front=NULL;
        back=NULL;
    }
    currsize--;
    delete temp;
    return result;
}

//remove the end of deque
int Deque::remove_back()
{
    //if deque is empty
    if(empty())
    {
        throw std::runtime_error("The deque is empty");
    }
    int result = back->data;
    Node * temp = new Node();
    temp = front;
    if (front->next != NULL)
    {
        while(temp->next->next != NULL)
        {
            temp=temp->next;
        }
        back= temp->next;
        back->next= NULL;
    }
    else
    {
        back=NULL;
        front=NULL;
    }
    currsize--;
    delete temp;
    return result;
}

//return the front value of deque
int Deque::peek_front() const
{
    //if deque is empty
    if(empty())
    {
        throw std::runtime_error("The deque is empty");
    }
    //if deque is not empty
    return front->data;
}

//return the back value of deque
int Deque::peek_back() const
{
    //if deque is empty
    if(empty())
    {
        throw std::runtime_error("The deque is empty");
    }
    //if deque contain multiple value
    return back->data;
}

//check whether the deque is empty
bool Deque::empty() const
{
    if(size()==0)
    {
        return true;
    }
    return false;
}

//check the size of deque;
int Deque::size() const
{
    return currsize;
}

//
//  LinkedList.cpp
//  Assignment5
//
//  Created by Guanhua Yang on 2015-11-21.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#include "LinkedList.h"
#include <iostream>
#include <vector>
#include <string>

//Default Constructor
LinkedList::LinkedList():head(NULL),linksize(0){};

//Copy Constructor
LinkedList::LinkedList(const LinkedList & tocopy)
{
    copylink(tocopy);
}

//Destructor
LinkedList::~LinkedList()
{
    removelink();
}

//operator
LinkedList &LinkedList::operator= (const LinkedList &tocopy)
{
    if(this != &tocopy)
    {
        removelink();
        copylink(tocopy);
    }
    return *this;
}

//copylink
void LinkedList::copylink(const LinkedList &tocopy)
{
    if(tocopy.head == NULL)
    {
        head = NULL;
        linksize = 0;
    }
    else
    {
        linksize = tocopy.linksize;
        Node* copynode = new Node(tocopy.head->data, NULL);
        head = copynode;
        Node* ptr = tocopy.head;
        ptr = ptr->next;
        while(ptr != NULL)
        {
            copynode->next = new Node(ptr->data, NULL);
            copynode = copynode->next;
            ptr = ptr->next;
        }
    }
}

//remove
void LinkedList::removelink()
{
    Node* temp = head;
    while(temp != NULL)
    {
        temp = head->next;
        delete head;
        head = temp;
    }
    linksize = 0;
}

//insert
bool LinkedList::insert(string toinsert)
{
    if(search(toinsert))
    {
        return false;
    }
    else
    {
        Node* newnode = new Node (toinsert, NULL);
        
        if(head == NULL)
        {
            head = newnode;
        }
        else
        {
            newnode->next = head;
            head = newnode;
        }
        linksize++;
        return true;
    }
}

//remove
bool LinkedList::remove(string toremove)
{
    if(!search(toremove))
    {
        return false;
    }
    else
    {
        Node* nodeptr = head;
        Node* temp = nodeptr->next;
        
        if(head->data == toremove)
        {
            head = temp;
            delete nodeptr;
            linksize--;
            return true;
        }
        else
        {
            while(temp != NULL)
            {
                if(temp->data == toremove)
                {
                    nodeptr->next = temp->next;
                    delete temp;
                    linksize--;
                    return true;
                    
                }
                nodeptr = nodeptr->next;
                temp = temp->next;
            }
        }
    }
    return false;
}

//search
bool LinkedList::search(string tosearch) const
{
    Node* temp = head;
    
    while(temp != NULL)
    {
        if(temp->data == tosearch)
        {
            return true;
        }
        temp = temp->next;
        
    }
    return false;
}

//get
vector<string> LinkedList::get() const
{
    vector<string> tempvec;
    if(head != NULL)
    {
        Node* temp = head;
        while(temp != NULL)
        {
            tempvec.push_back(temp->data);
            temp = temp->next;
        }
    }
    return tempvec;
}

















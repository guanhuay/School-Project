//
//  MyStack.h
//  MyStack
//
//  Created by Guanhua Yang on 2015-10-08.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#ifndef MY_STACK_HEADER
#define MY_STACK_HEADER
template <typename T>
class MyStack
{
public:
    //Default constructor
    //PRE:
    //POST: created empty stack of size 10
    MyStack();
    
    //Constructor(int)
    //PRE:
    //PARAM: n - size of stack to be created
    //POST: created empty stack of size n
    MyStack(int n);
    
    //Destructor
    ~MyStack();
    
    //Insert
    //PRE: stack is not full
    //PARAM: x - value to be inserted
    //POST: x pushed on the stack top
    void push(T x);
    
    //Remove
    //PRE: stack is not empty
    //POST: value at the stack top removed and returned
    T pop();
    
private:
    int size;
    int top;
    T* arr;
};


#include <stdexcept>
#include "MyStack.h"

template <typename T>
MyStack<T>::MyStack() : size{10}, top{0}, arr{new T[size]} {}

template <typename T>
MyStack<T>::MyStack(int n) : size{n}, top{0}, arr{new T[size]} {}

template <typename T>
MyStack<T>::~MyStack()
{
    delete [] arr;
}

template <typename T>
void MyStack<T>::push(T x)
{
    if (top == size) {
        throw std::runtime_error("stack is full");
    }
    arr[top++] = x;
}

template <typename T>
T MyStack<T>::pop()
{
    if (top == 0) {
        throw std::runtime_error("stack is empty");
    }
    return arr[--top];
}

#endif
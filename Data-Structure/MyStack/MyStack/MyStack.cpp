//
//  MyStack.cpp
//  MyStack
//
//  Created by Guanhua Yang on 2015-10-08.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

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
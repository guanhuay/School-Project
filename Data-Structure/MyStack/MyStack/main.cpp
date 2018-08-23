//
//  main.cpp
//  MyStack
//
//  Created by Guanhua Yang on 2015-10-08.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//
#include <iostream>
#include <string> // Used when we test the template version
#include "MyStack.h"

using std::cout;
using std::endl;
using std::string; // Used when we test the template version

void stackTest();

int main()
{
    stackTest();
}

void stackTest()
{
    MyStack<int> intSt{};
    
    intSt.push(3);
    intSt.push(2);
    intSt.push(1);
    
    cout << intSt.pop() << " -- ";
    cout << intSt.pop() << " -- ";
    cout << intSt.pop() << endl << endl;
    
    MyStack<string> strSt{};
    
    strSt.push("odin");
    strSt.push("freya");
    
    cout << strSt.pop() << endl;
    cout << strSt.pop() << endl << endl;
}

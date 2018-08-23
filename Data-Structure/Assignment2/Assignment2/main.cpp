//
//  main.cpp
//  Assignment2
//
//  Created by Guanhua Yang on 2015-09-28.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#include <iostream>
#include "Deque.h"
using std::cout;
using std::endl;

int main()
{
    Deque dq1;
    cout << dq1.empty() << " - 1" << endl;
    
    dq1.insert_front(42);
    dq1.insert_back(216);
    dq1.insert_front(35);
    dq1.insert_back(200);
    dq1.insert_back(100);
    
    cout << dq1.peek_front() << " - 35" << endl;
    cout << dq1.peek_back() << " - 100" << endl;
    cout << dq1.size() << " - 5" << endl;
    Deque dq4;
    Deque dq2(dq4);
    Deque dq3;
    dq3 = dq1;
    
    cout << dq1.remove_front() << " - 35" << endl;
    cout << dq1.remove_back() << " - 100" << endl;
    cout << dq1.size() << " - 3" << endl;
    
    cout << dq3.peek_front() << " - 35" << endl;
    cout << dq3.peek_back() << " - 100" << endl;
    
    cout << dq2.size() << " - 0" << endl;
    cout << dq2.peek_front() << " - 35" << endl;
    cout << dq2.peek_back() << " - 100" << endl;
    
    
    return 0;
}
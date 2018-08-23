//
//  main.cpp
//  Assignment5
//
//  Created by Guanhua Yang on 2015-11-21.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#include <iostream>
#include <string>
#include <vector>
#include <iostream>
#include "HashTable.h"

using std::string;
using std::vector;
using std::cout;
using std::endl;

void simpleTest();

int main()
{
    simpleTest();
    return 0;
}

void simpleTest()
{
    HashTable ht1 {9};
    ht1.insert("bat");
    ht1.insert("cat");
    ht1.insert("rhinoceros");
    ht1.insert("ocelot");
    ht1.insert("elephant");
    ht1.insert("hippopotamus");
    ht1.insert("giraffe");
    ht1.insert("camel");
    ht1.insert("lion");
    ht1.insert("panther");
    ht1.insert("bear");
    ht1.insert("wolf");
    
    // Test search
    cout << "search" << endl;
    string test1 = "frog";
    string test2 = "camel";
    cout << test1 << ": " << ht1.search(test1) << endl;
    cout << test2 << ": " << ht1.search(test2) << endl;
    
    // Test copy constructor and remove
    HashTable ht2 {ht1};
    ht2.remove("ocelot");
    ht2.remove("camel");
    ht2.remove("rhinoceros");
    
    // Test set difference
    cout << endl << "set difference" << endl;
    vector<string> difference = ht1.difference(ht2);
    for (auto s : difference) {
        cout << s << endl;
    }
}
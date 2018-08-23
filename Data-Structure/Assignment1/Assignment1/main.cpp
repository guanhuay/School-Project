
//
//  main.cpp
//  Assignment1
//
//  Created by Guanhua Yang on 2015-09-21.
//  Copyright (c) 2015 Guanhua Yang. All rights reserved.
//

#include <iostream>
#include "StringSet.h"
using std::cout;
using std::endl;

void PrintSet(StringSet a) {
    for (int i = 0; i < a.size(); ++i) cout << a.get(i) << " ";
    cout<<endl;
}

int main()
{
    //stringset a={a,b,g,d}
    StringSet a = StringSet();
    a.insert("5");
    a.insert("9");
    a.insert("4");
    a.insert("1");
    a.insert("20");
    
    cout<<"a: ";
    PrintSet(a);
    
    StringSet b = StringSet(a);
    //when a exist
    b.remove("1"); // “b”
    //when s not exist
    b.remove("0");
    //when a exist
    b.find("1");
    //when s not exist
    b.find("s");
    
    cout<<"b: ";
    PrintSet(b);
    
    //stringset d={f,g,s}
    StringSet d = StringSet();
    d.insert("4");
    d.insert("9");
    d.insert("0");
    d.insert("2");
    d.insert("10");
    d.insert("11");
    d.insert("13");
    d.insert("15");
    d.insert("16");
    d.insert("14");
    d.insert("19");
    
    cout<<"d: ";
    PrintSet(d);
    
    StringSet e = a.setunion(d);
    cout<<"e: ";
    PrintSet(e);
    
    StringSet c = a.intersection(d);
    cout<<"c: ";
    PrintSet(c);
    
    StringSet f = a.difference(d);
    cout<<"f: ";
    cout<<f.size()<<endl;
    cout<<"f: ";
    PrintSet(f);
    
}

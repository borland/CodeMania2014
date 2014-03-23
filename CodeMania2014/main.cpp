//
//  main.cpp
//  CodeMania2014
//
//  Created by Orion Edwards on 12/01/14.
//  Copyright (c) 2014 Orion Edwards. All rights reserved.
//

#include <iostream>
#include <functional>
#include <cassert>
#include <string>
#include <sstream>

#include "LinkedList.h"
//#include "non-type-templates.h"
#include "safeprintf.h"

using namespace std;

struct Nameable {
    virtual string getName() const = 0;
    virtual void setName(string name) = 0;
};

struct PersonZ : public Nameable {
    string m_name;
    
    string getName() const override {
        return m_name;
    }
    
    void setName(string name) override {
        m_name = name;
    }
};

struct Person {
    wstring _name;
};

template<>
wstring toString(Person x) {
    std::wstringstream s;
    s << L"<Person:" << x._name << L">";
    return s.str();
}

template<typename T>
T add(T a, T b, T c, T d) {
    return a + b + c + d;
}


int mymain(int argc, const char * argv[])
{
    
    safeprintf("%@\n", add(1, 2,3 ,4));
    safeprintf("%@\n", add(1.7, 2.3, 3.6, 4.8));
    safeprintf("%@\n", add<string>("cat", "dog", "horse", "fish"));

    return 0;
}


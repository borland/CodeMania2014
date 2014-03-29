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

template<typename _Char>
struct StringConverter<Person, _Char> {
    static basic_string<_Char> toString(Person p) {
        std::basic_stringstream<_Char> s;
        s << L"<Person:" << p._name << L">";
        return s.str();
    }
};

// partial spec for pointers

template<typename T, typename _Char>
struct StringConverter<T*, _Char> {
    static basic_string<_Char> toString(T* p) {
        return StringConverter<T, _Char>::toString(*p);
    }
};

template<typename T>
struct Wrapper {
    T* value;
};

// partial spec for wrappers
//template<typename T, typename _Char>
//struct StringConverter<Wrapper<T>, _Char> {
//    static basic_string<_Char> toString(Wrapper<T> p) {
//        return StringConverter<T, _Char>::toString(*(p.value));
//    }
//};

template <typename T>
T add (T a, T b) {
    return a + b;
}

int main(int argc, char** argv) {
    int x = add<std::string>("hello", 2.2);
    
    
//    safeprintf("%@\n", );
//    safeprintf("%@\n", add(1.7, 2.3, 3.6, 4.8));
//    safeprintf("%@\n", add<string>("cat", "dog", L"horse", "fish"));
}


//    Person p { L"Orion" };
//    
//    Person* j = new Person { L"Orion" };
//    
//    Wrapper<Person> w { &p };
//    
//    safeprintf(L"%@\n", p );
//    safeprintf(L"%@\n", j);
//    safeprintf(L"%@\n", w);



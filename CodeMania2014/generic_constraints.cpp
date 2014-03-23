//
//  generic_constraints.cpp
//  CodeMania2014
//
//  Created by Orion Edwards on 23/03/14.
//  Copyright (c) 2014 Orion Edwards. All rights reserved.
//

#include <vector>

using namespace std;

// ---------------------------------------------

#pragma clang diagnostic push
#pragma clang diagnostic ignored "-Wunused-variable"

template<class T, class B> struct Derived_from {
    typedef void(*constraint)(T*);
    const constraint c = [](T* p) { B* pb = p; };
};

#pragma clang diagnostic pop

struct B { };
struct D : B { };
struct DD : D { };
struct X { };

struct Mybase {
    
};

// the classical "elements must derived from Mybase*" constraint:
template<class T> class Container : Derived_from<T, Mybase> {
    // ...
};

struct MyDerived : Mybase {
    
};

int main()
{
    Derived_from<D,B>();
    Derived_from<DD,B>();
    //    Derived_from<X,B>();
    //    Derived_from<int,B>();
    //    Derived_from<X,int>();
    
    Container<Mybase> c1;
//    Container<string> c2;
    Container<MyDerived> c3;
}
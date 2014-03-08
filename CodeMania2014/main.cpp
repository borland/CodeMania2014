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

template<typename T>
struct LinkedList {
    struct ListNode {
        T item;
        ListNode* next;
        
        ListNode(T item, ListNode* next = nullptr)
            : item(item)
            , next(next)
        { }
        
        ~ListNode() {
            if(next) {
                delete next;
            }
        }
    };
    
    ListNode* head;
    ListNode* tail;
    
    LinkedList()
    : head(nullptr), tail(nullptr)
    { }
    
    ~LinkedList() {
        if(head) {
            delete head; // deletes the whole list
        }
    }
    
    void push(T item) {
        auto node = new ListNode(item);
        if(tail){
            tail->next = node;
        }
        tail = node;
        if(!head) {
            head = node;
        }
    }
    
    T pop() {
        if(head) {
            T ret = head->item;
            ListNode* oldhead = head;
            swap(head->next, head);
            
            oldhead->next = nullptr;
            delete oldhead;
            return ret;
        } else {
            return T();
        }
    }
    
    template<typename TCallback>
    void iterate(TCallback cb) {
        for(auto n = head; n; n = n->next) {
            if(n)
                cb(n->item);
        }
    }
};

template<typename T>
wstring toString(T x) {
    std::wstringstream s;
    s << x;
    return s.str();
}

template<typename T>
wstring safesprintf(const wstring &format, T obj) {
    wstring output { format };
    size_t pos = output.find(L"%@");
    assert(pos != wstring::npos); // not enough %@ in our string
    
    output.replace(pos, 2, toString(obj));
    return output;
}

template<typename T, typename... Args>
wstring safesprintf(const wstring &format, T obj, Args... rest) {
    wstring output { format };
    size_t pos = output.find(L"%@");
    assert(pos >= 0);
    
    output.replace(pos, 2, toString(obj));
    return safesprintf(output, rest...);
}

struct Person {
    wstring _name;
};

template<>
wstring toString(Person x) {
    std::wstringstream s;
    s << L"<Person:" << x._name << L">";
    return s.str();
}

int main(int argc, const char * argv[])
{
//    LinkedList<int> list;
//    list.push(1);
//    list.push(2);
//    list.push(3);
//    
//    list.pop();
//    
//    list.iterate([](int x){
//        cout << x << endl;
//    });
    
    Person p { L"Orion" };
    
    wcout << safesprintf(L"foo %@\n", L"bar");
    
    wcout << safesprintf(L"We have %@ dogs and %@ cats for a total price of %@ dollars, and an owner of %@\n",
            5, 3, 7.5, p);
    
}


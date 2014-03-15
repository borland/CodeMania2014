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
#include "diff.h"

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

template<typename _Char, typename T>
basic_string<_Char> toString(T x) {
    basic_stringstream<_Char> s;
    s << x;
    return s.str();
}

template<typename T>
wstring toString(const wstring& x) {
    wstringstream s;
    s << x;
    return s.str();
}

template <typename CharType>
struct PrintfHelper;

template <>
struct PrintfHelper<char> {
    static size_t print(const string& s) {
        cout << s;
        return s.length();
    }
    
    static const char* sep;
};

template <>
struct PrintfHelper<wchar_t> {
    static size_t print(const wstring& s) {
        wcout << s;
        return s.length();
    }
    static const wchar_t* sep;
};

const char* PrintfHelper<char>::sep = "%@";
const wchar_t* PrintfHelper<wchar_t>::sep = L"%@";

template<typename _Char, typename T>
basic_string<_Char> safesprintf(basic_string<_Char> format, T obj) {
    size_t pos = format.find(PrintfHelper<_Char>::sep);
    assert(pos != basic_string<_Char>::npos); // not enough %@ in our string
    
    string s = toString<_Char, T>(obj);
    format.replace(pos, 2, s);
    return format;
}

template<typename _Char, typename T, typename... Args>
wstring safesprintf(basic_string<_Char> format, T obj, Args... rest) {
    size_t pos = format.find(PrintfHelper<_Char>::sep);
    assert(pos != basic_string<_Char>::npos); // not enough %@ in our string
    
    format.replace(pos, 2, toString(obj));
    return safesprintf(format, rest...);
}

template<typename _Char, typename... Args>
size_t safeprintf(const basic_string<_Char>& format, Args... rest) {
    return PrintfHelper<_Char>::print(safesprintf(format, rest...));
}

template<typename _Char, typename... Args>
size_t safeprintf(const _Char * format, Args... rest) {
    return PrintfHelper<_Char>::print(
                                      safesprintf(basic_string<_Char>(format), rest...));
}

template<typename _Char>
size_t safeprintf(const basic_string<_Char>& format) {
    return PrintfHelper<_Char>::print(format);
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

template<typename T>
T add(T a, T b, T c, T d) {
    return a + b + c + d;
}


int main(int argc, const char * argv[])
{
    safeprintf("%@\n", add(1, 2,3 ,4));
    safeprintf("%@\n", add(1.7, 2.3, 3.6, 4.8));
    
    safeprintf("%@\n", add<string>("cat", "dog", "horse", "fish"));
}


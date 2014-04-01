#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

template<typename T, typename Hack = true_type>
struct StringConverter {
    static string convert(T item) {
        ostringstream o; o << item; return o.str();
    }
};

template<typename T>
struct StringConverter<vector<T>> {
    static string convert(vector<T> items) {
        string ret = "";
        for(T& x : items) {
            if(ret.length())
                ret += ",";
            ret += StringConverter<T>::convert(x);
        }
        return ret;
    }
};

template<typename T>
string safe_sprintf(string format, T arg) {
    size_t pos = format.find("%@", 0);
    assert(pos != string::npos);
    
    format.replace(pos, 2, StringConverter<T>::convert(arg));
    return format;
};

template<typename T, typename... TRemaining>
string safe_sprintf(string format, T arg, TRemaining... remaining) {
    size_t pos = format.find("%@", 0);
    assert(pos != string::npos);
    
    format.replace(pos, 2, StringConverter<T>::convert(arg));
    return safe_sprintf(format, remaining...);
};

template <typename... TRemaining>
void safe_printf(string format, TRemaining... args) {
    string s = safe_sprintf(format, args...);
    cout << s << endl;
}

struct Person {
    string name;
    
    string toString() { return string{"p:"} + name; }
};

template<class T>
struct has_toString {
    template<class PtrType, PtrType> struct eq { };
    
    template<class X> static true_type f(eq<string(X::*)(), &X::toString>*);
    template<class X> static false_type f(...);
    
    //    static const bool value = decltype(f<T>(nullptr))::value;
    typedef decltype(f<T>(nullptr)) type;
};

template<typename T>
struct StringConverter<T, typename has_toString<T>::type> {
    static string convert(T item) { return item.toString(); }
};

int main(int argc, const char * argv[])
{
    Person orion{ "orion" };
    safe_printf("%@ %@", orion, 3);
    //    safe_printf("%@ %@ - have %@ nice days", "hello", orion, 3);
}

#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <vector>
#include <iostream>

using namespace std;

template<typename T>
struct StringConverter {
    static string convert(T item) {
        ostringstream o;
        o << item;
        return o.str();
    }
};

template<typename T>
struct StringConverter<vector<T>> {
    static string convert(vector<T> items) {
        string output { "" };
        for(T& item : items) {
            if(output.length())
                output.append(",");
            
            output.append(StringConverter<T>::convert(item));
        }
        return output;
    }
};

template<typename T>
string safe_sprintf(string format, T arg) {
    size_t pos = format.find("%@", 0);
    assert(pos != string::npos);
    
    format.replace(pos, 2, StringConverter<T>::convert(arg));
    return format;
};

template <typename T, typename... TRemaining>
string safe_sprintf(string format, T arg, TRemaining... remaining) {
    size_t pos = format.find("%@", 0);
    assert(pos != string::npos);
    
    format.replace(pos, 2, StringConverter<T>::convert(arg));
    return safe_sprintf(format, remaining...);
}

template <typename... TRemaining>
void safe_printf(string format, TRemaining... remaining) {
    string s = safe_sprintf(format, remaining...);
    cout << s;
}

#pragma mark - Start Here

template <typename T>
class has_toString
{
private:
    template <typename U, U> class typesEqual { };
    
    template <typename C> static true_type f(typesEqual<string (C::*)(void), &C::toString>*);
    
    template <typename> static false_type f(...);
    
public:
    static const bool value = decltype(f<T>(nullptr))::value;
};


struct Person {
    string name;
    
    string toString() {
        return name;
    }
};

int main(int argc, const char * argv[])
{
    safe_printf("int has_toString? %@, person has_toString? %@\n", has_toString<int>::value, has_toString<Person>::value);
    return 0;
}


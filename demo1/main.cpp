#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>

using namespace std;

template <typename T>
struct StringConverter {
    static string toString(T item) {
        ostringstream s;
        s << item;
        return s.str();
    }
};

template <typename T>
struct StringConverter<T*> {
    static string toString(T* item) {
        ostringstream s;
        s << *item;
        return s.str();
    }
};

template<typename T>
string safe_sprintf(string format, T arg) {
    size_t pos = format.find("%@", 0);
    assert(pos != string::npos);
    
    string argString = StringConverter<T>::toString(arg);
    
    format.replace(pos, 2, argString);
    return format;
};

int main(int argc, const char * argv[])
{
    int a = 7;
    string targ = safe_sprintf("hello %@, have a nice day!", "joe");
    
    printf("%s\n", targ.c_str());
}


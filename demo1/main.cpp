#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>

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
string safe_sprintf(string format, T arg) {
    size_t pos = format.find("%@", 0);
    assert(pos != string::npos);
    
    format.replace(pos, 2, StringConverter<T>::convert(arg));
    return format;
};

template <typename T, typename Other...>
string safe_sprintf(string format, T... args) {
    <#statements#>
}

int main(int argc, const char * argv[])
{
    string targ = safe_sprintf("hello %@, have %@ nice days", "joe", 99);
    
    printf("%s\n", targ.c_str());
}



















template <typename T>
struct _StringConverter {
    static string toString(T item) {
        ostringstream s;
        s << item;
        return s.str();
    }
};

template <typename T>
struct _StringConverter<T*> {
    static string toString(T* item) {
        ostringstream s;
        s << *item;
        return s.str();
    }
};

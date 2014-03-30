#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>

using namespace std;

string safe_sprintf(string format, string arg) {
    size_t pos = format.find("%@", 0);
    assert(pos != string::npos);
    
    format.replace(pos, 2, arg);
    return format;
};

int main(int argc, const char * argv[])
{
    string targ = safe_sprintf("hello %@, have a nice day!", "joe");
    
    printf("%s\n", targ.c_str());
}



















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

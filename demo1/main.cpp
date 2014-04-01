#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

template<typename T>
struct StringConverter {
    static string convert(T item) {
        ostringstream o; o << item; return o.str();
    }
};

template<typename T>
string safe_sprintf(string format, T arg) {
    size_t pos = format.find("%@", 0);
    assert(pos != string::npos);
    
    format.replace(pos, 2, StringConverter<T>::convert(arg));
    return format;
};

int main(int argc, const char * argv[])
{
    string orion { "orion" };
    string targ = safe_sprintf("hello %@ - have a nice day!", orion);
    
    printf("%s\n", targ.c_str());
}

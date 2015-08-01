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

int main(int argc, const char * argv[])
{
    vector<string> people { "orion", "ian" };
    string targ = safe_sprintf("%@ %@ - have %@ nice days", "goodbye", people, 2);
    
    printf("%s\n", targ.c_str());
}

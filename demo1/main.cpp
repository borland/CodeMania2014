#include <string>
#include <sstream>
#include <algorithm>
#include <cassert>
#include <vector>

using namespace std;

string safe_sprintf(string format, string arg) {
    size_t pos = format.find("%@", 0);
    assert(pos != string::npos);
    
    format.replace(pos, 2, arg);
    return format;
};

int main(int argc, const char * argv[])
{
    string person { "orion" };
    string targ = safe_sprintf("hello %@ - have a nice day!", person);
    
    printf("%s\n", targ.c_str());
}

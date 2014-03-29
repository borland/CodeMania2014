#include <string>
#include <algorithm>

using namespace std;

string safe_sprintf(string format, const string& arg1) {
    size_t pos = 0;
    while((pos = format.find("%@", pos)) != string::npos) {

        format.replace(pos, 2, arg1);
        pos += arg1.length();
    }
    return format;
};

int main(int argc, const char * argv[])
{
    string targ = safe_sprintf("hello %@, have a %@ day!", "orion");
    
    printf("%s\n", targ.c_str());
}


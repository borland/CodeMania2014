#pragma once

#include <string>

// base template; cheat by using stringstream
template<typename T, typename _Char>
struct StringConverter {
    static std::basic_string<_Char> toString(T x) {
        std::basic_stringstream<_Char> s;
        s << x;
        return s.str();
    }
};

template<typename _Char>
struct StringConverter<char*, _Char> {
    static std::basic_string<_Char> toString(char* x) {
        return x;
    }
};

template <typename CharType>
struct PrintfHelper;

template <>
struct PrintfHelper<char> {
    static size_t print(const std::string& s) {
        std::cout << s;
        return s.length();
    }
    
    static const char* sep;
};

template <>
struct PrintfHelper<wchar_t> {
    static size_t print(const std::wstring& s) {
        std::wcout << s;
        return s.length();
    }
    static const wchar_t* sep;
};

const char* PrintfHelper<char>::sep = "%@";
const wchar_t* PrintfHelper<wchar_t>::sep = L"%@";

template<typename _Char, typename T>
std::basic_string<_Char> safesprintf(std::basic_string<_Char> format, T obj) {
    auto pos = format.find(PrintfHelper<_Char>::sep);
    assert(pos != std::basic_string<_Char>::npos); // not enough %@ in our string
    
    auto s = StringConverter<T, _Char>::toString(obj);
    format.replace(pos, 2, s);
    return format;
}

template<typename _Char, typename T, typename... Args>
std::basic_string<_Char> safesprintf(std::basic_string<_Char> format, T obj, Args... rest) {
    auto pos = format.find(PrintfHelper<_Char>::sep);
    assert(pos != std::basic_string<_Char>::npos); // not enough %@ in our string
    
    format.replace(pos, 2, StringConverter<T, _Char>::toString(obj));
    return safesprintf(format, rest...);
}

template<typename _Char, typename... Args>
size_t safeprintf(const std::basic_string<_Char>& format, Args... rest) {
    return PrintfHelper<_Char>::print(safesprintf(format, rest...));
}

template<typename _Char, typename... Args>
size_t safeprintf(const _Char * format, Args... rest) {
    return PrintfHelper<_Char>::print(
                                      safesprintf(std::basic_string<_Char>(format), rest...));
}

template<typename _Char>
size_t safeprintf(const std::basic_string<_Char>& format) {
    return PrintfHelper<_Char>::print(format);
}


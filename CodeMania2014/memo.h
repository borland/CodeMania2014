#pragma once

#include <iostream>
#include <functional>
#include <memory>

template<typename T>
class memo {
public:
    typedef std::function<T*(void)> Generator;
    
    memo(Generator generator)
    : _generator(generator),
    _value(nullptr) { }
    
    const T& operator ()() {
        if(!_value) {
            _value.reset(_generator());
        }
        return *_value;
    }
    
private:
    std::unique_ptr<T> _value;
    const Generator _generator;
};

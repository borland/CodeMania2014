//
//  diff.h
//  CodeMania2014
//
//  Created by Orion Edwards on 15/03/14.
//  Copyright (c) 2014 Orion Edwards. All rights reserved.
//

#ifndef __CodeMania2014__diff__
#define __CodeMania2014__diff__

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

#endif /* defined(__CodeMania2014__diff__) */

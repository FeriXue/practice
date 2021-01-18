#include <iostream>

struct absInt {
    int operator()(int val) const {
        return val > 0 ? val : -val;
    }
} ;


//
// Created by osboxes on 6/9/20.
//

#ifndef ITERTOOLS_CFAR_A_RANGE_HPP
#define ITERTOOLS_CFAR_A_RANGE_HPP

#include <sys/types.h> //uint

/**
 * for (iterator it = iterable.begin(); it != iterable.end(); ++it) {
    int x = *it;
    ...
}
 */
namespace itertools {
    class range {
        uint _start;
        uint _end;

    public:
        range(uint start, uint end): _start(start), _end(end){};
        typedef int value_type;//For compatibility

        class iterator
        {
            int _value;
        public:

            /**
             * explict keyword uses for prevent the compiler from using implicit conversation for constructors who
             * accepts 1 primitive type. The compiler as default behavior tries to do implicit conversation of that
             * type to a members exists within the class, hiding a bug.
             */
            explicit iterator(int value) : _value(value) {}
            //Iterator class must provide overloading of operators *, ++, !=
            int operator*() const { return _value; }
            bool operator==(const iterator& other) const { return _value == other._value; }
            bool operator!=(const iterator& other) const { return !(*this == other); }
            iterator& operator++(){
                ++_value;
                return *this;
            } //prefix ++
        };

        iterator begin() { return iterator(_start); }
        iterator end()   { return iterator(_end); }
    };
}

#endif //ITERTOOLS_CFAR_A_RANGE_HPP

//
// Created by osboxes on 6/9/20.
//

#ifndef ITERTOOLS_CFAR_A_ACCUMULATE_HPP
#define ITERTOOLS_CFAR_A_ACCUMULATE_HPP

#include <functional>

/**
 * Lambda expression:
 * [](int x, int y){return x*y;}
 */

namespace itertools {

    //Default function is plus two parameters
    template<typename Iter, typename lambada = std::plus<>>
    class accumulate {
        Iter & _iter; //We don't want to duplicate the container.
        lambada _func;

    public:
        /**
         * explict keyword uses for prevent the compiler from using implicit conversation for constructors who
         * accepts 1 primitive type. The compiler as default behavior tries to do implicit conversation of that
         * type to a members exists within the class, hiding a bug.
         */
        explicit accumulate(Iter & iter): accumulate(iter, _func) {}

        accumulate(Iter & iter, lambada func): _iter(iter){}

        class iterator{
            Iter & _it;
            decltype((_iter.begin())) _inner_iter;
            lambada _func;
            typename Iter::value_type _sum;
        public:

            iterator(Iter & it, lambada func):  _it(it), _inner_iter(it.begin()), _func(func), _sum(*_inner_iter){}

            //Iterator class must provide overloading of operators *, ++, !=
            auto operator*() const { return _sum; }
            bool operator==(const iterator& other) const { return _inner_iter == _it.end(); }
            bool operator!=(const iterator& other) const { return !(*this == other); }
            iterator& operator++(){
                ++_inner_iter;
                _sum = _func(_sum, *_inner_iter);//Perform the function.
                return *this;
            } //prefix ++
        };

        auto begin(){ iterator i(_iter, _func); return i.begin()}
        auto end(){iterator i(_iter, _func); return i.end()}

    };
}

#endif //ITERTOOLS_CFAR_A_ACCUMULATE_HPP

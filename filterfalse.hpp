//
// Created by osboxes on 6/9/20.
//

#ifndef ITERTOOLS_CFAR_A_FILTERFALSE_HPP
#define ITERTOOLS_CFAR_A_FILTERFALSE_HPP

#include <sys/types.h> //uint

namespace itertools {
    template< typename functor, typename Iter>
    class filterfalse {
        functor _functor;
        Iter & _iter;

    public:
        filterfalse(functor func, Iter & iter): _functor(func), _iter(iter){}

        class iterator
        {
            functor _filter;
            Iter & _it;
            decltype((_iter.begin())) _inner_iter;
            void normalize()
            {
                for(; _inner_iter != _it.end() && _filter(*_inner_iter); ++_inner_iter);//skip who ever not matching the filter
            }

        public:

            /**
             * explict keyword uses for prevent the compiler from using implicit conversation for constructors who
             * accepts 1 primitive type. The compiler as default behavior tries to do implicit conversation of that
             * type to a members exists within the class, hiding a bug.
             */
            iterator(functor operation, Iter & it) : _filter(operation),_it(it),  _inner_iter(_it.begin())
            {
                normalize();//We have to check the first element inside the ctor(otherwise it always stay)
            }

            //Iterator class must provide overloading of operators *, ++, !=
            auto operator*() const { return *_inner_iter; }
            bool operator==(const iterator& other) const {return _inner_iter == _it.end();}
            bool operator!=(const iterator& other) const { return !(*this == other); }

            iterator& operator++(){
                ++_inner_iter;
                normalize();
                return *this;
            } //prefix ++
        };

        iterator begin() { return iterator(_functor, _iter); }
        iterator end()   { return iterator(_functor, _iter); }
    };
}

#endif //ITERTOOLS_CFAR_A_FILTERFALSE_HPP

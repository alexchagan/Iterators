//
// Created by osboxes on 6/9/20.
//

#ifndef ITERTOOLS_CFAR_A_COMPRESS_HPP
#define ITERTOOLS_CFAR_A_COMPRESS_HPP

#include <vector>
using namespace std;

namespace itertools {
    template<typename Iter>
    class compress {
        Iter & _iter; //We don't want to duplicate the container.
        vector<bool> & _filter;
        decltype((_iter.begin())) _beg;//decltype uses to deduce runtime type of an object
        decltype((_iter.end())) _end_iter;

    public:
        //l-value ctor
        compress(Iter & iter, vector<bool> & filter): _iter(iter), _filter(filter), _beg(_iter.begin()), _end_iter(iter.end()){}
        //We need a reference to reference ctor in order to support passing reference of rvalue
        compress(Iter && iter, vector<bool> & filter): _iter(iter), _filter(filter), _beg(_iter.begin()), _end_iter(iter.end()){}

        class iterator{
            compress & _compress;
            decltype((_iter.begin())) _inner_iter;
            int _indexer;

        public:

            iterator(compress & compress): _inner_iter(compress._iter.begin()), _compress(compress), _indexer(0)
            {
                //Check for first element
                for(; _inner_iter != _compress._end_iter && !_compress._filter[_indexer]; ++_inner_iter, ++_indexer);//skip who ever not matching the filter
            }

            //Iterator class must provide overloading of operators *, ++, !=
            auto operator*() const { return *_inner_iter; }
            bool operator==(const iterator& other) const { return _inner_iter == _compress._iter.end(); }
            bool operator!=(const iterator& other) const { return !(*this == other); }
            iterator& operator++(){
                ++_inner_iter;
                ++_indexer;
                for(; _inner_iter != _compress._end_iter && !_compress._filter[_indexer]; ++_inner_iter, ++_indexer);//skip who ever not matching the filter
                return *this;
            } //prefix ++
        };

        auto begin(){ return iterator(*this);}
        auto end(){ return iterator(*this);}
    };
}


#endif //ITERTOOLS_CFAR_A_COMPRESS_HPP

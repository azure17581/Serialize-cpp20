#pragma once

#include <iostream>
#include <fstream>
#include <bit>
#include <stdexcept>

#include "bit_concept.h"

namespace bitRW {
    using namespace std;

    class bitSave{
    public:
        bitSave(string dst, bool d=false);

        string getDst();
        bool isOpen();
        void close();
        void open();

        //int, float,...
        template <BASIC T>
        void write(const T& x);

        //pair
        template <Pair T>
        void write(const T& x);

        //vector, list, map,...
        template <Container T>
        void write(const T& x);

        //STLarray
        template <Array T>
        void write(const T& x);

        //pointer
        // template<Pointer T>
        // void write(const remove_pointer_t<T> *const x);
        //template<Pointer T>
        //void write(const T const x);
        //template<class T>
        //void write(const T* const x);
        //参照先の値がconstになってない
        //         template <Pointer T>
// //        void write(const T& x);
//         void write(remove_pointer_t<T> const * const x);

        //class
        template<serializableClass T>
        void write(const T& x);

        //multi
        template <class H1, class H2, class... T>
        void write(const H1& head1, const H2& head2, const T& ...tail);

        // //STDarray
        // template <Pointer T>
        // void writeArr(const T& x, const size_t& s);

    private:
        string dstPath;
        ofstream ofs;
        bool dbg;
        void write(){};

    };

    class senderS{
    public:
        senderS(bitSave* s);

        template <class... Args>
        void operator()(const Args& ...args);

    private:
        bitSave* bs;
        void operator()() {};
    };
}
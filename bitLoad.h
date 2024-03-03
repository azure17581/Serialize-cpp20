#pragma once

#include <iostream>
#include <fstream>
#include <bit>
#include <stdexcept>

#include "bit_concept.h"

namespace bitRW {
    using namespace std;

    class bitLoad{
    public:
        bitLoad(string dst, bool d=false);

        string getDst();
        bool isOpen();
        void close();
        void open();
        bool isEOF();

        //int, float,...
        template <BASIC T>
        void read(T& x);

        //pair<T1, T2>
        template <Pair T>
        void read(T& x);

        //vector, list, string
        template <S_Container T>
        void read(T& x);

        //map, unordered_map
        template <Dictionary T>
        void read(T& x);

        //STLArray
        template <Array T>
        void read(T& x);

        //pointer
        // template <class T>
        // void read(T* x);
        // template <Pointer T>
        // void read(T& x);

        //class
        template <serializableClass T>
        void read(T& x);

        //multi
        template <class H, class... T>
        void read(H& head, T& ...tail);

        // //stdArr
        // template <Pointer T>
        // void read(T& x, size_t s);

    private:
        string dstPath;
        ifstream ifs;
        bool dbg;
        bool eof;
        void write(){};
    };

    class senderL{
    public:
        senderL(bitLoad* l);

        template<class... Args>
        void operator()(Args& ...args);
    
    private:
        bitLoad* bl;
        void operator()() {}
    };
}

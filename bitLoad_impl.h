#pragma once
#include "bitLoad.h"

namespace bitRW{
    using namespace std;

    //int, float,...
    template <BASIC T>
    void bitLoad::read(T& x){
//		cout << hex;
//		cout << (size_t)bit_cast<char*>(&x) << endl;
//		cout << &x << endl;
//		int kk;
//		cout << (size_t)bit_cast<char*>(&kk) << endl;
        if(this->eof) {
            cout << "EOF\n";
            throw runtime_error("EOF");
        }

        this->ifs.read(bit_cast<char*>(&x), sizeof(x));

        if(this->dbg) cout << "basicL : " << x << "\n";

        bool fail = this->ifs.fail();
        if(fail){
            cout << "LOAD FAILED\n";
            this->eof = true;
            throw runtime_error("EOF");
        }

        return;
    }

    //pair<T1, T2>
    template <Pair T>
    void bitLoad::read(T& x){
        if(this->dbg) cout << "PairL\n";

        this->read(x.first);
        this->read(x.second);

        return ;
    }

    //vector, string, list
    template <S_Container T>
    void bitLoad::read(T& x){
        if(this->dbg) cout << "S_ContainerL\n";

        size_t s = 0;
        this->read(s);
        x.resize(s);

        for(auto& temp : x){
            this->read(temp);
        }

        return;
    }

    //map, unordered_map
    template <Dictionary T>
    void bitLoad::read(T& x){
        if(this->dbg) cout << "DictionaryL\n";

        size_t s = 0;
        this->read(s);

        x.clear();

        typename T::key_type tk;
        typename T::mapped_type tm;
        for(size_t i=0; i<s; i++){
            this->read(tk);
            this->read(tm);

            x.insert(make_pair(tk, tm));
        }

        return;
    }

    //STLarray
    template <Array T>
    void bitLoad::read(T& x){
        if(this->dbg) cout << "STLArrayL\n";

        for(auto& temp : x){
            this->read(temp);
        }

        return;
    }

    //pointer
    // template <class T>
    // void bitLoad::read(T* x){
    //     if(this->dbg) cout << "PointerL \n";

    //     if(x==nullptr){
    //         throw runtime_error("nullptr");
    //     }

    //     this->read(*x);

    //     return;
    // }
    // template <Pointer T>
    // void bitLoad::read(T& x){
    //     if(this->dbg) cout << "PointerL\n";

    //     if(x == nullptr){
    //         throw runtime_error("nullPtr");
    //     }

    //     this->read(*x);

    //     return;
    // }

    //class
    template <serializableClass T>
    void bitLoad::read(T& x){
        if(this->dbg) cout << "ClassL\n";

        senderL sd(this);
        x.BITRW_BITLOAD(sd);

        return;
    }

    //multi
    template <class H, class... T>
    void bitLoad::read(H& head, T& ...tail){
        if(this->dbg) cout << "MultiL\n";

        this->read(head);
        this->read(tail...);

        return;
    }

//     //stdArr
//     template <Pointer T>
//     void bitLoad::read(T& x, size_t s){
// //		T ptr = x;

//         if(this->dbg) cout << "stdArray\n";
//         for(size_t i=0; i<s; i++){
//             this->read(x[i]);
//         }
//     }

    //--------------senderL
    template<class... Args>
    void senderL::operator()(Args& ...args){
        this->bl->read(args...);
    }

}
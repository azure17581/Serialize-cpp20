#pragma once
#include "bitSave.h"

namespace bitRW{
    using namespace std;

    //int, float,...
    template <BASIC T>
    void bitSave::write(const T& x){
        if(this->dbg) cout << "basicS : " << x << "\n";

        this->ofs.write(bit_cast<const char*>(&x), sizeof(x));

        return;
    }

    //pair<T1, T2>
    template <Pair T>
    void bitSave::write(const T& x){
        if(this->dbg) cout << "PairS\n";

        this->write(x.first);
        this->write(x.second);

        return;
    }

    //vector, list, map,...
    template <Container T>
    void bitSave::write(const T& x){
        if(this->dbg) cout << "ContainerS\n";

        size_t s = x.size();
        this->write(s);

        for(const auto& temp : x){
            this->write(temp);
        }

        return;
    }

    //STLarray
    template <Array T>
    void bitSave::write(const T& x){
        if(this->dbg) cout << "STLarrayS\n";

        for(const auto& temp : x){
            this->write(temp);
        }

        return;
    }

    // //Pointer
    // template<Pointer T>
    // void bitRW::bitSave::write(const remove_pointer_t<T>* const x) {
    //     if(this->dbg) cout << "PointerS\n";

    //     if(x == nullptr) throw runtime_error("nullPtr");

    //     this->write(*x);

    //     return;
    // }
    // template<Pointer T>
    // void bitSave::write(const T const x) {
    //     if(this->dbg) cout << "PointerS\n";

    //     if(x == nullptr) throw runtime_error("nullPtr");

    //     this->write(*x);

    //     return;
    // }
    // template<class T>
    // void bitSave::write(const T* const x){
    //     if(this->dbg) cout << "PointerS\n";

    //     if(x == nullptr) throw runtime_error("nullPtr");

    //     this->write(*x);

    //     return;
    // }
    // template <Pointer T>
    // void bitSave::write(remove_pointer_t<T> const * const x){
    //     if(this->dbg) cout << "PointerS\n";

    //     if(x == nullptr) throw runtime_error("nullPtr");

    //     this->write(*x);

    //     return;
    // }

    //class
    template <serializableClass T>
    void bitSave::write(const T& x){
        if(this->dbg) cout << "ClassS\n";

        senderS sd(this);
        x.BITRW_BITSAVE(sd);

        return;
    }

    //multi
    template <class H1, class H2, class... T>
    void bitSave::write(const H1& head1, const H2& head2, const T& ...tail){
        if(this->dbg) cout << "MultiS\n";

        this->write(head1);
        this->write(head2);
        this->write(tail...);

        return;
    }

    //STDarray
//     template <Pointer T>
//     void bitSave::writeArr(const T& x, const size_t& s){
// //		T ptr = x;
//         for(size_t i=0; i<s; i++){
//             this->write(x[i]);
// //			ptr++;
//         }

//         return;
//     }

    //-----------------senderS
    template <class... Args>
    void senderS::operator()(const Args& ...args){
        this->bs->write(args...);
    }
}
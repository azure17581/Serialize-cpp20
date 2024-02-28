#pragma once

#include "bit_concept.h"
#include "bitSave.h"
#include "bitLoad.h"

namespace bitRW{
    class sender{
    public:
        sender(bitLoad* l);
        sender(bitSave* s);
        template<class... Args>
        void operator()(Args& ...args);

    private:
        //false -> lode mode
        //true -> save mode
        bool mode;
        bitLoad* bl;
        bitSave* bs;

        void operator()() {}
    };

    template<class... Args>
    void sender::operator()(Args& ...args){
        if(this->mode){
            //save mode
            this->bs->write(args...);
        }else{
            //lode mode
            this->bl->read(args...);
        }
    }
}
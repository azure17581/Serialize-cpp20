#include "serialize.h"

namespace bitRW{
	using namespace std;

	bitSave::bitSave(string dst, bool d){
		this->dstPath = dst;
		this->open();
		this->dbg = d;
	}

	string bitSave::getDst(){
		return this->dstPath;
	}

	bool bitSave::isOpen(){
		return this->ofs.is_open();
	}

	void bitSave::close(){
		if(this->isOpen()) this->ofs.close();
		return;
	}

	void bitSave::open(){
		if(!this->isOpen()) this->ofs.open(this->dstPath, ios_base::binary);
	}

	//####

	bitLoad::bitLoad(string dst, bool d){
		this->dstPath = dst;
		this->open();
		this->dbg = d;
		this->eof = false;
	}

	string bitLoad::getDst(){
		return this->dstPath;
	}

	bool bitLoad::isOpen(){
		return this->ifs.is_open();
	}

	void bitLoad::close(){
		if(this->isOpen()) this->ifs.close();
		return;
	}

	void bitLoad::open(){
		if(!this->isOpen()) this->ifs.open(this->dstPath, ios_base::binary);
	}

	bool bitLoad::isEOF(){
		return this->eof;
	}

    // #### sender
    //lode mode
    sender::sender(bitLoad* l){
        mode = false;
        this->bl = l;
        this->bs = nullptr;
    }

    //save mode
    sender::sender(bitSave* s){
        mode = true;
        this->bl = nullptr;
        this->bs = s;
    }

	// ####
	senderS::senderS(bitSave* s){
		this->bs = s;
	}

	// ####
	senderW::senderW(bitLoad* l){
		this->bl = l;
	}
}
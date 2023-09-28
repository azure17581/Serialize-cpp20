#pragma once

#include <bit>
#include <fstream>
#include <iostream>

//#include "bit_concept.h"

namespace bitRW{
	using namespace std;

	template <BASIC T>
	bool bitLoad(T& x, ifstream& ifs, bool dbg = false){
		if(dbg) cout << "basicL\n";

		ifs.read(bit_cast<char*>(&x), sizeof(x));

		bool fail = ifs.fail();
		if(fail) cout << "LOAD FAILED\n";

		return !fail;
	}
	
	template <Pair T>
	bool bitLoad(T& x, ifstream& ifs, bool dbg = false){
		if(dbg) cout << "PairL\n";

		if(!bitLoad(x.first, ifs, dbg)) return false;
		if(!bitLoad(x.second, ifs, dbg)) return false;

		return true;
	}

	template <S_Container T>
	bool bitLoad(T& x, ifstream& ifs, bool dbg = false){
		if(dbg) cout << "S_ContainerL\n";

		size_t s = 0;
		bool stat = bitLoad(s, ifs);

		if(!stat) return false;

		x.resize(s);

		for(auto& temp : x){
			stat = bitLoad(temp, ifs, dbg);
			if(!stat) return false;
		}

		return stat;
	}

	template <Dictionary T>
	bool bitLoad(T& x, ifstream& ifs, bool dbg = false){
		if(dbg) cout << "DictionaryL\n";

		size_t s = 0;
		if(!bitLoad(s, ifs)) return false;

		x.clear();

		typename T::key_type tk;
		typename T::mapped_type tm;
		for(size_t i=0; i<s; i++){
			if(!bitLoad(tk, ifs, dbg)) return false;
			if(!bitLoad(tm, ifs, dbg)) return false;

			x.insert(make_pair(tk, tm));
		}

		return true;
	}
}
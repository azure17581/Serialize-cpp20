#pragma once
#include <bit>
#include <fstream>
#include <iostream>

#include "bit_concept.h"

namespace bitRW {
	using namespace std;

	template <BASIC T>
	void bitSave(const T& x, ofstream& ofs) {
		cout << "basicS\n";

		ofs.write(bit_cast<const char*>(&x), sizeof(x));

		return;
	}

	template <S_Container T>
	void bitSave(const T& x, ofstream& ofs) {
		cout << "S_ContainerS\n";
		size_t s = x.size();
		bitSave(s, ofs);

		for(const auto& temp : x){
//		for(const typename T::value_type& temp : x) {
			bitSave(temp, ofs);
		}

		return;
	}

	template <Dictionary T>
	void bitSave(const T& x, ofstream& ofs) {
		cout << "DictionaryS\n";
		size_t s = x.size();
		bitSave(s, ofs);

//		for(const typename T::value_type& temp : x) {
		for(const auto& temp : x) {
			bitSave(temp.first, ofs);
			bitSave(temp.second, ofs);
		}

		return;
	}
}
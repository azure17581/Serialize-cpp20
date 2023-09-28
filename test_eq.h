#include "bitSave.h"
#include "bitLoad.h"

using namespace std;
using namespace bitRW;

template<BASIC T>
bool test_eq(const T& x, const T& y){
	return x == y;
}

template<Pair T>
bool test_eq(const T& x, const T& y){
	return (x.first == y.first) && (x.second == y.second);
}

template<S_Container T>
bool test_eq(const T& x, const T& y){
	size_t s = x.size();
	if(s != y.size()) return false;

	auto yItr = y.begin();
	for(const auto& temp : x){
		if(!test_eq(temp, *yItr)) return false;
		yItr++;
	}

	return true;
}

//multimap は使えない
template<Dictionary T>
bool test_eq(const T& x, const T& y){
	size_t s = x.size();
	if(s != y.size()) return false;
	for(const auto& [key, val] : x){
		if(!y.count(key)) return false;
		if(!test_eq(val, y.at(key))) return false;
	}

	return true;
}


#include "test_eq.h"

size_t id = 0;

template<class T>
bool test_act(const T& x, string fn){
	string outPath = "test_out/" + fn;
	ofstream ofs;
	ofs.open(outPath, ios_base::binary);

	bitSave(x, ofs);
	ofs.close();

	T y;
	ifstream ifs;
	ifs.open(outPath, ios_base::binary);
	bool stat = bitLoad(y, ifs);

	return stat && test_eq(x, y);
}

template<class T>
void test(const T& x){
	string fn = "test" + to_string(id);
	if(test_act(x, fn)){
		cout << fn << "\t" << "OK\n";
	}else{
		cout << fn << "\t" << "NG\n";
	}

	id++;
	return;
}

int main(){
	test(0xfff);
	test(0xff5748bcdULL);

	vector<int> VInt1 = {0x23, 0xfff, 0x456, 0xabcd456};
	test(VInt1);
	vector<double> VDbl1 = {3.14, -5.82371, -4.678, 0.0};
	test(VDbl1);

	string str = "hoge";
	test(str);

	list<string> LStr = {"aa", "hogehoge", "shdfgoefg", "aaaaa"};
	test(LStr);

	map<char, int> MCI;
	MCI.emplace('x', 375);
	MCI.emplace('a', 777);
	MCI.emplace('~', 546151);
	test(MCI);

	vector<char> VChr1 = {};
	test(VChr1);

	vector<list<char>> VLC1;
	VLC1.push_back({'a', 'b', 'x', ' '});
	VLC1.push_back({'n', 'u', '\\'});
	VLC1.push_back({'l', '7', '(', 'V'});
	test(VLC1);

	return 0;
}
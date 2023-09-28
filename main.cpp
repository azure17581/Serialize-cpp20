#include <fstream>
#include <vector>
#include <string>
#include <list>
#include <map>
#include <utility>

#include "bitSave.h"
#include "bitLoad.h"

using namespace std;

void t1(){
	ofstream ofs;
	ofs.open("out", ios_base::binary);

	size_t s = 5;
	bitRW::bitSave(s, ofs);
	int x = 0xaa;
	bitRW::bitSave(x, ofs);
	x = 0x23;
	bitRW::bitSave(x, ofs);
	x = 0xfff;
	bitRW::bitSave(x, ofs);

	ofs.close();

	ifstream ifs;
	ifs.open("out", ios_base::binary);

	vector<int> v;
	bitRW::bitLoad(v, ifs);

	for(auto temp : v){
		cout << temp << " ";
	}
}

void t2(){
	ofstream ofs;
	ofs.open("out", ios_base::binary);

	string str = "hogefugapiyo";
	bitRW::bitSave(str, ofs);

	ofs.close();

	ifstream ifs;
	ifs.open("out", ios_base::binary);

	string str2;
	bitRW::bitLoad(str2, ifs);

	cout << str2 << endl;
}

void t3(){
	ofstream ofs;
	ofs.open("out", ios_base::binary);

	list<int> lst;
	lst.push_back(0x23);
	lst.push_back(0xfa);
	lst.push_back(0xbc);
	lst.push_back(0xc3);

	bitRW::bitSave(lst, ofs);
	ofs.close();

	ifstream ifs;
	ifs.open("out", ios_base::binary);

	list<int> lst2;
	bitRW::bitLoad(lst2, ifs);

	for(auto x : lst2){
		cout << x << " ";
	}

	return;
}

void t4(){
	ofstream ofs;
	ofs.open("out", ios_base::binary);

	float x = 0x1.3fbb5p+0f;

	bitRW::bitSave(x, ofs);
	ofs.close();

	ifstream ifs;
	ifs.open("out", ios_base::binary);

	float x2;
	bitRW::bitLoad(x2, ifs);

	cout << x2;

	return;
}

void t5(){
	ofstream ofs;
	ofs.open("out", ios_base::binary);

	map<char, int> mp, mp2;
	mp['a'] = 0x55;
	mp['x'] = 0xf0f0f0;
	mp['~'] = 0x1234567;

	bitRW::bitSave(mp, ofs);
	ofs.close();

	ifstream ifs;
	ifs.open("out", ios_base::binary);
	bitRW::bitLoad(mp2, ifs);

	return;	
}


int main() {
	t5();
	return 0;

	ofstream ofs;
	ofs.open("out", ios_base::binary);
	vector<int> v = {0xaa, 0x23, 0xfff, 0xabcd};

	bitRW::bitSave(v, ofs);
	ofs.close();

	ifstream ifs;
	ifs.open("out", ios_base::binary);

	vector<int> v2;
	bitRW::bitLoad(v2, ifs);
	for(auto x : v2){
		cout << x << " ";
	}

	return 0;
}
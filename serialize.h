#pragma once
#include <iostream>
#include <fstream>
#include <bit>
#include <stdexcept>

#include "bit_concept.h"

namespace bitRW {
	using namespace std;

	class bitSave{
	public:
		bitSave(string dst, bool d=false);

		string getDst();
		bool isOpen();
		void close();
		void open();

		//int, float,...
		template <BASIC T>
		void write(const T& x);

		//pair
		template <Pair T>
		void write(const T& x);

		//vector, list, map,...
		template <Container T>
		void write(const T& x);

		//pointer
		template <Pointer T>
		void write(const T& x);

		//class
		template <class T>
		void write(const T& x);

		//multi
		template <class H, class... T>
		void write(const H& head, const T& ...tail);

	private:
		string dstPath;
		ofstream ofs;
		bool dbg;
		void write(){};
	};

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
		bool read(T& x);

		//pair<T1, T2>
		template <Pair T>
		bool read(T& x);

		//vector, list, string
		template <S_Container T>
		bool read(T& x);

		//map, unordered_map
		template <Dictionary T>
		bool read(T& x);

		//pointer
		template <Pointer T>
		bool read(T& x);

	private:
		string dstPath;
		ifstream ifs;
		bool dbg;
		bool eof;
	};

	class senderS{
	public:
		senderS(bitSave* s);

		template <class... Args>
		void operator()(const Args& ...args);

	private:
		bitSave* bs;
		void operator()() {};

	};

	// bitSave #############################################

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

	//pointer
	template <Pointer T>
	void bitSave::write(const T& x){
		if(this->dbg) cout << "PointerS\n";
		if(x == nullptr) throw runtime_error("nullPtr");

		this->write(*x);

		return;
	}

	//class
	template <class T>
	void bitSave::write(const T& x){
		if(this->dbg) cout << "ClassS\n";

		senderS ss(this);
		x.RW(ss);

		return;
	}

	//multi
	template <class H, class... T>
	void bitSave::write(const H& head, const T& ...tail){
		if(this->dbg) cout << "MultiS\n";

		this->write(head);
		this->write(tail...);

		return;
	}


	// bitLoad #############################################

	//int, float,...
	template <BASIC T>
	bool bitLoad::read(T& x){
		cout << hex;
		cout << (size_t)bit_cast<char*>(&x) << endl;
		cout << &x << endl;
		int kk;
		cout << (size_t)bit_cast<char*>(&kk) << endl;
		if(this->eof) {
			cout << "EOF\n";
			return false;
		}

		this->ifs.read(bit_cast<char*>(&x), sizeof(x));

		if(this->dbg) cout << "basicL : " << x << "\n";

		bool fail = this->ifs.fail();
		if(fail){
			cout << "LOAD FAILED\n";
			this->eof = true;
		}

		return !fail;
	}

	//pair<T1, T2>
	template <Pair T>
	bool bitLoad::read(T& x){
		if(this->dbg) cout << "PairL\n";

		if(!this->read(x.first)) return false;
		if(!this->read(x.second)) return false;

		return true;
	}

	//vector, string, list
	template <S_Container T>
	bool bitLoad::read(T& x){
		if(this->dbg) cout << "S_ContainerL\n";

		size_t s = 0;
		if(!this->read(s)) return false;
		x.resize(s);

		for(auto& temp : x){
			if(!this->read(temp)) return false;
		}

		return true;
	}

	//map, unordered_map
	template <Dictionary T>
	bool bitLoad::read(T& x){
		if(this->dbg) cout << "DictionaryL\n";

		size_t s = 0;
		if(!this->read(s)) return false;

		x.clear();

		typename T::key_type tk;
		typename T::mapped_type tm;
		for(size_t i=0; i<s; i++){
			if(!this->read(tk)) return false;
			if(!this->read(tm)) return false;

			x.insert(make_pair(tk, tm));
		}

		return true;
	}

	//pointer
	template <Pointer T>
	bool bitLoad::read(T& x){
		if(this->dbg) cout << "PointerL\n";

		if(x == nullptr){
			throw runtime_error("nullPtr");
		}

		return (this->read(*x));
	}

	// senderS ######
	template <class... Args>
	void senderS::operator()(const Args& ...args){
		this->bs->write(args...);
	}
}
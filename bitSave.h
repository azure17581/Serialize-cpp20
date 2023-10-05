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

	class senderS{
	public:
		senderS(bitSave* s);

		template <class... Args>
		void operator()(const Args& ...args);

	private:
		bitSave* bs;
		void operator()() {};
	};

	//############################################################################

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

	// senderS ###################################################
	template <class... Args>
	void senderS::operator()(const Args& ...args){
		this->bs->write(args...);
	}
}
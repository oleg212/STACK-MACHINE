#pragma once
#define memsize 100
#include <string>
#include <iostream>
#include <fstream>

using namespace std;
class memory {
	string  a[memsize];

public:
	memory() {
		//string a[memsize];
		for (int i = 0; i < memsize; i++) {
			a[i] = "0";
		}
	}
	//~memory() {
	//	delete a;
	//}
	int get_int(int addr) {
		return atoi(a[addr].c_str());
	}
	double get_double(int addr) {
		return atof(a[addr].c_str());
	}
	 string get_str(int addr) {
		return a[addr];
	}
	void set(int addr, int val) {
		a[addr] = std::to_string(val);
	}
	void set(int addr, double val) {
		a[addr] = std::to_string(val);
	}
	void set(int addr, std::string val) {
		a[addr] = (val);
	}
	friend ostream& operator<<(ostream& out, memory& mem) {
		for (int i = 0; i < memsize; i++) {
			out << mem.get_str(i) << endl;
	}
		return out;
	}
	friend istream& operator>>(istream& in, memory& obj) {
		string temp;
		ifstream stream("memory.txt");
		int i = 0;
		while (stream) {
			getline(stream, temp);
			obj.a[i] = temp.substr(temp.find(']')+1, temp.length() - 1);

		}
		return in;
	}
	void save() {
		ofstream out("memory.txt");
		out << '[' << 0 << "] " << a[0];
		for (int i = 1; i < memsize; i++) {
			out << endl <<'['<<i<<"] " << a[i] ;
		}
	}
	void read() {
		ifstream in("memory.txt");
		in >> *this;
	}
};
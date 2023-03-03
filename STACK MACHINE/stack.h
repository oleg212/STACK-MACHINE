#pragma once

#include <string>
#include "memory.h"

#define size 100
using namespace std;


class stack {
	string  a[size];
	int up;
public:
	bool isempty() {
		return(up == -1);
	}
	stack() {
		string a [size];
		up = -1;
	}
	//~stack() {
	//	delete  a;
	//}
	void push_mem(int addr,memory mem ) {
		up++;
		a[up]=mem.get_str(addr);
		
	}
	void push(int val) {
		up++;
		a[up] = to_string(val);
	}
	void push(double val) {
		up++;
		a[up] = to_string(val);
	}
	void push(string val) {
		up++;
		a[up] =val;
	}

	void pop_mem(int addr, memory& mem) {
		if (isempty()) {
			throw "ERROR: stack empty";
		}
		mem.set(addr, a[up]);
		up--;

	}
	int pop_int() {
		int res = atoi(a[up].c_str());
		up--;
		return res;

	}
};
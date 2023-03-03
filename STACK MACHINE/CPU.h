#pragma once
#include "memory.h"
#include "stack.h"
#include <string>
#include <iostream>
#include <fstream>
#include <chrono>



//#include <map>
using namespace std;

//map <string, int> nums = {
//	{"IADD",1},
//	{"ISUB",2},
//	{"IMUL",3},
//	{"IDIV",4},
//	{"GET",5},
//	{"SET",6},
//	{"SETCONST",7}
//};

class CPU {
	memory mem;
	stack st;
	string  script[memsize*10];
	int counter;
private:
	void OR() {
		if (!st.isempty()) {
			int res = st.pop_int();
			if (!st.isempty()) {
				res =res||st.pop_int();
				st.push(res);
			}
			else { throw "ERROR: stack empty"; }
		}
		else { throw "ERROR: stack empty"; }
	}
	void AND() {
		if (!st.isempty()) {
			int res = st.pop_int();
			if (!st.isempty()) {
				res = res && st.pop_int();
				st.push(res);
			}
			else { throw "ERROR: stack empty"; }
		}
		else { throw "ERROR: stack empty"; }
	}
	void NOT() {
		if (!st.isempty()) {
			int res = st.pop_int();
			st.push(1-res);
		}
		
		else { throw "ERROR: stack empty"; }
	}
	void INT_ADD() {
		if (!st.isempty()) {
			int res = st.pop_int();
			if (!st.isempty()) {
				res += st.pop_int();
				st.push(res);
			}
			else { throw "ERROR: stack empty"; }
		}else { throw "ERROR: stack empty"; }
	}
	void INT_SUB() {
		if (!st.isempty()) {
			int res =  -st.pop_int();
			if (!st.isempty()) {
				res += st.pop_int();
				st.push(res);
			}
			else { throw "ERROR: stack empty"; }
		}
		else { throw "ERROR: stack empty"; }
	}
	void INT_MUL() {
		if (!st.isempty()) {
			int res = st.pop_int();
			if (!st.isempty()) {
				res *= st.pop_int();
				st.push(res);
			}
			else { throw "ERROR: stack empty"; }
		}
		else { throw "ERROR: stack empty"; }
	}
	void INT_DIV() {
		if (!st.isempty()) {
			int div = st.pop_int();
			if (!st.isempty()) {
				int res = st.pop_int()/div;
				st.push(res);
			}
			else { throw "ERROR: stack empty"; }
		}
		else { throw "ERROR: stack empty"; }
	}
	void GET(int addr) {
		st.push_mem(addr, mem);
	}
	void SET(int addr) {
		if (!st.isempty()) {
		st.pop_mem(addr, mem);
		savemem();
		}
		else { throw "ERROR: stack empty"; }
	}
	void PUSHCONST(string arg) {
		st.push(arg);
	}
	void EQ() {
		if (!st.isempty()) {
			int res = st.pop_int();
			if (!st.isempty()) {
				st.push(int(res == st.pop_int()));
			}
			else { throw "ERROR: stack empty"; }
		}
		else { throw "ERROR: stack empty"; }
	}
	void CL() {
		if (!st.isempty()) {
			int res = st.pop_int();
			if (!st.isempty()) {
				st.push(int(res < st.pop_int()));
			}
			else { throw "ERROR: stack empty"; }
		}
		else { throw "ERROR: stack empty"; }
	}
	void CG() {
		if (!st.isempty()) {
			int res = st.pop_int();
			if (!st.isempty()) {
				st.push(int(res > st.pop_int()));
			}
			else { throw "ERROR: stack empty"; }
		}
		else { throw "ERROR: stack empty"; }
	}
	void CLE() {
		if (!st.isempty()) {
			int res = st.pop_int();
			if (!st.isempty()) {
				st.push(int(res <= st.pop_int()));
			}
			else { throw "ERROR: stack empty"; }
		}
		else { throw "ERROR: stack empty"; }
	}
	void CGE() {
		if (!st.isempty()) {
			int res = st.pop_int();
			if (!st.isempty()) {
				st.push(int(res >= st.pop_int()));
			}
			else { throw "ERROR: stack empty"; }
		}
		else { throw "ERROR: stack empty"; }
	}
	void MOD() {
		if (!st.isempty()) {
			int res = st.pop_int();
			if (!st.isempty()) {
				res = st.pop_int() % res;
				st.push(res);
			}
			else { throw "ERROR: stack empty"; }
		}
		else { throw "ERROR: stack empty"; }
	}
	


	
	int find_type(string a) {
		if (a == "IADD") { return 1; }
		if (a == "ISUB") { return 2; }
		if (a == "IMUL") { return 3; }
		if (a == "IDIV") { return 4; }
		if (a == "GET") { return 5; }
		if (a == "SET") { return 6; }
		if (a == "PUSHCONST") { return 7; }
		if (a == "OR") { return 8; }
		if (a == "AND") { return 9; }
		if (a == "NOT") { return 10; }
		if (a == "JMP") { return 11; }
		if (a == "EQ") { return 12; }
		if (a == "CL") { return 13; }
		if (a == "CG") { return 14; }
		if (a == "CLE") { return 15; }
		if (a == "CGE") { return 16; }
		if (a == "MOD") { return 17; }

	}
public:
	CPU() {
		mem = memory();
		counter = 0;
		st = stack();
	}
	void savemem() {
		mem.save();
	}
	void readmem() {
		mem.save();
	}
	void EXECUTE(std::string ins) {
		int type = find_type(ins.substr(0, ins.find(' ')));
		string arg;
		if (ins.find(' ') > 0) {
			arg = ins.substr(ins.find(' ')+1, ins.length() - 1).c_str();
		}
		switch (type) {
			case 1: INT_ADD(); break;
			case 2: INT_SUB(); break;
			case 3: INT_MUL(); break;
			case 4: INT_DIV(); break;
			case 5: GET(atoi(arg.c_str())); break;
			case 6: SET(atoi(arg.c_str())); break;
			case 7: PUSHCONST((arg.c_str())); break;
			case 8: OR(); break;
			case 9: AND(); break;
			case 10: NOT(); break;
			case 11: if (st.pop_int()==1) counter = atoi(arg.c_str())-1; break;
			case 12: EQ(); break;
			case 13: CL(); break;
			case 14: CG(); break;
			case 15: CLE(); break;
			case 16: CGE(); break;
			case 17: MOD(); break;
		}
		savemem();
		
	}
	void RUN(string filename) {
		std::chrono::steady_clock::time_point begin = std::chrono::steady_clock::now();
		string temp;
		ifstream stream(filename);
		int scripti = 0;
		while (stream) {
			getline(stream,temp );
			if (temp.find("#") > 0) {
				script[scripti] = temp.substr(0, temp.find("#"));
			}else script[scripti]=(temp);
			scripti++;
		}
		int abs = 0;
		counter = 0;
		while (counter <= scripti+1) {
			string abb = script[counter];
			EXECUTE(script[counter]);
			counter++;
			abs++;
		}
		std::chrono::steady_clock::time_point end = std::chrono::steady_clock::now();
		std::cout << "Time difference = " << std::chrono::duration_cast<std::chrono::microseconds>(end - begin).count() << " s" << std::endl;
		cout << "instructions: " << abs<<endl;
	}

};
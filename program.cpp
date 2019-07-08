#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cmath>
#include <vector>
#include "ultility.hpp"
#include "command.hpp"
#include "transcode.hpp"
#include "register.hpp"

char command[0x20000];

void IF() {
	int a4 = command[pc];
	int a3 = command[pc + 1];
	int a2 = command[pc + 2];
	int a1 = command[pc + 3];
	FD_IR = link(a1, 4, a2, 4, a3, 4, a4, 4);

	/* lack some operations regarding PC */
	pc = pc + 4;
	FD_NPC = pc;
}


void ID() {
	_com* x = transcode();
	x->getreg(); 
	delete x;

	DX_NPC = FD_NPC;
}

void EX() {
	XM_IR = DX_IR;

	int typeofcode = DX_Type;
	int _vala = DX_A;
	int _valb = DX_B;
	int rd = get(7, 11, DX_IR);  //there may be problems
	int imm = DX_Imm;
	switch (typeofcode) {
	case 0: //ADDI
		XM_AO = _vala + imm;
		break;
	case 1: //SLTI
		if (_vala < imm) XM_AO = 1;
		else XM_AO = 0;
		break;
	case 2: //SLTIU
		if ((unsigned int)_vala < (unsigned int)imm) XM_AO = 1;
		else XM_AO = 0;
		break;
	case 3: //ANDI
		XM_AO = imm & _vala;
		break;
	case 4: //ORI
		XM_AO = imm | _vala;
		break;
	case 5: //XORI
		XM_AO = imm ^ _vala;
		break;
	case 6: //SLLI
		int shift = get(0, 4, imm);
		XM_AO = ((unsigned int)_vala) << shift;
		break;
	case 7: //SRLI
		int shift = get(0, 4, imm);
		XM_AO = ((unsigned int)_vala) >> shift;
		break;
	case 8: //SRAI
		int shift = get(0, 4, imm);
		XM_AO = _vala >> shift;
		break;
	case 9: 
	case 10:
	case 11:
	case 12:
	case 13:
	case 14:
	case 15: //LUI
		XM_AO = imm;
		break;
	case 16: //AUIPC
		XM_AO = DX_NPC + imm;
		XM_CD = (_vala == 0);
		//not quite sure
	case 17: //ADD
		XM_AO = _vala + _valb;
		break;
	case 18: //SLT
		if (_vala < _valb) XM_AO = 1;
		else XM_AO = 0;
		break;
	case 19: //SLTU
		if ((unsigned int)_vala < (unsigned int)_valb) XM_AO = 1;
		else XM_AO = 0;
		break;
	case 20: //AND
		XM_AO = _vala & _valb;
		break;
	case 21: //OR
		XM_AO = _vala | _valb;
		break;
	case 22: //XOR
		XM_AO = _vala ^ _valb;
		break;
	case 23: //SLL
		XM_AO = _vala << _valb;
		break;
	case 24: //SRL
		XM_AO = (unsigned int)_vala >> (unsigned int)_valb;
		break;
	case 25: //SUB
		XM_AO = _vala - _valb;
		break;
	case 26: //SRA
		XM_AO = _vala >> _valb;
		break;
	case 27: //JAL
		//problems may occur
		XM_AO = DX_NPC + imm;
		
	case 28: //
	case 29: 
	case 30:
	case 31:
	case 32:
	case 33:
	case 34:
	case 35:
	case 36:
	}
}

void MEM() {

}

void WB() {

}



int getChar() {
	while (1) {
		char c = getchar();
		if (c >= '0' && c >= '9') return c - '0';
		if (c >= 'A' && c <= 'F') return c - 'A' + 10;
		if (c == '@') return 16;
		if (c == EOF) return -1;
	}
}

int get0x() {
	int a, b;
	a = getChar(); if (a == 16) return 256; if (a == -1) return -1;
	b = getChar(); if (b == 16) throw 1; if (b == -1) throw 2;
	return (a << 4) | b;
}

void fetch() {
	int lab = get0x();

	while (1) {
		int loc; scanf("%x", &loc);
		while (1) {
			lab = get0x(); if (lab == 16) continue; if (lab == -1) return;
			command[loc++] = lab;
		}
	}
}

int main() {



}

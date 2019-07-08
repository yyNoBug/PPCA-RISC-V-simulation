#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cmath>
#include <vector>
#include "register.hpp"
#include "ultility.hpp"
#include "transcode.hpp"
#include "excecution.hpp"

unsigned char memory[0x20000];
bool stop;

void IF() {
	int a4 = memory[pc];
	int a3 = memory[pc + 1];
	int a2 = memory[pc + 2];
	int a1 = memory[pc + 3];
	FD_IR = link(a1, 4, a2, 4, a3, 4, a4, 4);

	pc = pc + 4;
	FD_NPC = pc;
}


void ID() {
	int ir = FD_IR;
	
	_com* x = transcode(ir);
	x->getreg(); 
	delete x;

	DX_IR = FD_IR;
	DX_NPC = FD_NPC;
}

void EX() {
	int type = DX_TYPE;
	int _vala = DX_A;
	int _valb = DX_B;
	int imm = DX_IMM;
	int npc = DX_NPC;
	
	excecute(_vala, _valb, imm, npc, type);
	XM_IR = DX_IR;
	XM_TYPE = DX_TYPE;
}

void MEM() {
	int type = XM_TYPE;
	int ao = XM_AO;
	int npc = XM_NPC;

	switch (type) {
	case 0: case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8: case 16:
	case 17: case 18: case 19: case 20: case 21:
	case 22: case 23: case 24: case 25: case 26:
		MB_AO = ao;
		break;
	case 10: case 11: case 12: case 13: case 14: case 15:
		MB_LMD = memory[ao];
		break;
	case 34: case 35: case 36:
		memory[ao] = XM_B;
		break;
	case 9: case 27: case 28: case 29:
	case 30: case 31: case 32: case 33:
		MB_AO = ao;
		MB_NPC = npc;
		break;
	}
	
	MB_IR = XM_IR;
	MB_TYPE = XM_TYPE;
}

void WB() {
	int type = MB_TYPE;
	int ir = MB_IR;
	int ao = MB_AO;
	int npc = MB_NPC;
	
	int rd;
	switch (type) {
	case 0: case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8: case 16:
	case 17: case 18: case 19: case 20: case 21:
	case 22: case 23: case 24: case 25: case 26:
		rd = get(7, 11, ir);
		x[rd] = ao;
		break;
	case 10: case 11: case 12: case 13: case 14: case 15:
		rd = get(7, 11, ir);
		x[rd] = ao;
		break;
	case 34: case 35: case 36:
		break;
	case 9: case 27: case 28: case 29:
	case 30: case 31: case 32: case 33:
		break;
	}
}

int getChar() {
	while (1) {
		char c = getchar();
		if (c >= '0' && c <= '9') return c - '0';
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
			memory[loc++] = lab;
		}
	}
}

int main() {
	fetch();

	stop = false;
	while (!stop) {
		IF();
		ID();
		EX();
		MEM();
		WB();
	}
	std::cout << ((unsigned int)x[10] & 0b11111111);
	//may cause problems
}

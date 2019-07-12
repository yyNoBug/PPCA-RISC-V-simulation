#include <iostream>
#include <stdio.h>
#include <cstring>
#include <cmath>
#include <vector>
#include "storage.hpp"
#include "ultility.hpp"
#include "transcode.hpp"
#include "excecution.hpp"
#include "readin.hpp"

using std::cout;

bool stop, fake;

void IF();
void ID();
void EX();
void MEM();
void WB();

int main() {

	fetch();

	while (1) {
		WB();
		MEM();
		EX();
		ID();
		IF(); if (stop) break;
	}
	WB();
	MEM();
	EX();
	WB();
	MEM();
	WB();

	cout << ((unsigned int)x[10] & 255u);
}

void IF() {
	int cond = XM_CD;
	int opcode = get(0, 6, XM_IR);
	int npc = XM_NPC;

	if (cond && isBranch(opcode)) {
		pc = npc;
		int rd = get(7, 11, DX_IR);
		if (spjdge(DX_IR) && FD_IR == 0) {
		    lock[rd]--;
		}
		FD_IR = 0;
		DX_IR = 0;
	}

	if (FD_IR) return;

	int a4 = memory[pc];
	int a3 = memory[pc + 1];
	int a2 = memory[pc + 2];
	int a1 = memory[pc + 3];
	FD_IR = link(a1, 8, a2, 8, a3, 8, a4, 8);
	if (FD_IR == 0x00c68223) stop = true;

	pc = pc + 4;
	FD_NPC = pc;
}


void ID() {
	if (!FD_IR || DX_IR) return;
	int ir = FD_IR;

	_com* x = transcode(ir);
	if (!x->getreg()) {
		delete x;
		return;
	}
	delete x;

	DX_IR = FD_IR;
	DX_NPC = FD_NPC;

	FD_IR = 0;
}

void EX() {
	if (!DX_IR || XM_IR) return;

	int type = DX_TYPE;
	int _vala = DX_A;
	int _valb = DX_B;
	int imm = DX_IMM;
	int npc = DX_NPC;

	excecute(_vala, _valb, imm, npc, type);
	XM_IR = DX_IR;
	XM_TYPE = DX_TYPE;

	DX_IR = 0;
}

void MEM() {
	if (!XM_IR || MB_IR) return;

	switch (memcnt) {
	case 2:
		memcnt--;
		return;
	case 1:
		memcnt--;
		break;
	case 0:
		int type = XM_TYPE;
		int ao = XM_AO;

		int a1, a2, a3, a4, st;
		switch (type) {
		case 0: case 1: case 2: case 3: case 4:
		case 5: case 6: case 7: case 8: case 15: case 16:
		case 17: case 18: case 19: case 20: case 21:
		case 22: case 23: case 24: case 25: case 26:
			break;
		case 10: //LW
			a4 = memory[ao];
			a3 = memory[ao + 1];
			a2 = memory[ao + 2];
			a1 = memory[ao + 3];
			MB_LMD = link(a1, 8, a2, 8, a3, 8, a4, 8);
			memcnt = 2;
			return;
		case 11: //LH
			a4 = memory[ao];
			a3 = memory[ao + 1];
			MB_LMD = ulink(a3, 8, a4, 8) << 16 >> 16;
			memcnt = 2;
			return;
		case 12: //LHU
			a4 = memory[ao];
			a3 = memory[ao + 1];
			MB_LMD = ulink(a3, 8, a4, 8);
			memcnt = 2;
			return;
		case 13: //LB
			a4 = memory[ao];
			MB_LMD = a4 << 24 >> 24;
			memcnt = 2;
			return;
		case 14: //LBU
			a4 = memory[ao];
			MB_LMD = a4;
			memcnt = 2;
			return;
		case 34: case 35: case 36:
			st = XM_B;
			memory[ao] = get(0, 7, st);
			memory[ao + 1] = get(8, 15, st);
			memory[ao + 2] = get(16, 23, st);
			memory[ao + 3] = get(24, 31, st);
			memcnt = 2;
			return;
		case 9: case 27:
			break;
		case 28: case 29: case 30:
		case 31: case 32: case 33:
			break;
		}
	}

	MB_IR = XM_IR;
	MB_AO = XM_AO;
	MB_TYPE = XM_TYPE;

	XM_IR = 0;
}

void WB() {
	if (!MB_IR) return;

	int type = MB_TYPE;
	int ir = MB_IR;
	int ao = MB_AO;

	int rd;
	rd = get(7, 11, ir);
	switch (type) {
	case 0: case 1: case 2: case 3: case 4:
	case 5: case 6: case 7: case 8: case 15: case 16:
	case 17: case 18: case 19: case 20: case 21:
	case 22: case 23: case 24: case 25: case 26:
		x[rd] = ao;
		lock[rd]--;
		break;
	case 10: case 11: case 12: case 13: case 14:
		x[rd] = MB_LMD;
		lock[rd]--;
		break;
	case 34: case 35: case 36:
		break;
	case 9: case 27: //JALR, JAL
		x[rd] = ao;
		lock[rd]--;
		break;
	case 28: case 29:case 30:
	case 31: case 32: case 33:
		break;
	}

	x[0] = 0;
	MB_IR = 0;
}

/* void display() {
	for (int i = 0; i < 32; ++i) {
		int s[32];
		unsigned int t = x[i];
		for (int j = 0; j < 32; ++j) {
			s[31 - j] = t % 2;
			t /= 2;
		}
		if (i >= 0 && i <= 9) printf("x[%d]:  ", i);
		else printf("x[%d]: ", i);
		for (int j = 0; j < 32; ++j) {
			printf("%d", s[j]);
			if (j % 4 == 3) printf(" ");
		}
		printf("\n");
	}
}*/

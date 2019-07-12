#ifndef STORAGE
#define STORAGE

unsigned char memory[0x20000];

int x[32], pc;

int FD_IR, FD_NPC;

int DX_IR, DX_NPC, DX_TYPE, DX_A, DX_B, DX_IMM;

int XM_IR, XM_NPC, XM_TYPE, XM_B, XM_AO, XM_CD;

int MB_IR, MB_TYPE, MB_AO, MB_LMD;

short lock[32];

int memcnt;

void efd() {
	FD_IR = 0;
	FD_NPC = 0;
}

void edx() {
	DX_IR = 0;
	DX_NPC = 0;
	DX_TYPE = 0;
	DX_A = 0;
	DX_B = 0;
	DX_IMM = 0;
}

void exm() {
	XM_IR = 0;
	XM_NPC = 0;
	XM_TYPE = 0;
	XM_B = 0;
	XM_AO = 0;
	XM_CD = 0;
}

void emb() {
	MB_IR = 0;
	MB_TYPE = 0;
	MB_AO = 0;
	MB_LMD = 0;
}

/*
struct FD {
	int IR, NPC;
};

struct DX {
	int IR, NPC, A, B, imm, type;
};

struct XM {
	int IR, NPC, AluOutput, cond, type;
};

struct MB {
	int IR, NPC, AluOutput, cond, LMD;
};*/

#endif // !STORAGE

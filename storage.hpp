#ifndef STORAGE
#define STORAGE

unsigned char memory[0x20000];

int x[32], pc;

int FD_IR, FD_NPC;

int DX_IR, DX_NPC, DX_TYPE, DX_A, DX_B, DX_IMM;

int XM_IR, XM_NPC, XM_TYPE, XM_B, XM_AO, XM_CD;

int MB_IR, MB_TYPE, MB_AO, MB_LMD;

short lock[32];


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

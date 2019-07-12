#ifndef STORAGE
#define STORAGE

unsigned char memory[0x20000];

int x[32], pc;

short lock[32];

struct regFD {
	int IR, NPC;
} FD;

struct regDX {
	int IR, NPC, A, B, imm, type;
} DX;

struct regXM {
	int IR, NPC, B, AluOutput, cond, type;
} XM;

struct regMB {
	int IR, NPC, AluOutput, cond, type, LMD;
} MB;

#endif // !STORAGE

#ifndef EXCECUTION
#define EXCECUTION

#include "storage.hpp"
#include "ultility.hpp"

void excecute(int _vala, int _valb, int imm, int npc, int typeofcode) {

	int rd = get(7, 11, DX_IR);  //there may be problems
	int shift;
	
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
		shift = get(0, 4, imm);
		XM_AO = ((unsigned int)_vala) << shift;
		break;
	case 7: //SRLI
		shift = get(0, 4, imm);
		XM_AO = ((unsigned int)_vala) >> shift;
		break;
	case 8: //SRAI
		shift = get(0, 4, imm);
		XM_AO = _vala >> shift;
		break;
	case 9: //JALR
		XM_AO = npc;
		XM_NPC = (_vala + imm) & (-2);
		XM_CD = 1;
		break;
	case 10: //LW
		XM_AO = _vala + imm;
		break;
	case 11: //LH
		XM_AO = _vala + imm;
		break;
	case 12: //LHU
		XM_AO = _vala + imm;
		break;
	case 13: //LB
		XM_AO = _vala + imm;
		break;
	case 14: //LBU
		XM_AO = _vala + imm;
		break;
	case 15: //LUI
		XM_AO = imm;
		break;
	case 16: //AUIPC
		XM_AO = npc - 4 + imm;
		break;
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
		XM_AO = npc;
		XM_NPC = npc + imm - 4;
		XM_CD = 1;
		break;
	case 28: //BEQ
		if (_vala == _valb) {
			XM_NPC = npc + imm - 4;
			XM_CD = 1;
		}
		else {
			XM_NPC = npc;
			XM_CD = 0;
		}
		break;
	case 29: //BNE
		if (_vala != _valb) {
			XM_NPC = npc + imm - 4;
			XM_CD = 1;
		}
		else {
			XM_NPC = npc;
			XM_CD = 0;
		}
		break;
	case 30: //BLT
		if (_vala < _valb) {
			XM_NPC = npc + imm - 4;
			XM_CD = 1;
		}
		else {
			XM_NPC = npc;
			XM_CD = 0;
		}
		break;
	case 31: //BLTU
		if ((unsigned int)_vala < (unsigned int)_valb) {
			XM_NPC = npc + imm - 4;
			XM_CD = 1;
		}
		else {
			XM_NPC = npc;
			XM_CD = 0;
		}
		break;
	case 32: //BGE
		if (_vala >= _valb) {
			XM_NPC = npc + imm - 4;
			XM_CD = 1;
		}
		else {
			XM_NPC = npc;
			XM_CD = 0;
		}
		break;
	case 33: //BGEU
		if ((unsigned int)_vala >= (unsigned int)_valb) {
			XM_NPC = npc + imm - 4;
			XM_CD = 1;
		}
		else {
			XM_NPC = npc;
			XM_CD = 0;
		}
		break;
	case 34: //SW
		XM_AO = _vala + imm;
		XM_B = _valb;
		break;
	case 35: //SH
		XM_AO = _vala + imm;
		XM_B = _valb & 0b1111111111111111;
		break;
	case 36: //SB
		XM_AO = _vala + imm;
		XM_B = _valb & 0b11111111;
		break;
	}
}

#endif // !EXCECUTION

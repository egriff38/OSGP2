//
// Created by Eshin Griffith on 11/3/17.
//

#ifndef PHASE_2_CPU_H
#define PHASE_2_CPU_H
#include "Ram.h"
#include <iostream>
#include "PCB.h"
#include <vector>
#include "Cache.h"
#include "MMU.h"

struct Op{
    std::string op_type;
    std::string op_code;
    int sreg1;
    int sreg2;
    int dreg;
    int breg;
    int address;
};

enum mode{debug,production};

class CPU {
private:
    MMU *mmu;
    int Register[16];
    int PC;
    Cache d_cache;
    Cache i_cache;
    bool RD(int s1, int s2, int address);
    bool WR(int s1, int s2, int address);
    bool ST(int addr, int breg, int dreg);
    bool LW(int addr, int breg, int dreg);
    bool MOV(int S1, int S2);
    bool ADD(int S1, int S2, int D);
    bool SUB(int S1, int S2, int D);
    bool DIV(int S1, int S2, int D);
    bool MUL(int S1, int S2, int D);
    bool AND(int S1, int S2, int D);
    bool OR(int S1, int S2, int D);
    bool MOVI(int val, int D);
    bool ADDI(int val, int D);
    bool DIVI(int val, int D);
    bool MULI(int val, int D);
    bool JMP(int line_no);
    bool LDI(int val, int D);
    bool SLT(int S, int B, int D);
    bool SLTI(int S, int val, int D);
    bool HLT();
    bool NOP();
    bool BEQ(int B, int D, int addr);
    bool BNE(int B, int D, int addr);
    bool BEZ(int B, int addr);
    bool BNZ(int B, int addr);
    bool BGZ(int B, int addr);
    bool BLZ(int B, int addr);

    std::string fetch(int i, std::string wr="");
    Op decode(std::string basic_string);
    void execute(Op op);

    void pass(std::string val);
public:
    int page_trip;
    PCB *state;
    bool Operate();
    void load_pcb(PCB *p);
    PCB* store_pcb();
    CPU(MMU* mmu,mode);
    int* dump_registers();
};


#endif //PHASE_2_CPU_H

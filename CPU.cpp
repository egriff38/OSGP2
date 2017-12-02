//
// Created by conrad on 11/7/17.
//

#include "CPU.h"
#include "Hex_Util.h"
#include "Log.h"


bool CPU::Operate() {
        std::string instruction = CPU::fetch(this->PC);
        if(instruction!="") {
            ++PC;
            Op decoded = CPU::decode(instruction);
            CPU::execute(decoded);
            if(state->state == PCB::PAGE_FAULT)
                --PC;
        }
        return true;
    }

CPU::CPU(MMU* mmu,mode m) {
    if(m==debug) std::cout<<"--DEBUG--\n";

    for (int i = 0; i < 16; ++i) {
        this->Register[i]=i;
    }
    this->Register[1] = 0;
    this->d_cache = Cache ();
    this->i_cache = Cache ();
    this->mmu = mmu;
}

bool CPU::RD(int s1, int s2, int address) {
    /*if(address==0)Register[s1] = Hex_Util::hex_to_decimal(cache.read(Register[s2] / 4));
    else Register[s1] = Hex_Util::hex_to_decimal(cache.read((address) / 4));*/
    std::string a;
    state->log->upIO();
    if(address==0) {
        a = fetch(Register[s2] / 4);
        Register[s1] = Hex_Util::hex_to_decimal(a);
    }
    else {
        a = fetch(address / 4);
        if(state->state != PCB::PAGE_FAULT) {
            state->state = PCB::IO_BLOCKED;
            state->s1 = s1;
            state->s2 = s2;
            state->address = Hex_Util::hex_to_decimal(a);
            state->read_IO = true;
        }
    }

    return true;
}

bool CPU::WR(int s1, int s2, int address) {
    std::string s = (fetch(address/4,Hex_Util::decimal_to_hex(Register[s1])));
    int addr = mmu->get_ram_frame(address/4/4,state);
    int off = (address/4) % 4;
    state->log->upIO();
    if(s == "") {
        state->state = PCB::PAGE_FAULT;
        return true;
    }
        state->state = PCB::IO_BLOCKED;
        state->s1  = s1;
        state->s2 = Hex_Util::hex_to_decimal(s);
        state->address = addr*4 + off;
        state->read_IO = false;
    return true;
}

bool CPU::ST(int addr, int breg, int dreg) {/*
    if(addr==0) cache.write(Register[dreg]/4, Hex_Util::decimal_to_hex(Register[breg]));
    else cache.write(addr/4, Hex_Util::decimal_to_hex(Register[breg]));*/
    state->log->upIO();
    if(addr==0) fetch(Register[dreg]/4, Hex_Util::decimal_to_hex(Register[breg]));
    else fetch(addr/4, Hex_Util::decimal_to_hex(Register[breg]));
    return true;
}

bool CPU::LW(int addr, int breg, int dreg) {
    /*cache.write(addr/4, Hex_Util::decimal_to_hex(Register[breg]));*/
    state->log->upIO();
    fetch(addr/4,Hex_Util::decimal_to_hex(Register[breg]));
    return true;
}

bool CPU::MOV(int S1, int S2) {
    this->Register[S1] = this->Register[S2];
    return true;
}
bool CPU::ADD(int S1, int S2, int D) {
    int s1=Register[S1];
    int s2=Register[S2];
    this->Register[D] = this->Register[S1] + this->Register[S2];

//    Debug::debug(Debug::VERBOSE, "CR["+std::to_string(S1)+"]("+std::to_string(s1)
//                                 +") + R["+std::to_string(S2)+"]("+std::to_string(s2)
//                                 +") -> R["+std::to_string(D)+"]("+std::to_string(Register[D])+")");
    return true;
}
bool CPU::SUB(int S1, int S2, int D) {
    int s1=Register[S1];
    int s2=Register[S2];
    this->Register[D] = this->Register[S1] - this->Register[S2];
//    Debug::debug(Debug::VERBOSE, "CR["+std::to_string(S1)+"]("+std::to_string(s1)
//                                 +") - R["+std::to_string(S2)+"]("+std::to_string(s2)
//                                 +") -> R["+std::to_string(D)+"]("+std::to_string(Register[D])+")");
    return true;
}
bool CPU::MUL(int S1, int S2, int D) {
    int s1=Register[S1];
    int s2=Register[S2];
    this->Register[D] = this->Register[S1] * this->Register[S2];
//    Debug::debug(Debug::VERBOSE, "CR["+std::to_string(S1)+"]("+std::to_string(s1)
//                                 +") * R["+std::to_string(S2)+"]("+std::to_string(s2)
//                                 +") -> R["+std::to_string(D)+"]("+std::to_string(Register[D])+")");
    return true;
}
bool CPU::DIV(int S1, int S2, int D) {
    int s1=Register[S1];
    int s2=Register[S2];
    this->Register[D] = this->Register[S1] / this->Register[S2];
//    Debug::debug(Debug::VERBOSE, "CR["+std::to_string(S1)+"]("+std::to_string(s1)
//                                 +") / R["+std::to_string(S2)+"]("+std::to_string(s2)
//                                 +") -> R["+std::to_string(D)+"]("+std::to_string(Register[D])+")");
    return true;
}
bool CPU::AND(int S1, int S2, int D) {
    this->Register[D] = this->Register[S1] & this->Register[S2];
    return true;
}
bool CPU::OR(int S1, int S2, int D) {
    this->Register[D] = this->Register[S1] | this->Register[S2];
    return true;
}
bool CPU::MOVI(int val, int D) {
    this -> Register[D] = val;
    return true;
}
bool CPU::ADDI(int val, int D) {
    this->Register[D]+= val;
    return true;
}
bool CPU::MULI(int val, int D) {
    this->Register[D]*= val;
    return true;
}
bool CPU::DIVI(int val, int D) {
    this->Register[D]/= val;
    return true;
}
bool CPU::LDI(int val, int D) {
    this->Register[D]= val;
    return true;
}
bool CPU::SLT(int S, int B, int D) {
    this->Register[D]= (this->Register[S]<this->Register[B])?1:0;
    return true;
}
bool CPU::SLTI(int S, int val, int D) {
    this->Register[D]= (this->Register[S]<val)?1:0;
    return true;
}
bool CPU::HLT() {
    this->state->state = state->COMPLETED;
    return true; //end program?
}
bool CPU::NOP() {
    return true;
}
bool CPU::JMP(int line_no) {
    PC = line_no/4;
    return true;
}
bool CPU::BEQ(int B, int D, int addr) {
    if(this->Register[B]==this->Register[D]) JMP(addr);
    return true;
}
bool CPU::BNE(int B, int D, int addr) {
    if(this->Register[B]!=this->Register[D]) JMP(addr);
    return true;
}
bool CPU::BEZ(int B, int addr) {
    if(this->Register[B]==0) JMP(addr);
    return true;
}
bool CPU::BNZ(int B, int addr) {
    if(this->Register[B]!=0) JMP(addr);
    return true;
}
bool CPU::BGZ(int B, int addr) {
    if(this->Register[B]>0) JMP(addr);
    return true;
}
bool CPU::BLZ(int B, int addr) {
    if(this->Register[B]<0) JMP(addr);
    return true;
}

int *CPU::dump_registers() {
    return Register;
}

std::string CPU::fetch(int addr, std::string wr) {
    //page and offset vector
    std::vector<int> a = {addr / 4, addr % 4};
    bool exists = this->state->page_table.count(a[0]) > 0; //checks for entry with matching key in page table
    bool isValid = std::get<2>(this->state->page_table[a[0]]); //checks valid bit

    if(addr<state->job_size+state->in_buf_size) {
        //check the cache
        auto cache = i_cache;
        if (addr > state->job_size) {
            cache = d_cache;
            addr -= state->job_size;
        }
        //cache vector (may be different for data)
        std::vector<int> b = {addr / 4, addr % 4};

        //check the cache
        std::string instr = cache.read_data(b[0])[b[1]];
        if (instr != "") return instr;

        //check ram... if exists and if valid bit
        if (exists && isValid) {
            //write page to cache
            int frame = std::get<1>(state->page_table[a[0]]);
            auto page = mmu->read_page_from_ram(frame);
            cache.write_data(b[0],page);
            //return that cache with offset
            std::string instr2 = cache.read_data(b[0])[b[1]];
            return instr2;
        }
    }
    // if we failed to be in read-only range, we need to go straight to the RAM
     if (exists && isValid) {
        int frame = std::get<1>(state->page_table[a[0]]);
        auto page = mmu->read_page_from_ram(frame);
        //Is there a string to be written? If so overwrite what was there and return your query string (guarenteed not to be empty)
//        if(wr!=""){
//            page[a[1]] = wr;
//            mmu->add_page_to_ram(page,frame);
//            return wr;
//        }
        //else return the value
        return page[a[1]];


    }
    /*
     * If the address either:
     * 1. was in the Read Only range, failed to be in the cache, and failed to be in the ram, or
     * 2. was not in the Read Only range, and failed to be in the ram
     * then we resort to a page fault, with the faulty *page* written to page_trip cpu member.
     * The methods in the CPU are designed to change the state to IO_BLOCKED if called from an I/O operation.
     */

    this->state->state = PCB::PAGE_FAULT;
    this->page_trip = a[0];
    return "";

}

Op CPU::decode(std::string hex) {
    std::string instruction = Hex_Util::hex_to_binary(hex);
    Op inst;
    inst.op_type = instruction.substr(0,2);
    inst.op_code = Hex_Util::binary_to_hex(instruction.substr(2, 6));
    if(inst.op_type=="00"){
        inst.sreg1 = Hex_Util::binary_to_decimal(instruction.substr(8, 4));
        inst.sreg2 = Hex_Util::binary_to_decimal(instruction.substr(12, 4));
        inst.dreg  = Hex_Util::binary_to_decimal(instruction.substr(16, 4));
        inst.address = -1;
        inst.breg = -1;

    }
    else if(inst.op_type=="01"){
        inst.breg = Hex_Util::binary_to_decimal(instruction.substr(8, 4));
        inst.dreg = Hex_Util::binary_to_decimal(instruction.substr(12, 4));
        inst.address = Hex_Util::binary_to_decimal(instruction.substr(16, 16));
        inst.sreg1 = -1;
        inst.sreg2 = -1;
    }
    else if(inst.op_type=="10"){
        inst.address = Hex_Util::binary_to_decimal(instruction.substr(8, 24));
        inst.sreg1 = -1;
        inst.sreg2 = -1;
        inst.breg = -1;
        inst.dreg = -1;

    }
    else if(inst.op_type=="11"){
        inst.sreg1 = Hex_Util::binary_to_decimal(instruction.substr(8, 4));
        inst.sreg2 = Hex_Util::binary_to_decimal(instruction.substr(12, 4));
        inst.address  = Hex_Util::binary_to_decimal(instruction.substr(16, 16));
        inst.breg = -1;
        inst.dreg = -1;
    }
    return inst;
}

void CPU::execute(Op op) {
    if(op.op_type=="00"){
        if(op.op_code=="04")CPU::MOV(op.sreg1,op.sreg2);
        else if(op.op_code=="05")CPU::ADD(op.sreg1,op.sreg2,op.dreg);
        else if(op.op_code=="06")CPU::SUB(op.sreg1,op.sreg2,op.dreg);
        else if(op.op_code=="07")CPU::MUL(op.sreg1,op.sreg2,op.dreg);
        else if(op.op_code=="08")CPU::DIV(op.sreg1,op.sreg2,op.dreg);
        else if(op.op_code=="09")CPU::AND(op.sreg1,op.sreg2,op.dreg);
        else if(op.op_code=="10")CPU::SLT(op.sreg1,op.sreg2,op.dreg);
        else if(op.op_code=="0A")CPU::OR(op.sreg1,op.sreg2,op.dreg);
    }else
    if(op.op_type=="01"){
        if(op.op_code=="02")CPU::ST(op.address,op.breg,op.dreg);
        else if(op.op_code=="03")CPU::LW(op.address,op.breg,op.dreg);
        else if(op.op_code=="0B")CPU::MOVI(op.address,op.dreg);
        else if(op.op_code=="0C")CPU::ADDI(op.address,op.dreg);
        else if(op.op_code=="0D")CPU::MULI(op.address,op.dreg);
        else if(op.op_code=="0E")CPU::DIVI(op.address,op.dreg);
        else if(op.op_code=="0F")CPU::LDI(op.address,op.dreg);
        else if(op.op_code=="11")CPU::SLTI(op.breg,op.address,op.dreg);
        else if(op.op_code=="15")CPU::BEQ(op.breg,op.dreg,op.address);
        else if(op.op_code=="16")CPU::BNE(op.breg,op.dreg,op.address);
        else if(op.op_code=="17")CPU::BEZ(op.breg,op.address);
        else if(op.op_code=="18")CPU::BNZ(op.breg,op.address);
        else if(op.op_code=="19")CPU::BGZ(op.breg,op.address);
        else if(op.op_code=="1A")CPU::BLZ(op.breg,op.address);
    }else
    if(op.op_type=="10"){
        if(op.op_code=="12")CPU::HLT();
        else if(op.op_code=="14")CPU::JMP(op.address);
    }else
    if(op.op_type=="11"){
        if(op.op_code=="00")
            CPU::RD(op.sreg1,op.sreg2,op.address);
        else if(op.op_code=="01")
            CPU::WR(op.sreg1,op.sreg2,op.address);
    }
}

void CPU::load_pcb(PCB *p) {
    this->state = p;
    PC = p->prgm_counter;
    this->state->state = PCB::RUNNING;
    for (int i = 0; i < 16; ++i) {
        this->Register[i] = this->state->registers[i];
    }

}
PCB* CPU::store_pcb() {
    PCB* out = state;
    out->prgm_counter = PC;
    i_cache.clear_cache();
    d_cache.clear_cache();
    for (int i = 0; i < 16; ++i) {
        out->registers[i] = this->Register[i];
    }

    return out;
}
void CPU::pass(std::string val) {
    Op decoded = CPU::decode(val);
    std::cout << "OpType: " << decoded.op_type << std::endl;
    std::cout << "OpCode: " << decoded.op_code << std::endl;
    std::cout << "sreg1: " << decoded.sreg1 << std::endl;
    std::cout << "sreg2: " << decoded.sreg2 << std::endl;
    std::cout << "dreg: " << decoded.dreg << std::endl;
    std::cout << "breg: " << decoded.breg << std::endl;
    std::cout << "address: " << decoded.address << std::endl <<std::endl;


    CPU::execute(decoded);
    for(int i=0;i<16;i++){
        std::cout << i <<"\t";
    }
    std::cout << std::endl;
    for (int i : this->Register) {
        std::cout << i <<"\t";
    }
    std::cout << std::endl;
}

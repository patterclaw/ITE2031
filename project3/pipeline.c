#include "pipeline.h"

#include "simulator.h"
#include "alu.h"
#include "control.h"
#include "reg_file.h"
#include "mem.h"
#include "forward.h"

#include <string.h>

void fetch(const unsigned int pc, IFID_reg* IFID) {
	unsigned int inst = inst_fetch(pc);
	IFID->PC = pc + 4;
	IFID->Inst = inst_fetch(pc);
}

void decode(const IFID_reg* IFID, const int detected, IDEX_reg* IDEX) {
	unsigned int inst;
	field_info fields; //opcode rs rt rd shamt func imm addr
	control ctl;
	inst = IFID->Inst;
#ifdef HYU_ITE2031
	// Detect any pipeline hazard and stall
	// TODO: complete here 
	if (detected) { //stall
		PCWrite=0;
		IFIDWrite=0;
		inst=NOP_INSTR;
	}

	// Decode the given instruction
	setup_fields(inst, &fields);

	// Read registers and store them into pipeline registers
	reg_file_read(fields.rs, fields.rt, IDEX);

	// Store pipeline registers
	// TODO: complete here 
	IDEX->PC=IFID->PC;
	IDEX->Inst=inst;
	IDEX->OPCode=fields.opcode;
	IDEX->RegisterRs=fields.rs;
	IDEX->RegisterRt=fields.rt;
	IDEX->RegisterRd=fields.rd;
	IDEX->Imm=fields.imm;
		
	// Determine control signals
	setup_control(inst, &ctl);
	
	// Store control into pipeline registers
	// TODO: complete here
	IDEX->ALUOp=ctl.ALUOp; //ex
	IDEX->RegDest=ctl.RegDest; //ex
	IDEX->MemRead=ctl.MemRead; //m
	IDEX->MemtoReg=ctl.MemtoReg; //wb
	IDEX->MemWrite=ctl.MemWrite; //m
	IDEX->ALUSrc=ctl.ALUSrc; //ex
	IDEX->RegWrite=ctl.RegWrite; //wb
	 
#endif //HYU_ITE2031
} 

void execute(const IDEX_reg* IDEX, const int valA, const int valB, 
		EXMEM_reg* EXMEM) {
	int ALU_ctl, ALU_out;
#ifdef HYU_ITE2031
	// TODO: complete here 
	ALU_ctl=setup_ALU_ctl(IDEX->ALUOp,IDEX->OPCode,IDEX->Inst & 0x3f);
	// ALU_ctl = setup_ALU_ctl(...);
	int value_b=valB;
	if(IDEX->ALUSrc){
		value_b=IDEX->Imm;
	}
	if(ALU_ctl==ALU_UNDEF){
		ALU_out=0;
	}else{
		ALU_out=do_ALU(valA,value_b,ALU_ctl);
	}
	// ALU_out = do_ALU(...);
	EXMEM->ALUResult=ALU_out;
	EXMEM->Data=valB;
	// Store pipeline registers
	EXMEM->PC=IDEX->PC;
	EXMEM->Inst=IDEX->Inst;
	EXMEM->RegisterRt=IDEX->RegisterRt;
	EXMEM->RegisterRd=IDEX->RegDest ? IDEX->RegisterRd : IDEX->RegisterRt;
	// Store control into pipeline registers
	EXMEM->RegDest=IDEX->RegDest;
	EXMEM->MemRead=IDEX->MemRead;
	EXMEM->MemtoReg=IDEX->MemtoReg;
	EXMEM->MemWrite=IDEX->MemWrite;
	EXMEM->RegWrite=IDEX->RegWrite;
#endif //HYU_ITE2031
}

void memory(const EXMEM_reg* EXMEM, const int valB, MEMWB_reg* MEMWB) {
#ifdef HYU_ITE2031
	// TODO: complete here 
	// Data access
	if(EXMEM->MemRead){
		MEMWB->Data=data_load(EXMEM->ALUResult);
	}
	if(EXMEM->MemWrite){
		data_store(EXMEM->ALUResult,valB);
	}
	// Store pipeline registers
	MEMWB->PC=EXMEM->PC;
	MEMWB->Inst=EXMEM->Inst;
	MEMWB->RegisterRd=EXMEM->RegisterRd;
	MEMWB->ALUResult=EXMEM->ALUResult;
	// Store control into pipeline registers
	MEMWB->RegDest=EXMEM->RegDest;
	MEMWB->MemtoReg=EXMEM->MemtoReg;
	MEMWB->RegWrite=EXMEM->RegWrite;
	
#endif //HYU_ITE2031
}

void writeback(const MEMWB_reg* MEMWB, IDEX_reg* IDEX,
		retirement_info* retired) {
#ifdef HYU_ITE2031
	// TODO: complete here 
	//regdest==0 : rt가 dest ->lw rt offset(rs)
	//regdest==1 : rd가 dest ->alu add rs rt rd
	if(MEMWB->RegWrite){
		//lw alu
		unsigned int data;
		if(MEMWB->MemtoReg){
			data=MEMWB->Data;
		}else{
			data=MEMWB->ALUResult;
		}
		reg_file_write(MEMWB->RegisterRd,data,IDEX);
	}

#endif //HYU_ITE2031
	// fill the retirement information which is used in print_state()
	retired->PC = MEMWB->PC;
	retired->Inst = MEMWB->Inst;
}

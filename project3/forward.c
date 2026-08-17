#include "forward.h"

int forwardIDA(const state_info* state, int valA) {
#ifdef HYU_ITE2031
	// TODO: complete here beq rs rt label
	field_info fields;
	unsigned char src;
	setup_fields(state->IFID.Inst,&fields);
	src=fields.rs;
	if(state->EXMEM.RegWrite && !state->EXMEM.MemtoReg
	&& state->EXMEM.RegisterRd && state->EXMEM.RegisterRd==src){
		return state->EXMEM.ALUResult;
	}
	if(state->MEMWB.RegWrite && state->MEMWB.RegisterRd && state->MEMWB.RegisterRd==src){
		if(state->MEMWB.MemtoReg){
			return state->MEMWB.Data;
		}else{
			return state->MEMWB.ALUResult;
		}
	}
	// No forwording
	return valA;
#endif //HYU_ITE2031
}

int forwardIDB(const state_info* state, int valB) {
#ifdef HYU_ITE2031
	// TODO: complete here
	field_info fields;
	unsigned char src;
	setup_fields(state->IFID.Inst,&fields);
	src=fields.rt;
	if(state->EXMEM.RegWrite && !state->EXMEM.MemtoReg
	&& state->EXMEM.RegisterRd && state->EXMEM.RegisterRd==src){
		return state->EXMEM.ALUResult;
	}
	if(state->MEMWB.RegWrite && state->MEMWB.RegisterRd && state->MEMWB.RegisterRd==src){
		if(state->MEMWB.MemtoReg){
			return state->MEMWB.Data;
		}else{
			return state->MEMWB.ALUResult;
		}
	}
	// No forwording
	return valB;
#endif // HYU_ITE2031
}

int forwardEXA(const state_info* state) {
#ifdef HYU_ITE2031
	// TODO: complete here
	unsigned char src=state->IDEX.RegisterRs;
	if(state->EXMEM.RegWrite && !state->EXMEM.MemtoReg && state->EXMEM.RegisterRd
	&& state->EXMEM.RegisterRd==src){
		return state->EXMEM.ALUResult;
	}
	if(state->MEMWB.RegWrite && state->MEMWB.RegisterRd && state->MEMWB.RegisterRd==src){
		if(state->MEMWB.MemtoReg){
			return state->MEMWB.Data;
		}else{
			return state->MEMWB.ALUResult;
		}
	}
	// No forwording
	return state->IDEX.valA;
#endif // HYU_ITE2031
}

int forwardEXB(const state_info* state) {
#ifdef HYU_ITE2031
	// TODO: complete here
	unsigned char src=state->IDEX.RegisterRt;
	if(state->EXMEM.RegWrite && !state->EXMEM.MemtoReg && state->EXMEM.RegisterRd
	&& state->EXMEM.RegisterRd==src){
		return state->EXMEM.ALUResult;
	}
	if(state->MEMWB.RegWrite && state->MEMWB.RegisterRd && state->MEMWB.RegisterRd==src){
		if(state->MEMWB.MemtoReg){
			return state->MEMWB.Data;
		}else{
			return state->MEMWB.ALUResult;
		}
	}
	// No forwording
	return state->IDEX.valB;
#endif // HYU_ITE2031

}

int forwardMEM(const state_info* state) {
#ifdef HYU_ITE2031
	// TODO: complete here sw rt offset(rs)
	unsigned char src=state->EXMEM.RegisterRt;
	if(state->MEMWB.RegWrite && state->MEMWB.RegisterRd==src){
		if(state->MEMWB.MemtoReg){
			return state->MEMWB.Data;
		}else{
			return state->MEMWB.ALUResult;
		}
	}
	// No forwording
	return state->EXMEM.Data;
#endif //HYU_ITE2031
}

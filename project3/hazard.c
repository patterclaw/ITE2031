#include "hazard.h"

int detect_load_use_data_hazard(const state_info* state) {
#ifdef HYU_ITE2031
	// TODO: complete here
	field_info fields;
	setup_fields(state->IFID.Inst, &fields);
	if(state->IDEX.MemRead && state->IDEX.RegisterRt!=0){
		if(state->IDEX.RegisterRt==fields.rs || state->IDEX.RegisterRt==fields.rt){
			return 1;
		}

	}
	return 0;
#endif //HYU_ITE2031
}

int detect_data_hazard_for_branch(const state_info* state) {
#ifdef HYU_ITE2031
	// TODO: complete here branch
	field_info fields;
	unsigned char rs,rt,idex_dst,exmem_dst;
	
	if(get_inst_type(state->IFID.Inst) != BEQ){
		return 0;
	}
	setup_fields(state->IFID.Inst, &fields);
	rs=fields.rs;
	rt=fields.rt;
	if(state->IDEX.RegDest){
		idex_dst=state->IDEX.RegisterRd;
	}else{
		idex_dst=state->IDEX.RegisterRt;
	}
	if(state->IDEX.RegWrite && idex_dst !=0){
		if(idex_dst ==rs || idex_dst ==rt){
			return 1;
		}
	}
	exmem_dst=state->EXMEM.RegisterRd;
	if(state->EXMEM.MemRead && exmem_dst!=0){
		if(exmem_dst ==rs || exmem_dst ==rt){
			return 1;
		}
	}
	return 0;
#endif //HYU_ITE2031
}

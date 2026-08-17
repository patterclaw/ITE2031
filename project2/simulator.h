#ifndef __SIMULATOR_H__
#define  __SIMULATOR_H__

#define SEG_SIZE 65536		/* maximum number of "bytes" in memory */
#define NUM_REGS 32 				/* number of machine registers */

#define TEXT_SECTION_START 0x00400000
#define DATA_SECTION_START 0x10000000

#define NOP_INST 0x0U

#define sign_extend(num) ((num << 16) >> 16)

typedef enum {
	UNDEFINED = -1, ADD, SLT, NOR, JR, ADDI, LW, SW, BEQ, JAL, J, NOP, LI, SYSCALL 
} OP_TYPE;

typedef struct {
	unsigned int pc;
	unsigned int regs[NUM_REGS];
	unsigned int text_len;
	unsigned int data_len;
	unsigned char text[SEG_SIZE];
	unsigned char data[SEG_SIZE];
} state_info;

typedef struct {
	// Most fields are 5 or 6 bits long
	unsigned char opcode; //6 31:26
	unsigned char rs; //5 25:21
	unsigned char rt; //5 20:16
	unsigned char rd; //5 15:11
	unsigned char shamt; //5 10:6
	unsigned char func; //6 5:0
	// imm field is 16-bit long
	int imm; //16 15:0
	// addr field is 26-bit long
	unsigned int addr; //26 25:0
} field_info;

// sub-routines for the simulator
void fetch(state_info*, unsigned int*);
void decode(const unsigned int, field_info*);
void execute(const unsigned int, const field_info*, state_info*);
void print_state(state_info *, unsigned int);

// helper functions
int get_op_type(const unsigned int);

#endif //__SIMULATOR_H__

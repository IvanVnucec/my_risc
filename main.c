#include <stdio.h>
#include <stdint.h>


#define MEM_SIZE 1024 // words


enum instructions {
    NOP,
    JMP,
    STR,
    LDR,
    ADD,
    SUB,
    NOT,
    AND,
    ORR,
    MOV
};

void debug_cpu(void);
void memory_init(void);
void cpu_tick(void);

uint32_t set_instruction(uint32_t mode, uint32_t value, uint32_t instr);
uint32_t get_reg_instr(void);
uint32_t get_reg_instr_value(void);
uint32_t get_reg_instr_mode(void);

void nop(void);
void jmp(void);
void str(void);
void ldr(void);
void add(void);
void sub(void);
void not(void);
void and(void);
void orr(void);
void mov(void);


uint32_t memory[MEM_SIZE];
uint32_t clock;

uint32_t reg_instr;
uint32_t reg_pc;
uint32_t reg_a;
uint32_t reg_b;
uint32_t reg_c;


int main(void) {
    memory_init();

    for (int i=0; i<30; i++) {
        cpu_tick();
    }

    printf("\nDone!\n");

    return 0;
}


// write program here
void memory_init(void) {
    memory[0] = set_instruction(0, 0, NOP);     // just incr PC
    memory[1] = set_instruction(0, 0x11, MOV);  // reg_a = 0x11
    memory[2] = set_instruction(1, 0x22, MOV);  // reg_b = 0x22
    memory[3] = set_instruction(0, 2, MOV);     // reg_a = 2
    memory[4] = set_instruction(1, 0, MOV);     // reg_b = 0
    memory[5] = set_instruction(1, 1, ADD);     // reg_c = reg_a + 1
    memory[6] = set_instruction(5, 0, MOV);     // reg_b = reg_c
    memory[7] = set_instruction(0, 0, ADD);     // reg_c = reg_a + reg_b
    memory[8] = set_instruction(0, 0, MOV);     // reg_a = 0
    memory[9] = set_instruction(1, 1, ADD);     // reg_c = reg_a + 1
    memory[10] = set_instruction(4, 0, MOV);    // reg_a = reg_c
    memory[11] = set_instruction(0, 9, JMP);    // pc = 9
}


uint32_t set_instruction(uint32_t mode, uint32_t value, uint32_t instr) {
    return (((uint32_t)(mode) << 29)
        | (((value) & 0x01FFFFFF) << 4) 
        | ((instr) & 0xF));
}


uint32_t get_reg_instr(void) {
    return reg_instr & (uint32_t) 0xF;
}


uint32_t get_reg_instr_value(void) {
    return ((reg_instr & 0x1FFFFFFF) >> 4);
}


uint32_t get_reg_instr_mode(void) {
    return reg_instr >> 29;
}


void cpu_tick(void) {
    clock++;
    
    // load instr from memory at PC 
    reg_instr = memory[reg_pc];

    uint32_t instruction = get_reg_instr();

    // execute instruction
    switch (instruction) {
    case NOP: nop(); break;
    case JMP: jmp(); break;
    case STR: str(); break;
    case LDR: ldr(); break;
    case ADD: add(); break;
    case SUB: sub(); break;
    case NOT: not(); break;
    case AND: and(); break;
    case ORR: orr(); break;
    case MOV: mov(); break;
    default:
        printf("ERROR: Undefined function: %d", instruction);
        while(1);
    }

    debug_cpu();

}


void nop(void) {
    // do nothing
    reg_pc++;
}


void jmp(void) {
    reg_pc = get_reg_instr_value();
}


void str(void) {
    // memory[pc + reg_c] = reg_a
    reg_pc++;
}


void ldr(void) {
    // reg_a = memory[pc + reg_c]
    reg_pc++;
}


void add(void) {
    switch (get_reg_instr_mode()) {
    case 0: // reg_c = reg_a + reg_b
        reg_c = reg_a + reg_b;
        break;

    case 1: // reg_c = reg_a + value
        reg_c = reg_a + get_reg_instr_value();
        break;
    default:
        printf("ERROR: Invalid reg_instr mode!\n");
        while(1);
    }

    reg_pc++;
}


void sub(void) {
    reg_c = reg_a - reg_b;
    reg_pc++;
}


void not(void) {
    reg_c = ~reg_a;
    reg_pc++;
}


void and(void) {
    reg_c = reg_a & reg_b;
    reg_pc++;
}


void orr(void) {
    reg_c = reg_a | reg_b;
    reg_pc++;
}


void mov(void) {
    switch (get_reg_instr_mode()) {
    case 0: // reg_a = value
        reg_a = get_reg_instr_value();
        reg_pc++;
        break;
    
    case 1: // reg_b = value
        reg_b = get_reg_instr_value();
        reg_pc++;
        break;
    
    case 2: // reg_a = pc
        reg_a = reg_pc;
        reg_pc++;
        break;
    
    case 3: // pc = reg_c
        reg_pc = reg_c;
        break;
    
    case 4: // reg_a = reg_c
        reg_a = reg_c;
        reg_pc++;
        break;

    case 5: // reg_b = reg_c
        reg_b = reg_c;
        reg_pc++;
        break;

    case 6: // reg_a = reg_b
        reg_a = reg_b;
        reg_pc++;
        break;

    case 7: // reg_b = reg_a
        reg_b = reg_a;
        reg_pc++;
        break;
    default:
        printf("ERROR: Invalid reg_instr mode!\n");
        while(1);
    }
}


void debug_cpu(void) {
    static const char *instr_names[] = {
        "NOP",
        "JMP",
        "STR",
        "LDR",
        "ADD",
        "SUB",
        "NOT",
        "AND",
        "ORR",
        "MOV"
    };

    static uint32_t last_pc;

    // print CPU regs
    printf("Clock: %d\n", clock);
    printf("REG_A: 0x%08x\n", reg_a);
    printf("REG_B: 0x%08x\n", reg_b);
    printf("REG_C: 0x%08x\n", reg_c);
    printf("REG_PC: 0x%08x (was 0x%08x)\n", reg_pc, last_pc);
    printf("REG_INSTR: 0x%08x (%s)\n\n", reg_instr, instr_names[get_reg_instr()]);

    last_pc = reg_pc;
}

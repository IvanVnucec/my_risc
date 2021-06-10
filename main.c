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
uint32_t pc;
uint32_t reg_a;
uint32_t reg_b;
uint32_t reg_c;


int main(void) {
    memory_init();

    for (int i=0; i<3; i++) {
        cpu_tick();
    }

    printf("\nDone!\n");

    return 0;
}


void memory_init(void) {
    memory[0] = JMP;
}


void debug_cpu(void) {
    // print CPU regs
    printf("REG_A: %d\n", reg_a);
    printf("REG_B: %d\n", reg_b);
    printf("REG_C: %d\n", reg_c);
    printf("PC: %d\n\n", pc);
}


void cpu_tick(void) {
    // load instr from PC
    uint32_t instr = memory[pc];

    // execute instruction
    switch (instr) {
    case NOP: nop(); pc++; break;
    case JMP: jmp(); break;
    case STR: str(); pc++; break;
    case LDR: ldr(); pc++; break;
    case ADD: add(); pc++; break;
    case SUB: sub(); pc++; break;
    case NOT: not(); pc++; break;
    case AND: and(); pc++; break;
    case ORR: orr(); pc++; break;
    case MOV: mov(); pc++; break;
    default:
        printf("ERROR: Undefined function: %d", instr);
        while(1);
    }

    debug_cpu();
}


void nop(void) {
    // do nothing
}


void jmp(void) {
    pc = reg_c;
}


void str(void) {
    // memory[pc + reg_c] = reg_a
}


void ldr(void) {
    // reg_a = memory[pc + reg_c]
}


void add(void) {
    reg_c = reg_a + reg_b;
}


void sub(void) {
    reg_c = reg_a - reg_b;
}


void not(void) {
    reg_c = ~reg_a;
}


void and(void) {
    reg_c = reg_a & reg_b;
}


void orr(void) {
    reg_c = reg_a | reg_b;
}


void mov(void) {
    // reg_a = value
    // reg_b = value
    // reg_a = pc
    // pc = reg_c
}


#include <stdio.h>
#include <stdint.h>


#define MEM_SIZE 1024 // words


enum instructions {
    NOP,
    STR,
    LDR,
    ADD,
    SUB,
    NOT,
    AND,
    ORR
};


void cpu_tick(void);


uint32_t memory[MEM_SIZE];
uint32_t pc;
uint32_t reg_a;
uint32_t reg_b;
uint32_t reg_c;


int main(void) {
    for (int i=0; i<100; i++) {
        cpu_tick();
    }

    printf("Done!\n");

    return 0;
}


void cpu_tick(void) {
    
}

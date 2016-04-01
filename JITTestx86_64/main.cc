//
//  main.cc
//  JITTestx86_64
//
//  Copyright © 2016 Satori. All rights reserved.
//

#include <iostream>
#include "Jit.h"

/** hello  world, x86_64
 mov     rsi, rdi       // move str pointer from arg 1 into arg 2
 mov     rax, 0x2000004 // write()
 mov     rdi, 1         // stdout
 mov     rdx, 14        // strlen("hello, world!\n")
 syscall
 ret                                                            */

inline uint8_t* $mov_rsi_rdi(uint8_t *buf) {
    uint8_t op[] = { 0x48, 0x89, 0xFE };
    memcpy(buf, op, sizeof(op));
    buf += sizeof(op);
    return buf;
}

inline uint8_t* $mov_rax_imm(uint8_t *buf, uint32_t imm) {
    uint8_t op[] = { 0x48, 0xC7, 0xC0, 0x00, 0x00, 0x00, 0x00 };
    memcpy(buf, op, sizeof(op));
    memcpy(buf+3, &imm, sizeof(imm));
    buf += sizeof(op);
    return buf;
}

inline uint8_t* $mov_rdi_imm(uint8_t *buf, uint32_t imm) {
    uint8_t op[] = { 0x48, 0xC7, 0xC7, 0x00, 0x00, 0x00, 0x00 };
    memcpy(buf, op, sizeof(op));
    memcpy(buf+3, &imm, sizeof(imm));
    buf += sizeof(op);
    return buf;
}

inline uint8_t* $mov_rdx_imm(uint8_t *buf, uint32_t imm) {
    uint8_t op[] = { 0x48, 0xC7, 0xC2, 0x00, 0x00, 0x00, 0x00 };
    memcpy(buf, op, sizeof(op));
    memcpy(buf+3, &imm, sizeof(imm));
    buf += sizeof(op);
    return buf;
}

inline uint8_t* $syscall(uint8_t *buf) {
    uint8_t op[] = { 0x0F, 0x05 };
    memcpy(buf, op, sizeof(op));
    buf += sizeof(op);
    return buf;
}

inline uint8_t* $ret(uint8_t *buf) {
    uint8_t op[] = { 0xC3 };
    memcpy(buf, op, sizeof(op));
    buf += sizeof(op);
    return buf;
}

const char *str = "hello, world!\n";

int main(int argc, const char * argv[]) {
    // insert code here...
    Jit *jit = Jit::CreateJIT();
    uint8_t *instrs = (uint8_t *)jit->Map();
   
    instrs = $mov_rsi_rdi(instrs);
    instrs = $mov_rax_imm(instrs, 0x2000004);
    instrs = $mov_rdi_imm(instrs, 1);
    instrs = $mov_rdx_imm(instrs, 14);
    instrs = $syscall(instrs);
    instrs = $ret(instrs);
    
    jit->Execute((void*)str);
    delete jit;
   
    return 0;
}

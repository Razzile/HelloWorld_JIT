//
//  main.cc
//  JITTestx86_64
//
//  Copyright © 2016 Satori. All rights reserved.
//

#include <iostream>
#include "Jit.h"

/*
 mov     rsi, rdi       // move str pointer from arg 1 into arg 2
 mov     rax, 0x2000004 // write()
 mov     rdi, 1         // stdout
 mov     rdx, 14        // strlen("hello, world!\n")
 syscall
 ret                                                            */
unsigned char hello_asm[] = {   0x48, 0x89, 0xFE, 0x48, 0xC7, 0xC0, 0x04, 0x00, 0x00, 0x02, 0x48,
                                0xC7, 0xC7, 0x01, 0x00, 0x00, 0x00, 0x48, 0xC7, 0xC2, 0x0E, 0x00,
                                0x00, 0x00, 0x0F, 0x05, 0xC3 };


const char *str = "hello, world!\n";

int main(int argc, const char * argv[]) {
    // insert code here...
    Jit *jit = Jit::CreateJIT(hello_asm, sizeof(hello_asm));
    jit->Execute((void*)str);
    delete jit;
   
    return 0;
}

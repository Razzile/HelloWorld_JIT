//
//  Jit.cc
//  JITTestx86_64
//
//  Copyright © 2016 Satori. All rights reserved.
//

#include "Jit.h"


Jit *Jit::CreateJIT() {
    Jit *jit = new Jit();
    
    jit->mapStart = mmap(NULL, 4096, PROT_READ | PROT_WRITE | PROT_EXEC, MAP_ANON | MAP_JIT | MAP_PRIVATE, -1, 0);
    
    if (jit->mapStart == (void*)-1) {
        perror(NULL);
        return jit;
    }
    
//    memcpy(jit->mapStart, data, datalen);
    
    return jit;
}

void Jit::Execute(void *ptr) {
    typedef void (*function)(void*);
    function func = (void (*)(void*))mapStart;
    func(ptr);
}
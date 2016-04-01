//
//  Jit.h
//  JITTestx86_64
//
//  Copyright © 2016 Satori. All rights reserved.
//

#ifndef _Jit_
#define _Jit_

#include <stdio.h>
#include <sys/mman.h>
#include <string.h>

class Jit {
public:
    static Jit *CreateJIT(void *data, size_t datalen);
    void Execute(void *ptr);
private:
    void CreateMap();
    
    void *mapStart;
};

#endif /* _Jit_ */

//#include "include/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int main() {
    //uintptr_t *p = (uintptr_t*)malloc(sizeof(uintptr_t));
    unsigned long thesize = 8192*8192;
    uintptr_t *p = (uintptr_t*)malloc(thesize);
    
    if( p==NULL )
    {
        printf("Unable to allocate memory\n");
        exit(1);
    } else {
        printf("Just allocated %lu to uintptr_t.\n", thesize);
        printf("(FYI the size of uintptr_t is %lu and an int is %lu)\n", sizeof(uintptr_t), sizeof(int));
    }
    
    int q = 10;
    *p = q;
    
    printf("\nuintptr_t before freeing: %lu\n", *p);
    free(p);
    printf("Freed the memory.\n");
    printf("On Debian g++, if 134473 or more bytes are allocated, the code runs to here and throws a segmentation fault.\n");
    printf("uintptr_t after freeing: %lu\n\n", *p);
    
    printf("On Apple clang the code runs to here and outputs 10 after free, even when 8192*8192 bytes are allocated.\n");
    printf("On Debian g++ the code runs to here and outputs 139968358726624 (for example) after free, if up to 134472 bytes are allocated (which is 8192*16.42).\n");
    printf("On QEMU morello-purecap WITHOUT cheri include files, the code runs to here and outputs 10 after free, even when 8192*8192 bytes are allocated.\n");
    printf("On QEMU morello-purecap the code runs to here and outputs 10 after free, even when 8192*8192 bytes are allocated.\n");

    return 0;
}





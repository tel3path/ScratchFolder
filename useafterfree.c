//#include "include/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

int main() {
    uintptr_t *p = (uintptr_t*)malloc(sizeof(uintptr_t));
    *p = 10;
    printf("uintptr_t before freeing: %lu\n", *p);
    free(p);
    printf("uintptr_t after freeing: %lu\n", *p);
    printf("On Apple clang the code runs to here and outputs 10 after free.\n");
    printf("On Debian g++ the code runs to here and outputs 0 after free.\n");
    printf("On QEMU morello-purecap the code runs to here and outputs 10 after free.\n");

    return 0;
}



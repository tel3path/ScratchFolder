#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#ifdef __CHERI_PURE_CAPABILITY__
#include "include/common.h"
#endif

#include "cheripointerbounds.h"

int main(int argc, char *argv[]) {
    int input;
    int lowertest = 8;
    int highertest = 32768;
     
    if (argc < 2) // no arguments were passed
    {
        exitstrategy(lowertest, highertest);
    } else {
        input = atoi(argv[1]);
        if(input<lowertest || input > highertest) 
            exitstrategy(lowertest, highertest);
    }
    char * buffer = malloc(input);
    if( buffer==NULL )
    {
        printf("Unable to allocate memory\n");
        exit(1);
    }
    uint64_t length = cheri_length_get(buffer);
    uint64_t lim = length-1;
    printf("Length of buffer is: %lu\n", length);
    for (uint32_t i = 0; i <= (length / sizeof(char)) + lim; i++) {
        uint64_t addr = cheri_address_get(buffer + i);
        printf("buffer[%d] address is %04lx\n", i, addr);
        uint64_t base = cheri_base_get(buffer + i);
        uint64_t limit = base + length;
        printf("buffer[%d] base is %04lx - %04lx\n", i, base, limit);
        uint64_t flags = cheri_flags_get(buffer + i);
        printf("buffer[%d] flags is %lx\n", i, flags);
        uint64_t perms = cheri_perms_get(buffer + i);
        printf("buffer[%d] value is %d\n", i, *(buffer + i));
    }
    free(buffer);
}

void exitstrategy(int lt, int ht) {
    printf("Enter a number between %d and %d: ", lt, ht);
    exit(1);
}





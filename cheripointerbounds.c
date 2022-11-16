#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <inttypes.h>

#ifdef __CHERI_PURE_CAPABILITY__
#include "include/common.h"
#endif

int main(int argc, char *argv[]) {
    int input;
    int lowertest = 8;
    int highertest = 32768;
    int bounds[2] = {lowertest, highertest};
    
    for(int i=0; i<sizeof(bounds); i++) {
        printf("Using malloc to give %d bytes to buffer.\n", bounds[i]);
        char * buffer = malloc(bounds[i]);
        if( buffer==NULL )
        {
            printf("Unable to allocate memory\n");
            exit(1);
        }
        uint64_t length = cheri_length_get(buffer);
        printf("Length of buffer is: %lu\n", length);
        uint64_t base = cheri_base_get(buffer);
        printf("Lower bound of buffer is %04lx\n", base);
        uint64_t ubound = base + length;
        printf("Upper bound of buffer is %04lx\n", ubound);

        printf("About to free this buffer.\n");
        free(buffer);
        printf("Successfully freed the buffer.\n");
    }
}






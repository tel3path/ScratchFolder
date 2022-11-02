# ScratchFolder
Scratch folder for rough drafts

==========

2 NOV 2022: Two files: notoverflow.c and overflow.c

One overflows a char array of length 1, and the other one doesn't.

----------

NOTOVERFLOW.C

The one that doesn't overflow (or at least doesn't crash) uses strlcpy() to try to put a 9-character string literal into a char array of size 1. It doesn't crash but it doesn't produce any output from the resulting buffer either.

--------

OVERFLOW.C

The one that does overflow uses strcpy(). 

First, it allocates a char array of size 2 and tries to use strcpy() to place one letter into it.

This produces the output: 

"buffer content= e
"strcpy() executed..."

on both CHERI and MacOS.

Then, it allocates a char array of size 1 and tries to use strcpy() to place one letter into it.

On CHERI this produces Error 255.

On MacOS this produces the same output as before:

"buffer content= e
"strcpy() executed..."

======================

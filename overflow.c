// buffer overflow                                                             \
                                                                                
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/**                                                                             
*                                                                               
* This is an incomplete and frustrated effort to                                
* first allocate a byte's worth of memory and not overflow it,                  
* and then allocate a byte's worth of memory and overflow it.                   
* I've been doing this remotely on bencher14.                                   
* I have been blocked by my unfamiliarity with the                              
* dev environment, so this has been more of an adventure                        
* in that sense than an adventure in code.                                      
*                                                                               
* I tried running this on my local (non-CHERI, MacOS) machine to compare        
* the "vanilla" behaviour.                                                      
*                                                                               
* I started by getting a command-line parameter but                             
* abandoned that approach after the following experiences:   
*                                                                               
* On MacOS, strcpy take 25 characters of command-line input before throwing     
* a segfault.                                                                   
*                                                                               
* If I do the strcpy programmatically, it accepts                               
* a much longer array (I didn't find the limits of it                           
* because I turned my attention elsewhere).                                     
*                                                                               
* On bencher14, if I don't put in a command-line argument,                      
* it ran far enough to prompt for input but didn't appear                       
* to respond when it got the input.      
*                                                                               
* If I did put in a command-line argument, e.g. "./testbreak 1"                 
* (which you will notice has only one character)                                
* there was also no output.                                                     
*                                                                               
* After some time of tinkering with this                                        
* I gave up and used the classic Wikipedia example                              
* which you see implemented below.                                              
*                                                                               
* I didn't resort to using any of the CHERI-specific                            
* API calls, at least.                                                          
*                                                                               
*/
int main(int argc, char *argv[])
{

char abuffer[2] = "";
       unsigned short B = 1979;

       // the below causes the following output:                                
       // buffer content= e                                                     
       // strcpy() executed...                                                  
       strcpy(abuffer, "e");
       printf("buffer content= %s\n", abuffer);
       printf("strcpy() executed...\n");

       char bbuffer[1] = "";
       unsigned short C = 1980;

       // the below causes the following output:                                
       // make: *** [build/Makefile.simple:46: run-overflow] Error 255          
       strcpy(bbuffer, "e");
       printf("buffer content= %s\n", bbuffer);
       printf("strcpy() executed...\n");   

       return 0;
}
                                              

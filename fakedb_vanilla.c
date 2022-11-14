#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
//#include<time.h>
#include "fakedb.h"

/**
* "Conventional code generation:
* "Unmodified operating systems, user programs, and user libraries 
* "will work without modification on CHERI processors. 
* "This code will not receive the benefits of CHERI memory protection 
* "– although it may execute encapsulated within sandboxes maintained
* "by CHERI-aware code, and thus can participate in a larger 
* "compartmentalized application. It will also be able to call hybrid
* code." - UCAM-CL-TR-951, Section 2.4.6
*
* This vanilla version should contain only CHERI-unaware code.
* [Attempt to] 1) compile and 2) run three ways:
* - using clang locally (Apple clang version 13.0.0 (clang-1300.0.29.30)
* Target: x86_64-apple-darwin20.6.0
* Thread model: posix
* OS: macOS Big Sur v11.7.1)
* - using g++ remotely in a non-CHERI environment on FreeBSD
* - using QEMU morello-purecap on bencher14
* Two other companion files adapted for similar comparison:
* fakedb_cherienv.c and fakedb_morello.c respectively
*
* Start with primitive data types and iterate from there.
*/

int main(int argc, char *argv[])
{
    // money for the employee's salary
    struct money *g6 = setMoney(30000.00, 35);
    
    printf("\nBartleby is an employee.\n");
    printf("Bartleby has an employee ID which is a char.\n");
    printf("Let's see if we can overflow that char and crash this.\n");
    printf("First we'll try it on MacOS, using:\n");
    printf("Apple clang version 13.0.0 (clang-1300.0.29.30)\n");

    // this shouldn't crash
    char *eid;
    eid = (char*)malloc(sizeof(char));
    strcpy((char*)eid,"0"); 
    char *enm = malloc(10);
    strcpy(enm, "Bartleby");
    char ejt[101];
    strcpy(ejt, "Scrivener");
    int emid = 0;
    char esd[11];
    strcpy(esd, "2020-06-30");
    struct employee *e1 = setEmployee(eid, enm, ejt, emid, esd, g6); 
    printf("This should look right:\n\n");
    printEmployee(e1, true);
    free(eid);
    
    // hopefully this *should* crash
    eid = (unsigned char*)malloc(4*sizeof(unsigned char));
    strcpy((char*)eid,"01234567"); 
    free(eid);    //crash plz?
    e1->empId = *eid;
    printf("If it hasn't crashed, this should at least look wrong:\n\n");
    printEmployee(e1, true);

    enm = malloc(101);
    strcpy(enm, "123456789101112ladybugscametotheladybugs\'picnic");
    printf("At this point on Apple clang I get \"illegal hardware instruction  ./fakedb_vanilla\n");
    strcpy(e1->empName, enm);
    strcpy(ejt, "Scrivener");
    strcpy(esd, "2020-06-30");
    printf("If you can see this, I gave the employee a too-long name, and their job title should look wrong:\n\n");
    printEmployee(e1, true);
    free(e1);
    

    return 0;
}

/**
* Takes in every member of an employee struct, instantiates it,
* sets the values, and returns it
*/
struct employee * setEmployee(char *eid, char enm[101], char ejt[101], int emgr, char esd[11],
struct money *em) {
    struct employee *e = malloc(sizeof (struct employee));
    e->empId = *eid;
    strcpy(e->empName, enm);
    strcpy(e->jobTitle, ejt);
    e->mgrId = emgr;
    strcpy(e->startDate, esd);
    e->salary = *em;
    return e;
}

/**
* Takes in every member of a money struct, instantiates it,
* sets the values, and returns it
*/
struct money * setMoney(long wd, unsigned char fd) {
    struct money *m = malloc(sizeof (struct money));
    m->whole_dollars = wd;
    m->frac_dollar = fd;
    return m;
}

void printEmployee(struct employee *emp, bool bStandalone) {
    if(bStandalone) {
        printf("EMPLOYEE\n");
        printf("========\n");
    }
    
    printf("Employee id is %c\n", emp->empId);
    printf("Employee is %s\n", emp->empName);
    printf("Employee job title is %s\n", emp->jobTitle);
    printf("Employee manager id is %d\n", emp->mgrId);
    printf("Employee start date was %s\n", emp->startDate);
    printf("Employee salary is ");
    printMoney(&emp->salary);
    printf("\n");
    
    if(bStandalone)
        printf("\n");
}

/**
* if only
*/
void printMoney(struct money *m) {
    printf("%ld.%d", m->whole_dollars, m->frac_dollar);
}


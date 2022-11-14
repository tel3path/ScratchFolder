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
    printf("Target: x86_64-apple-darwin20.6.0\n");
    printf("Thread model: posix\n\n");

    // the employee id
    // this shouldn't crash
    char *eid;
    // allocate the right amount of memory for a char
    eid = (char*)malloc(sizeof(char));
    // now give it an appropriate value for a char
    strcpy((char*)eid,"0"); 
    printf("\n\nEmployee id after allocating a char's worth = %c\n", *eid);
    // now set up the other employee attributes
    char *enm = malloc(10);
    strcpy(enm, "Bartleby");
    char ejt[101];
    strcpy(ejt, "Scrivener");
    int emid = 0;
    char esd[11];
    strcpy(esd, "2020-06-30");
    // now construct the employee
    struct employee *e1 = setEmployee(eid, enm, ejt, emid, esd, g6); 
    printf("Employee ID is set to the right type and size (char), so this should look right:\n\n");
    printEmployee(e1, true);
    printf("Input %c, displayed %c, value is %c\n\n", *eid, e1->empId, e1->empId);
    // free the employee ID char
    free(eid);
    
    // hopefully this *should* crash
    printf("Now let's try overflowing the employee ID char.\n");
    printf("I know this would have crashed it elsewhere, doesn\'t seem to on Apple clang version 13.0.0.\n");
    printf("Quadrupling the allocation to the employee ID char AND making it unsigned:\n");
    eid = (unsigned char*)malloc(4*sizeof(unsigned char));
    printf("Now writing 8 bytes to employee ID char (8 times too much for a char, twice the amount given to malloc):\n");
    strcpy((char*)eid,"01234567"); 
    printf("eid = %c\n", *eid);
    printf("Now freeing the new empId and hoping *that* crashes it (like it used to):\n");
    free(eid);    //crash plz?
    printf("the new empId after freeing = %c\n", *eid);
    printf("And if that didn't crash it let's try assigning the too-big value to the employee structure:\n");
    e1->empId = *eid;
    printEmployee(e1, true);
    printf("Input %c, displayed %c, value is %c\n\n", *eid, e1->empId, e1->empId); 
    
    printf("\n\nWhy didn't it crash? Char is only supposed to be %zu\n", sizeof(char));
    
    printf("Well, let's try this. I gave the employee member empName 10 chars,\n");
    printf("but I'm still going to allocate 101, then put in a string longer than 10 but shorter than 101.\n");
    printf("Then I'll try to free it. That should crash it.\n\n");
    printf("Allocating 101 chars to a variable:\n");
    enm = malloc(101);
    printf("Now giving the variable a string no more than 50 chars long\n");
    strcpy(enm, "123456789101112ladybugscametotheladybugs\'picnic");
    printf("Now assigning it to the (10-char) employee member, empName\n");
    printf("At this point on Apple clang I get \"illegal hardware instruction  ./fakedb_vanilla\n");
    strcpy(e1->empName, enm);
    printf("Now giving the employee their last name\n");
    strcpy(ejt, "Scrivener");
    printf("Now setting the employee's start date\n");
    strcpy(esd, "2020-06-30");
    printf("Now let's look at the employee\n");
    printEmployee(e1, true);
    printf("Now freeing up that employee's memory:\n");
    free(e1);
    

    
    /*signed char sc1 = -127;
    printf("Setting the employee ID char to a signed char, so the following should look wrong:\n\n");
    e1->empId = sc1;
    printEmployee(e1, true);
    printf("Input %d, expected %d, got %c\n\n", sc1, e1->empId, e1->empId);
    printf("Subtracting 4 from %d\n", sc1);
    sc1 -= 4;
    e1->empId = sc1;
    printEmployee(e1, true);
    printf("Input %d, expected %d, got %c\n\n", sc1, e1->empId, e1->empId);
    
    unsigned char uc1 = 255;
    printf("Setting the employee ID char to an unsigned char, so the following should look wrong:\n\n");
    e1->empId = uc1;
    printEmployee(e1, true);
    printf("Input %d, displayed %c, value is %d\n\n", uc1, e1->empId, e1->empId);
    printf("Adding 4 to %d\n", uc1);
    uc1 += 4;
    e1->empId = uc1;
    printEmployee(e1, true);
    printf("Input %d, expected %d, got %c\n\n", uc1, e1->empId, e1->empId);

    
    short int si1 = 32767;
    printf("Setting the employee ID char to a short int, so the following should look wrong:\n\n");
    e1->empId = si1;
    printEmployee(e1, true);
    printf("Input %d, displayed %c, value is %d\n\n", si1, e1->empId, e1->empId);
    printf("Adding 4 to %d\n", si1);
    si1 += 4;
    e1->empId = si1;
    printEmployee(e1, true);
    printf("Input %d, expected %d, got %c\n\n", si1, e1->empId, e1->empId);*/

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

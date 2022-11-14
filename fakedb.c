// Comment this out if compiling in a non-CHERI environment
//#include "include/common.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include <stdbool.h>
#include "fakedb.h"

int main(int argc, char *argv[])
{
    // this shouldn't crash
    char *eid;
    eid = (char*)malloc(sizeof(char));
    printf("\nIf I do make-run on QEMU morello-purecap, it falls over here:\n\n");
    strcpy((char*)eid,"0"); 
    char *enm = malloc(10);
    strcpy(enm, "Bartleby");
    char ejt[101];
    strcpy(ejt, "Scrivener");
    int emid = 0;
    char esd[11];
    strcpy(esd, "2020-06-30");
    struct employee *e1 = setEmployee(eid, enm, ejt, emid, esd); 
    printf("This should look right:\n\n");
    printEmployee(e1);
    free(eid);
    
    // hopefully this *should* crash
    eid = (unsigned char*)malloc(4*sizeof(unsigned char));
    strcpy((char*)eid,"01234567"); 
    free(eid);    
    e1->empId = *eid;
    printf("If it hasn't crashed, this should at least look wrong:\n\n");
    printEmployee(e1);

    enm = malloc(101);
    strcpy(enm, "123456789101112ladybugscametotheladybugs\'picnic");
    printf("On Apple clang it falls over here, with \"illegal hardware instruction\"\n");
    strcpy(e1->empName, enm);
    printEmployee(e1);
    free(e1);
    printf("If I compile and run this on Debian g++ it runs to the end (here)\n");

    return 0;
}

/**
* Takes in every member of an employee struct, instantiates it,
* sets the values, and returns it
*/
struct employee * setEmployee(char *eid, char enm[101], char ejt[101], int emgr, char esd[11]) {
    struct employee *e = malloc(sizeof (struct employee));
    e->empId = *eid;
    strcpy(e->empName, enm);
    strcpy(e->jobTitle, ejt);
    e->mgrId = emgr;
    strcpy(e->startDate, esd);
    return e;
}

void printEmployee(struct employee *emp) {
    printf("EMPLOYEE\n");
    printf("========\n");
    
    printf("Employee id is %c\n", emp->empId);
    printf("Employee is %s\n", emp->empName);
    printf("Employee job title is %s\n", emp->jobTitle);
    printf("Employee manager id is %d\n", emp->mgrId);
    printf("Employee start date was %s\n\n", emp->startDate);
}


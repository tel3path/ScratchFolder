#include "include/common.h"
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
* This begins as a straight copy of the vanilla version,
* contain only CHERI-unaware code.
* Then I attempt to 1) compile and 2) run it using g++
* remotely in a non-CHERI environment on FreeBSD
* and make changes as necessary.
* [Attempt to] 1) compile and 2) run three ways:
* - The vanilla version, fakedb_vanilla.c, was compiled and
* run using clang locally (Apple clang version 13.0.0 (clang-1300.0.29.30)
* Target: x86_64-apple-darwin20.6.0
* Thread model: posix
* OS: macOS Big Sur v11.7.1)
* - This version built using g++ remotely in a non-CHERI environment on FreeBSD
* - Fakedb_morello.c built using QEMU morello-purecap on bencher14
*
* Start with primitive data types and increment
*/

int main(int argc, char *argv[])
{
    // money for the employee's salary
    struct money *g6 = setMoney(30000.00, 35);
    
    // the price of goods
    struct money *allOnePrice = setMoney(0, 99);
    
    // our basic customer
    struct customer c1 = setCustomer(0, "Herman");
    //printCustomer(c1, true);
    
    // an address
    // this is a pointless way to assign values, considering strcpy.
    // Oh well
    int a1id = 0;
    char a1l1[101];
    strcpy(a1l1, "15 Acacia Avenue");
    char a1l2[101];
    strcpy(a1l2, "Little Snoring");
    char a1l3[101];
    char a1l4[101];
    char a1l5[101];
    char a1rgn[101];
    strcpy(a1rgn, "Wiltshire");
    char a1pc[21];
    strcpy(a1pc, "90210");
    char a1ctry[101];
    strcpy(a1ctry, "United Kingdom");
    struct address a1 = setAddress(a1id, a1l1, a1l2, a1l3, a1l4, a1l5, a1rgn, a1pc, a1ctry);
    //printAddress(a1, true);

    int intlimit = INT_MAX;
    float overfloat = 6000000.01;

    // the employee
    char eid = 48;
    char enm[101];
    strcpy(enm, "Bartleby");
    char ejt[101];
    strcpy(ejt, "Scrivener");
    int emid = 0;
    char esd[11];
    strcpy(esd, "2020-06-30");
    struct employee e1 = setEmployee(eid, enm, ejt, emid, esd, g6);
    printf("Employee ID is supposed to be a char, and is a char, so the following should look like it's supposed to:\n\n");
    printEmployee(e1, true);
    printf("Input %c, displayed %c, value is %c\n\n", eid, e1.empId, e1.empId); 
    
    // not sure outputting it to a file is useful
    /*FILE *fptr;
    fptr = fopen("blorf.txt","w");
    if(fptr == NULL) {
      printf("Error!");
      exit(1);
    }
    fprintf(fptr,"mode,expected type,original param,expected display,input type,input param,displayed conversion,type-appropriate conversion\n");
    fprintf(fptr,"==================================================================================\n");
    fprintf(fptr,"vanilla,char,48,0,char,48,%c,%c\n", e1.empId, e1.empId);*/
    
    signed char sc1 = -127;
    printf("Setting the employee ID char to a signed char, so the following should look wrong:\n\n");
    e1.empId = sc1;
    printEmployee(e1, true);
    printf("Input %d, expected %d, got %c\n\n", sc1, e1.empId, e1.empId);
    //fprintf(fptr,"vanilla,char,48,0,signed char,-127,%c,%d\n", e1.empId, e1.empId);
    printf("Subtracting 4 from %d\n", sc1);
    sc1 -= 4;
    e1.empId = sc1;
    printEmployee(e1, true);
    printf("Input %d, expected %d, got %c\n\n", sc1, e1.empId, e1.empId);
    
    unsigned char uc1 = 255;
    printf("Setting the employee ID char to an unsigned char, so the following should look wrong:\n\n");
    e1.empId = uc1;
    printEmployee(e1, true);
    printf("Input %d, displayed %c, value is %d\n\n", uc1, e1.empId, e1.empId);
    //fprintf(fptr,"vanilla,char,48,0,unsigned char,255,%c,%d\n", e1.empId, e1.empId);
    printf("Adding 4 to %d\n", uc1);
    uc1 += 4;
    e1.empId = uc1;
    printEmployee(e1, true);
    printf("Input %d, expected %d, got %c\n\n", uc1, e1.empId, e1.empId);

    
    short int si1 = 32767;
    printf("Setting the employee ID char to a short int, so the following should look wrong:\n\n");
    e1.empId = si1;
    printEmployee(e1, true);
    printf("Input %d, displayed %c, value is %d\n\n", si1, e1.empId, e1.empId);
    //fprintf(fptr,"vanilla,char,48,0,short int,32767,%c,%d\n", e1.empId, e1.empId);
    printf("Adding 4 to %d\n", si1);
    si1 += 4;
    e1.empId = si1;
    printEmployee(e1, true);
    printf("Input %d, expected %d, got %c\n\n", si1, e1.empId, e1.empId);

    
    //fclose(fptr);
    
    // the order
    int oid = 0;
    char od[11];
    strcpy(od, "2022-11-07");
    char odd[11];
    strcpy(odd, "2022-13-07");
    bool obd = false;
    char oir[21];
    strcpy(oir, "1234567");
    char oin[101];
    strcpy(oin, "Banana Bender");
    int oq = 33;
    struct order o1 = setOrder(oid, od, c1, a1, odd, obd, oir, oin, oq, allOnePrice);
    //printOrder(o1, true);

    // relation of employee and order
    int eoid = 0;
    struct employee_order eo1 = setEmployeeOrder(eoid, e1, o1);
    //printEmployeeOrder(eo1);
    
    return 0;
}

/**
* Takes in every member of an address struct, instantiates it,
* sets the values, and returns it
*/
struct address setAddress(int aid, char al1[101], char al2[101], char al3[101], 
char al4[101], char al5[101], char ar[101], char apc[101], char actry[101]) {
    struct address a;
    a.addrId = aid;
    strcpy(a.address1, al1);
    strcpy(a.address2, al2);
    strcpy(a.address3, al3);
    strcpy(a.address4, al4);
    strcpy(a.address5, al5);
    strcpy(a.region, ar);
    strcpy(a.postcode, apc);
    strcpy(a.country, actry);
    return a;
}

/**
* Takes in every member of a customer struct, instantiates it,
* sets the values, and returns it
*/
struct customer setCustomer(int cid, char cname[101]) {
	struct customer c;
	c.custId = cid;
	strcpy(c.custName, cname);
	return c;
}

/**
* Takes in every member of an employee struct, instantiates it,
* sets the values, and returns it
*/
struct employee setEmployee(char eid, char enm[101], char ejt[101], int emgr, char esd[11],
struct money *em) {
	struct employee e;
	e.empId = eid;
	strcpy(e.empName, enm);
	strcpy(e.jobTitle, ejt);
	e.mgrId = emgr;
	strcpy(e.startDate, esd);
	e.salary = *em;
	return e;
}

/**
* Takes in every member of an employee-order struct, instantiates it,
* sets the values, and returns it
*/
struct employee_order setEmployeeOrder(int eoid, struct employee eoe, struct order eoo) {
    struct employee_order eo;
    eo.emp_ord_id = eoid;
    eo.emp = eoe;
    eo.ord = eoo;
    return eo;
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

/**
* Takes in every member of an order struct, instantiates it,
* sets the values, and returns it
*/
struct order setOrder(int oid, char od[11], struct customer oc, struct address oa, 
char odd[11], bool obd, char oir[21], char oin[101], int oqt, struct money *oup) {
	struct order o;
	o.orderId = oid;
	strcpy(o.orderDate, od);
	o.cust = oc;
	o.del_addr = oa;
	strcpy(o.deliveryDate, odd);
	o.bDelivered = obd;
	strcpy(o.itemRef, oir);
	strcpy(o.itemName, oin);
	o.qty = oqt;
	o.ppu = *oup;
	return o;
}

/**
* Formatting for comparison of output rather than
* elegance of output
*/
void printAddress(struct address addr, bool bStandalone) {
    if(bStandalone) {
        printf("ADDRESS\n");
        printf("=======\n");
    }
    printf("Address1 is %s\n", addr.address1);
    printf("Address2 is %s\n", addr.address2);
    printf("Address3 is %s\n", addr.address3);
    printf("Address4 is %s\n", addr.address4);
    printf("Address5 is %s\n", addr.address5);
    printf("Region is %s\n", addr.region);
    printf("Postcode is %s\n", addr.postcode);
    printf("Country is %s\n", addr.country);
    
    if(bStandalone)
        printf("\n");
}

void printCustomer(struct customer cust, bool bStandalone) {
    if(bStandalone) {
        printf("CUSTOMER\n");
        printf("========\n");
    }
    
    printf("Customer id is %d\n", cust.custId);
    printf("Customer name is %s\n", cust.custName);
    
    if(bStandalone)
        printf("\n");
}

void printEmployee(struct employee emp, bool bStandalone) {
    if(bStandalone) {
        printf("EMPLOYEE\n");
        printf("========\n");
    }
    
    printf("Employee id is %c\n", emp.empId);
    printf("Employee is %s\n", emp.empName);
    printf("Employee job title is %s\n", emp.jobTitle);
    printf("Employee manager id is %d\n", emp.mgrId);
    printf("Employee start date was %s\n", emp.startDate);
    printf("Employee salary is ");
    printMoney(&emp.salary);
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

void printOrder(struct order ord, bool bStandalone) {
    if(bStandalone) {
        printf("ORDER\n");
        printf("=====\n");
    }
    
    printf("Order id is %d\n", ord.orderId);
    printf("Order date is %s\n", ord.orderDate);
    printCustomer(ord.cust, false);
    printAddress(ord.del_addr, false);
    printf("Delivery date is %s\n", ord.deliveryDate);
    printf("Order has ");
    if(!ord.bDelivered)
        printf("not ");
    printf("been delivered\n");
    printf("Item ref is %s\n", ord.itemRef);
    printf("Item name is %s\n", ord.itemName);
    printf("Item quantity is %d\n", ord.qty);
    printf("Price per unit is ");
    printMoney(&ord.ppu);
    printf("\n");

    
    if(bStandalone)
        printf("\n");
}

void printEmployeeOrder(struct employee_order eo) {
    printf("ORDER PLACED BY EMPLOYEE\n");
    printf("========================\n");
    printf("Employee/Order ID is %d\n", eo.emp_ord_id);
    printf("Employee id is %c\n", eo.emp.empId);
    printf("Employee name is %s\n", eo.emp.empName);
    printf("Employee's manager is %d\n", eo.emp.mgrId);
    printOrder(eo.ord, false);
}


//#include "include/common.h"
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <stdbool.h>
#include<time.h>

struct money {
  long whole_dollars; 
  int frac_dollar; 
};

struct customer {
	int custId;
	char custName[101];
};

struct employee {
        int empId;
  // on QEMU, make-f Makefile.morello-purecap run-fakedb_vanilla outputs:
  // "fakedb_vanilla.c:21:3: error: unknown type name 'uint'; did you mean 'int'?"
  //uint empId;
  	char empName[101];
  	char jobTitle[101];
  	int mgrId;
  	// Just use a string for now, time structures todo
  	char startDate[11];
  	struct money salary;
};

struct order {
	int orderId;
	char orderDate[11];
	char deliveryDate[11];
	bool bDelivered;
	char itemRef[21];
	char itemName[101];
	int qty;
	struct customer cust;
};

struct employee_order {
  int emp_ord_id;
  struct employee emp;
  struct order ord;  
};

int main(int argc, char *argv[])
{ 
	struct employee e1;
	
	struct order o1;
	
	struct money g6;
	g6.whole_dollars = 30000.00;
	g6.frac_dollar = 35;
	
	struct customer c1;
	c1.custId = 1;
	strcpy(c1.custName, "Herman");

	// Int outputs "Employee id is 1"
        // Uint outputs "Employee id is 1"
        //e1.empId = 1;

        // Int outputs "Employee id is 2147483647"
        // Uint outputs "Employee id is 2147483647:
	//e1.empId = INT_MAX;
        // ****
	// on make -f Makefile.morello-purecap run-fakedb_vanilla, uint outputs:
	// "fakedb_vanilla.c:68:2: error: use of undeclared identifier 'uint'; did you mean 'int'?"
	//uint intlimit = INT_MAX;
	int intlimit = INT_MAX;
	float overfloat = 6000000.01;

        // Int outputs "Employee id is 2147483647"
        // Uint outputs "Employee id is 2147483647"
	//e1.empId = intlimit++;

	// Int outputs "Employee id is -2147483648"
        // Uint outputs "Employee id is -2147483648" 
	//e1.empId = ++intlimit;

        // Int outputs "Employee id is -2"
        // Uint outputs "Employee id is -2" 
	//e1.empId = intlimit * 2;

        // Int outputs "Employee id is -4"
        // Uint outputs "Employee id is -4"
	//e1.empId = intlimit * 4;

        // int outputs "Employee id is 6000000"
        // uint outputs "Employee id is 6000000" 
        e1.empId = overfloat;

	// char[101] outputs "Employee is Bartleby"
	strcpy(e1.empName, "Bartleby");
        // char[101] outputs "Employee job title is Scrivener"
	strcpy(e1.jobTitle, "Scrivener");
        // int outputs "Employee manager id is 0"
	e1.mgrId = 0;
        // char[11] outputs "Employee start date was 2020-06-30"
	strcpy(e1.startDate, "2020-06-30");
        // long.int outputs "Employee salary is 30000.35"
	e1.salary = g6;
	
	o1.orderId = 1;
	strcpy(o1.orderDate, "2022-11-07");
	strcpy(o1.deliveryDate, "2022-13-07");
	o1.bDelivered = false;
 	strcpy(o1.itemRef, "1234567");
 	strcpy(o1.itemName, "Banana Bender");
 	o1.qty = 33;
 	o1.cust = c1;
 	
        printf("Employee id is %d\n", e1.empId);
	printf("Employee is %s\n", e1.empName);
	printf("Employee job title is %s\n", e1.jobTitle);
	printf("Employee manager id is %d\n", e1.mgrId);
        printf("Employee start date was %s\n", e1.startDate);
	printf("Employee salary is %ld.%d\n", e1.salary.whole_dollars, e1.salary.frac_dollar);

	struct employee_order eo1;
	eo1.emp_ord_id = 1;
	eo1.emp = e1;
	eo1.ord = o1;
	printf("Employee id %d by the name of %s placed order %d for %s on %s\n", eo1.emp.empId, eo1.emp.empName, eo1.ord.orderId, eo1.ord.itemName, eo1.ord.orderDate);
	
	return 0;
}

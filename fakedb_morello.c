#include "include/common.h"
#include <assert.h>
#include <limits.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
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
  char empName[101];
  //char *empName;
  char jobTitle[101];
  //char *jobTitle;
  int mgrId;
  // Just use a string for now, time structures todo
  char startDate[11];
  //char *startDate;
  struct money salary;
};

struct order {
  int orderId;
  char orderDate[11];
  //char *orderDate;
  char deliveryDate[11];
  //char *deliveryDate;
  bool bDelivered;
  char itemRef[21];
  //char *itemRef;
  char itemName[101];
  //char *itemName;
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
  //struct employee e1;

  struct employee *e1 = malloc(sizeof (struct employee));
  pp_cap(e1);
  
  struct order *o1 = malloc(sizeof(struct order));
  pp_cap(o1);
  
	struct money g6;
	g6.whole_dollars = 30000.00;
	g6.frac_dollar = 35;
	
	struct customer c1;
	c1.custId = 1;
	strcpy(c1.custName, "Herman");

        e1->empId = 1;

	int intlimit = INT_MAX;
	float overfloat = 6000000.01;
 
        //e1->empId = overfloat;

	strcpy(e1->empName, "Bartleby");
	strcpy(e1->jobTitle, "Scrivener");
	e1->mgrId = 0;
	strcpy(e1->startDate, "2020-06-30");
	e1->salary = g6;
	
	o1->orderId = 1;
	strcpy(o1->orderDate, "2022-11-07");
	strcpy(o1->deliveryDate, "2022-13-07");
	o1->bDelivered = false;
 	strcpy(o1->itemRef, "1234567");
 	strcpy(o1->itemName, "Banana Bender");
 	o1->qty = 33;
 	o1->cust = c1;
 	
        printf("Employee id is %d\n", e1->empId);
	printf("Employee is %s\n", e1->empName);
	printf("Employee job title is %s\n", e1->jobTitle);
	printf("Employee manager id is %d\n", e1->mgrId);
        printf("Employee start date was %s\n", e1->startDate);
	printf("Employee salary is %ld.%d\n", e1->salary.whole_dollars, e1->salary.frac_dollar);

	struct employee_order eo1;
	eo1.emp_ord_id = 1;
	eo1.emp = *e1;
	eo1.ord = *o1;
	printf("Employee id %d by the name of %s placed order %d for %s on %s\n", eo1.emp.empId, eo1.emp.empName, eo1.ord.orderId, eo1.ord.itemName, eo1.ord.orderDate);
	
	return 0;
}

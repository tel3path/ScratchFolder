// fakedb.h

/**
* An address, all free text no lookup for now
*/
struct address {
    int addrId;
    char address1[101];
    char address2[101];
    char address3[101];
    char address4[101];
    char address5[101];
    char region [101];
    char postcode[21];
    char country[101];
};

/**
* Because it doesn't work to store money as
* a float or decimal.
*/
struct money {
    // future-proof for inflation
    // all currency is $
    long whole_dollars; 
    // cents
    unsigned char frac_dollar; 
};

/**
* A minimal employee 
*/
struct employee {
    // employee ID number
    // (Let's make this a char. Not recommended for global megacorps)
    char empId;
    // employee name
    char empName[101];
    // job title
    char jobTitle[101];
    // manager ID (manager is an employee)
    int mgrId;
    // Just use a string for now, time structures TODO
    // YYYY-MM-DD
    char startDate[11];
    // not a grade or spine point or anything, just an amount TODO
    struct money salary;
};

/**
* A less-than-minimal customer
*/
struct customer {
    // Amazon has like 200 million Prime subscribers so
    // an int should hold us for a while
    int custId;
    // Full name all in one string for amusing trouble purposes later
    char custName[101];
};

/**
* A minimal order
*/
struct order {
    // how many orders per customer before we exceed an int
    int orderId;
    // YYYY-MM-DD
    char orderDate[11];
    struct customer cust;
    struct address del_addr;
    // YYYY-MM-DD
    char deliveryDate[11];
    // flag when delivered or not
    bool bDelivered;
    char itemRef[21];
    char itemName[101];
    int qty;
    // price per unit
    struct money ppu;
};

/**
* Relate order to employee
*/
struct employee_order {
    // unique ID of this employee-order relation
    int emp_ord_id;
    struct employee emp;
    struct order ord;  
};

void printAddress(struct address addr, bool bStandalone);

void printCustomer(struct customer cust, bool bStandalone);

void printEmployee(struct employee emp, bool bStandalone);

void printEmployeeOrder(struct employee_order eo);

void printMoney(struct money * m);

void printOrder(struct order emp, bool bStandalone);

struct address setAddress(int aid, char al1[101], char al2[101], char al3[101], char al4[101], char al5[101], char ar[101], char apc[21], char actry[101]);

struct customer setCustomer(int cid, char cname[101]);

struct employee setEmployee(char eid, char enm[101], char ejt[101], int emgr, char sd[11],
struct money *em);

struct employee_order setEmployeeOrder(int eoid, struct employee eoe, struct order eoo);

struct money * setMoney(long wd, unsigned char fd);

struct order setOrder(int oid, char od[11], struct customer oc, struct address oa, 
char odd[11], bool obd, char oir[21], char oin[101], int oqt, struct money *oup);




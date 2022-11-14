// fakedb.h

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
    char empName[10];
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

void printEmployee(struct employee *emp, bool bStandalone);

void printMoney(struct money * m);

struct employee * setEmployee(char *eid, char enm[10], char ejt[101], int emgr, char sd[11],
struct money *em);

struct money * setMoney(long wd, unsigned char fd);

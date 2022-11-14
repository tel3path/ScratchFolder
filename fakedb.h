// fakedb.h

struct employee {
    // employee ID number
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
};

void printEmployee(struct employee *emp);

struct employee * setEmployee(char *eid, char enm[10], char ejt[101], int emgr, char sd[11]);


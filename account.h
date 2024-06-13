#ifndef ACCOUNT_H
#define ACCOUNT_H

typedef struct {
    char accountNumber[255];
    double balance;
    char agencyCode[255];
    int fk_Client_ID;
    char password[255];
    int active;
} Account;

#endif

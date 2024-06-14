#ifndef CLIENT_H
#define CLIENT_H


typedef enum {
    Single,
    Married
} MaritalStatus;

typedef struct {
	int id;
    char cpf[12];
    char rg[30];
    char name[40];
    char address[40];
    char phone[12];
    MaritalStatus maritalStatus;
    int active;
} Client;



MaritalStatus stringToMaritalStatus(char* str) {
    if (str == NULL) {
        return Single; 
    }

    if (strcmp(str, "SINGLE") == 0) {
        return Single;
    } else if (strcmp(str, "MARRIED") == 0) {
        return Married;
    }
}

const char* MaritalStatusToString(MaritalStatus estado) {
    switch (estado) {
        case Single: return "Single";
        case Married: return "Married";
        default: return "Estado civil desconhecido";
    }
}

int isValidCpf(const char *cpf) {

    if (strlen(cpf) != 11) {
        return 0;
    }

    int i = 0;
    for (i; i < 11; ++i) {
        if (!isdigit(cpf[i])) {
            return 0;
        }
    }

    i = 0;
    int sum = 0;
    for (i; i < 9; ++i) {
        sum += (cpf[i] - '0') * (10 - i);
    }
    int firstDigit = (sum * 10) % 11;
    if (firstDigit == 10) firstDigit = 0;

    sum = 0;
    i = 0;
    for (i; i < 10; ++i) {
        sum += (cpf[i] - '0') * (11 - i);
    }
    int secondDigit = (sum * 10) % 11;
    if (secondDigit == 10) secondDigit = 0;

    if (cpf[9] - '0' != firstDigit || cpf[10] - '0' != secondDigit) {
        return 0;
    }

    return 1;
}

int isValidRg(const char *rg) {
    return (strlen(rg) == 9);;
}


#endif 


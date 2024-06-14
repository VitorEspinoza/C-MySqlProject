#ifndef TRANSACTION_H
#define TRANSACTION_H

typedef enum {
    Credit,
    Debit
} PaymentType;

typedef struct {
	char accountNumber[20];
	char targetAccount[20];
    double amount;
    char date[11];
    char hour[9];
    PaymentType paymentType;
} Transaction;

PaymentType stringToPaymentType(char* str) {
    if (str == NULL) {
        return Credit; 
    }

    if (strcmp(str, "CREDIT") == 0) {
        return Credit;
    } else if (strcmp(str, "DEBIT") == 0) {
        return Debit;
    }
}

const char* PaymentTypeToString(PaymentType paymentType) {
    switch (paymentType) {
        case 0: return "Credit";
        case 1: return "Debit";
        default: return "Forma de pagamento desconhecida";
	}
}
#endif

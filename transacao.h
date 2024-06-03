#ifndef TRANSACAO_H
#define TRANSACAO_H

typedef enum {
    Credit,
    Debit
} PaymentType;

typedef struct {
	char numeroConta[20];
	char contaDestino[20];
    double quantia;
    char data[11];
    char hora[9];
    PaymentType paymentType;
} Transaction;

PaymentType stringToPaymentType(char* str) {
    if (str == NULL) {
        printf("Erro: str é NULL\n");
        return Credit; 
    }

    if (strcmp(str, "CREDITO") == 0) {
        return Credit;
    } else if (strcmp(str, "DEBITO") == 0) {
        return Debit;
    }
}

const char* PaymentTypeToString(PaymentType paymentType) {
    switch (paymentType) {
        case 0: return "Credito";
        case 1: return "Debito";
        default: return "Forma de pagamento desconhecida";
	}
}
#endif

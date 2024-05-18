#include <conta.h>

struct Transacao {
    struct Conta numeroConta;
    double quantia;
    char data[10];
    char hora[5];
    enum tipoPagamento {
        Credito,
        Debito
    };
};

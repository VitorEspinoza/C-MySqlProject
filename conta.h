#ifndef CONTA_H
#define CONTA_H

typedef struct {
    char numeroConta[255];
    double saldo;
    char numAgencia[255];
    int fk_Cliente_ID;
    char senha[255];
    int ativa;
} Conta;

#endif


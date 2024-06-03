#ifndef CONTA_H
#define CONTA_H

typedef struct {
    char numeroConta[255];
    double saldo;
    char numAgencia[255];
    char cpfCliente[12];
    char senha[255];
} Conta;

#endif


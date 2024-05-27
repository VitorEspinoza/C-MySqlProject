#ifndef CONTA_H
#define CONTA_H


typedef struct {
	int numeroConta;
    double saldo;
    int numAgencia;
    char cpfCliente[12];
	char senha[255];
} Conta;

#endif 

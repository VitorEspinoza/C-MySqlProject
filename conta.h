#include "agencia.h"

struct Conta {
    int numeroConta;
    double saldo;
    struct Agencia codigoAgencia;
    char nomeGerente[40];
    Cliente cliente;
};

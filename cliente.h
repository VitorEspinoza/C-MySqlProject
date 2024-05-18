#ifndef CLIENTE_H
#define CLIENTE_H


enum EstadoCivil {
    Solteiro,
    Casado
};

typedef struct {
    char cpf[12];
    char rg[30];
    char nome[40];
    char endereco[40];
    char telefone[12];
    enum EstadoCivil estadoCivil;
} Cliente;


#endif 


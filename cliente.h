#ifndef CLIENTE_H
#define CLIENTE_H


typedef enum {
    Solteiro,
    Casado
} EstadoCivil;

typedef struct {
	int id;
    char cpf[12];
    char rg[13];
    char nome[101];
    char endereco[40];
    char telefone[12];
    EstadoCivil estadoCivil;
} Cliente;


EstadoCivil stringToEstadoCivil(char* str) {
    if (str == NULL) {
        printf("Erro: str é NULL\n");
        return Solteiro; 
    }

    if (strcmp(str, "SOLTEIRO") == 0) {
        return Solteiro;
    } else if (strcmp(str, "CASADO") == 0) {
        return Casado;
    }
}

const char* EstadoCivilToString(EstadoCivil estado) {
    switch (estado) {
        case Solteiro: return "Solteiro";
        case Casado: return "Casado";
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


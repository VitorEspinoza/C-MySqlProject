#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "conta.h"
#include "databaseController.h"

char* generateRandomNumber();

Propriedade* setPropriedadesConta(Conta conta) {
	
    static Propriedade propriedades[5];
	
	char saldoConta[50];
	sprintf(saldoConta, "%lf", conta.saldo);
	
    propriedades[0] = setPropriedade("fk_cliente_cpf", "string", conta.cpfCliente);
    propriedades[1] = setPropriedade("codigoAgencia", "string", conta.numAgencia);
    propriedades[2] = setPropriedade("saldo", "double", saldoConta);
    propriedades[3] = setPropriedade("senha", "string", conta.senha);
    propriedades[4] = setPropriedade("numeroConta", "string", conta.numeroConta);

    return propriedades;
}

int createConta(Conta conta) {
	
	char randomNumber = generateRandomNumber();
    strcpy(conta.numeroConta, randomNumber);
    free(randomNumber);
    
	Propriedade* propriedades = setPropriedadesConta(conta);
	printf("testando");
	
	int success = create("Conta", 5, propriedades[0], propriedades[1], propriedades[2], propriedades[3], propriedades[4]);
	
	printf("depos");
	return success;
}

Conta readContaByField(Propriedade propriedade) {
	MYSQL_ROW row = readByField("conta", propriedade);
	
	Conta conta;
	
	strcpy(conta.numeroConta, row[0]);
	conta.saldo = atof(row[1]);
	strcpy(conta.numAgencia, row[2]);
	strcpy(conta.cpfCliente, row[3]);
	
	clearResult();
	return conta;

}

char* generateRandomNumber() {
    srand(time(NULL)); // Inicializa o gerador de números aleatórios

    int number = rand() % 90000 + 10000; // Gera um número aleatório entre 10000 e 99999

    char* str = malloc(6 * sizeof(char)); // Aloca memória para a string
    if (str == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    sprintf(str, "%d", number); // Converte o número para uma string

    return str; // Retorna a string
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include <time.h>
#include "conta.h"
#include "databaseController.h"

typedef struct {
	int success;
	Conta account;
} ResponseAccount;

char* randomFourDigitNumber();
Conta readContaByField(Propriedade propriedade);

Propriedade* setPropriedadesConta(Conta conta) {
	
    static Propriedade propriedades[5];
	
	char saldoConta[50];
	sprintf(saldoConta, "%lf", conta.saldo);
	
	char idCliente[50];
	sprintf(idCliente, "%d", conta.fk_Cliente_ID);
	
    propriedades[0] = setPropriedade("fk_Cliente_ID", "int", idCliente);
    propriedades[1] = setPropriedade("codigoAgencia", "string", conta.numAgencia);
    propriedades[2] = setPropriedade("saldo", "double", saldoConta);
    propriedades[3] = setPropriedade("senha", "string", conta.senha);
    propriedades[4] = setPropriedade("numeroConta", "string", conta.numeroConta);

    return propriedades;
}

ResponseAccount createConta(Conta conta) {
	
	char* generatedNumber;
	Propriedade numAccountProp;
	Conta existingAccount;
	int isExist;
	
	do {
		generatedNumber = randomFourDigitNumber();
		numAccountProp = setPropriedade("numeroConta", "string", generatedNumber);
		existingAccount = readContaByField(numAccountProp);
		isExist = strcmp(existingAccount.numeroConta, "NULL") != 0;
		
	} while(isExist);

    strcpy(conta.numeroConta, generatedNumber);
    free(generatedNumber);
    
	Propriedade* propriedades = setPropriedadesConta(conta);

	
	ResponseAccount responseAccount;
	responseAccount.success = create("Conta", 5, propriedades[0], propriedades[1], propriedades[2], propriedades[3], propriedades[4]);
	
	responseAccount.account = conta;

	clearBuffer();
	getchar();
	
	return responseAccount;
}

Conta readContaByField(Propriedade propriedade) {
	MYSQL_ROW row = readByField("conta", propriedade);

	Conta conta;
	
	if(row == NULL) {
		strcpy(conta.numeroConta, "NULL");
		clearResult();
		return conta;
	}
	
	strcpy(conta.numeroConta, row[0]);
	conta.saldo = atof(row[1]);
	strcpy(conta.numAgencia, row[2]);
	conta.fk_Cliente_ID = atoi(row[3]);
	strcpy(conta.senha, row[4]);
	conta.ativa = atoi(row[5]);
	clearResult();
	return conta;

}

ResponseAccount updateAccount(Conta account, Propriedade identifierField) {

  	Propriedade* propriedades = setPropriedadesConta(account);
  	
  	ResponseAccount responseAccount;
	responseAccount.success = update("Conta", identifierField, 5, propriedades[0], propriedades[1], propriedades[2], propriedades[3], propriedades[4]);
	
	responseAccount.account = account;
	
	return responseAccount;
}

int deleteConta(Propriedade identifierField) {
	Propriedade activeAccount = setPropriedade("ativa", "int", "0");
	int success = update("conta", identifierField, 1, activeAccount);
	return success;
}

int reactiveAccount(Propriedade identifierField) {
	Propriedade activeAccount = setPropriedade("ativa", "int", "1");
	int success = update("conta", identifierField, 1, activeAccount);
	return success;
}


char* randomFourDigitNumber() {
    srand(time(NULL));
    int number = rand() % 9000 + 1000; 

    char* str = malloc(5 * sizeof(char)); 
    if (str == NULL) {
        printf("Erro ao alocar memória.\n");
        exit(1);
    }

    sprintf(str, "%d", number); 

    return str;
}

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <locale.h>
#include "conta.h"
#include "databaseController.h"

int createConta(Conta conta) {
	printf("testando\n");
	
	setlocale(LC_NUMERIC, "C");

	char numAgenciaConvertido[50];
	sprintf(numAgenciaConvertido, "%d", conta.numAgencia);
    printf("Numero agencia: %s\n", numAgenciaConvertido);
    
	Propriedade numAgenciaProp;
	numAgenciaProp = setPropriedade("codigoAgencia", "int", numAgenciaConvertido);
	
	Propriedade cpfClienteProp;
	cpfClienteProp = setPropriedade("FK_Cliente_CPF", "string", conta.cpfCliente);
	printf("CPF: %s\n", cpfClienteProp.Valor);
	
	char saldoCliente[50];
	sprintf(saldoCliente, "%.2f", conta.saldo);
	printf("saldoCliente: ");
	printf("c%\n", saldoCliente);
	
	Propriedade saldoProp;
	saldoProp = setPropriedade("saldo", "double", saldoCliente);
	
	Propriedade senhaProp;
	senhaProp = setPropriedade("senha", "string", conta.senha);
	
	int success = create("Conta", 4, numAgenciaProp, cpfClienteProp, saldoProp, senhaProp);
	
	return success;
}

Conta readContaByField(Propriedade propriedade) {
	MYSQL_ROW row = readByField("conta", propriedade);
	
	Conta conta;
	
	conta.numeroConta = atoi(row[0]);
	conta.saldo = atof(row[1]);
	conta.numAgencia = atoi(row[2]);
	strcpy(conta.cpfCliente, row[3]);
	
	clearResult();
	return conta;

}

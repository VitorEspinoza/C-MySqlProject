#include <string.h>
#include <locale.h>
#include <stdio.h>
#include "transacao.h"
#include "databaseController.h"

typedef struct {
	int numberOfRows;
	Transaction** transactions;
}ResponseTransactions;

Propriedade* setPropertiesTransaction(Transaction transaction) {

	char convertedPaymentType[10];
    strcpy(convertedPaymentType, PaymentTypeToString(transaction.paymentType));

	char quantityString[50];
	sprintf(quantityString, "%lf", transaction.quantia);

    static Propriedade propriedades[6];

    propriedades[0] = setPropriedade("fk_conta_numeroconta", "string", transaction.numeroConta);
    propriedades[1] = setPropriedade("quantia", "double", quantityString);
    propriedades[2] = setPropriedade("data", "date", transaction.data);
    propriedades[3] = setPropriedade("hora", "time", transaction.hora);
    propriedades[4] = setPropriedade("conta_Destino", "string", transaction.contaDestino);
    propriedades[5] = setPropriedade("tipoPagamento", "string", convertedPaymentType);

    return propriedades;
}


int createTransaction(Transaction transaction) {
	Propriedade* propriedades = setPropertiesTransaction(transaction);
	int success = create("transacao", 6, propriedades[0], propriedades[1], propriedades[2], propriedades[3], propriedades[4], propriedades[5]);

	return success;
}


void fillTransaction(void* structToFill, MYSQL_ROW row) {
    if (structToFill == NULL || row == NULL) {
        printf("Erro: structToFill ou row é NULL\n");
        return;
    }

    Transaction* transaction = (Transaction*)structToFill;

    if (row[0] != NULL) strcpy(transaction->numeroConta, row[0]);
    if (row[1] != NULL) strcpy(transaction->contaDestino, row[1]);
	if (row[2] != NULL) transaction->paymentType = stringToPaymentType(row[2]);
    if (row[3] != NULL) transaction->quantia = atof(row[3]);
    if (row[4] != NULL) strcpy(transaction->data, row[4]);
    if (row[5] != NULL) strcpy(transaction->hora, row[5]);
}

ResponseTransactions readAllTransactions(char * numeroConta) {
	char whereQuery[50];

	sprintf(whereQuery, "WHERE fk_conta_numeroConta = %s", numeroConta);

	ResponseTransactions responseTransactions;

    responseTransactions.transactions = (Transaction**)readAll("Transacao", fillTransaction, sizeof(Transaction), whereQuery, &(responseTransactions.numberOfRows));
	return responseTransactions;
}

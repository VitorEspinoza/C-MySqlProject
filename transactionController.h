#include <string.h>
#include <locale.h>
#include <stdio.h>
#include "transaction.h"
#include "databaseController.h"

typedef struct {
	int numberOfRows;
	Transaction** transactions;
}ResponseTransactions;

Property* setPropertiesTransaction(Transaction transaction) {

	char convertedPaymentType[10];
    strcpy(convertedPaymentType, PaymentTypeToString(transaction.paymentType));

	char quantityString[50];
	sprintf(quantityString, "%lf", transaction.amount);

    static Property properties[6];

    properties[0] = setProperty("fk_account_accountNumber", "string", transaction.accountNumber);
    properties[1] = setProperty("amount", "double", quantityString);
    properties[2] = setProperty("date", "date", transaction.date);
    properties[3] = setProperty("hour", "time", transaction.hour);
    properties[4] = setProperty("target_account", "string", transaction.targetAccount);
    properties[5] = setProperty("paymentType", "string", convertedPaymentType);

    return properties;
}


int createTransaction(Transaction transaction) {
	Property* properties = setPropertiesTransaction(transaction);
	int success = create("transaction", 6, properties[0], properties[1], properties[2], properties[3], properties[4], properties[5]);

	return success;
}


void fillTransaction(void* structToFill, MYSQL_ROW row) {
    if (structToFill == NULL || row == NULL) {
        return;
    }

    Transaction* transaction = (Transaction*)structToFill;

    if (row[0] != NULL) strcpy(transaction->accountNumber, row[0]);
    if (row[1] != NULL) strcpy(transaction->targetAccount, row[1]);
	if (row[2] != NULL) transaction->paymentType = stringToPaymentType(row[2]);
    if (row[3] != NULL) transaction->amount = atof(row[3]);
    if (row[4] != NULL) strcpy(transaction->date, row[4]);
    if (row[5] != NULL) strcpy(transaction->hour, row[5]);
}

ResponseTransactions readAllTransactions(char * accountNumber) {
	char whereClause[50];

	sprintf(whereClause, "WHERE fk_account_accountNumber = %s", accountNumber);

	ResponseTransactions responseTransactions;

    responseTransactions.transactions = (Transaction**)readAll("transaction", fillTransaction, sizeof(Transaction), whereClause, &(responseTransactions.numberOfRows));
	return responseTransactions;
}
